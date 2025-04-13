#include <iostream>
#include <vector>
#include <random>
#include <string.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <mutex>
#include <time.h>
#include <chrono>
#include <fstream>
#include <atomic>
#include <mutex>
#include <thread>
#include "Logger.h"
#include "DataItemForAbortOther.h"
#include "Transaction.h"

static Logger LOGGER;
int n, m, totalTrans, constVal, numIters;
float lambda;
std::vector<DataItem> shared;
std::atomic<int> availableTransactionId{0};
std::atomic<long long> totalCommitDelay{0};
std::atomic<long long> totalAborts{0};


void readInput(std::string filename)
{
    std::ifstream inputfile(filename);
    inputfile >> n >> m >> totalTrans >> constVal >> lambda >> numIters;
    shared.resize(m);
    LOGGER.x = 2; // For writing into repective log file
    inputfile.close();
    return;
}

double Timer(float exp_time) {
    static std::random_device rd;  // Non-deterministic random seed
    static std::mt19937 generate(rd());  // Mersenne Twister PRNG
    std::exponential_distribution<double> distr(1.0 / exp_time);
    return distr(generate);
}

Transaction *begin_trans() {
    return new Transaction(availableTransactionId.fetch_add(1));
}

void read(Transaction *t, int index, int *localVal) {

    shared[index].lock.lock();
    *localVal = shared[index].value;
    shared[index].readList.insert(t);
    shared[index].lock.unlock();
    t->readSet.insert(index);

    return;
}

void write(Transaction *t, int index, int localVal) {

    t->localWrites[index] = localVal;
    t->writeSet.insert(index); // Unnecessary? Iterate over localWrites.first()?

    return;
}


// Everytime we acquire a lock, if it waited, it means that it waited for some transaction to evaluate, and therefor, there is a chance this transaction's status is set to abort.
// So check if there is an abort before acquiring lock on each data item
// If after acquiring all locks, if this transaction didnot abort, then it will continue and probably set others to abort, if at all.
TransactionStatus tryCommit(Transaction *t) {

    TransactionStatus status = commited;

    for(auto item: t->writeSet) {
        shared[item].lock.lock();

        if(status != aborted) {
            status = t->status.load();
            // If my status is set abort by some other transaction, I will set this to abort as well. 
            // Anyhow we need to access atomic at this point, so no extra time taken
            // break; // Should not break because we need to acquire locks for modifying readLists too
        }
    }

    for(auto i: t->readSet) { // By now, I acquired all locks, I will either commit or abort. So I will remove myself from all readLists
        // No need to lock because readSet = writeSet, so we are already holding the lock
        shared[i].readList.erase(t);
    }
    
    
    if(status == aborted) { // If aborted, release locks and return abort

        for(auto i : t->writeSet) {
            shared[i].lock.unlock();
        }

        return aborted;
    }

    // If not aborted, we should check for conflicts and then abort those that are in conflicts
    // Checking if my writeset's dataitems' readlist is not empty
    // At this point I will abort others, so I will write globally
    for(auto item: t->writeSet) {
        shared[item].value = t->localWrites[item];

        if(shared[item].readList.size() != 0) {
            for(auto transaction: shared[item].readList) {
                transaction->status.store(aborted);
            }
        }

        shared[item].lock.unlock();
    }

    return status;
}

void updtMem(int i) {
    TransactionStatus status = aborted;
    int abortCnt = 0;

    int numTrans = (totalTrans/n);

    if(i < totalTrans % n) { // For first reminder number of threads, just deal with one more transaction
        numTrans++;
    }

    for(int currTrans = 0; currTrans < numTrans; currTrans++) {
        abortCnt = 0;
        
        auto critStartTime = std::chrono::high_resolution_clock::now();

        do {
            Transaction *t = begin_trans();
            int localVal = 0;

            for(int i = 0; i < numIters; i++) {
                int randInd = rand()%m;
                int randVal = rand()%constVal;

                read(t, randInd, &localVal);
                LOGGER.OUTPUTT("Thread id ", i, ", transaction ", t->id, " reads from [", randInd, "] a value ", localVal, " at time ");

                localVal += randVal;

                write(t, randInd, localVal);
                LOGGER.OUTPUTT("Thread id ", i, ", transaction ", t->id, " writes (locally) to [", randInd, "] a value ", localVal, " at time ");

                auto randTime = Timer(lambda);
                usleep((int)Timer(lambda) *1e3);
            }
            
            status = tryCommit(t);
            LOGGER.OUTPUTT(t->id, "th transaction tryCommit resulted in ", status, " at time ");

            if(status == aborted) {
                abortCnt++;
            }

            // Before deleting the transaction, delete itself from all readlists

            delete t;
        } while (status != commited);

        auto critEndTime = std::chrono::high_resolution_clock::now();
        auto commitDelay = std::chrono::duration_cast<std::chrono::milliseconds>(critEndTime - critStartTime).count();

        LOGGER.OUTPUTT("Commit Delay: ", commitDelay, " milliseconds, ", "abortCount: ", abortCnt);
        totalCommitDelay.fetch_add(commitDelay);
        totalAborts.fetch_add(abortCnt);
    }
}

int main(int argc, char *argv[]) {
    readInput(argv[1]);
    auto start_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT(argv[1]);
    LOGGER.OUTPUTT("The start time is ");

    std::thread threads[n];

    for(int i = 0; i < n; i++) {
        threads[i] = std::thread(updtMem, i);
    }

    for(int i = 0; i < n; i++) {
        threads[i].join();
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUTT("The stop time is ");

    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
    LOGGER.OUTPUT("Total execution time: ", time_diff, " milliseconds");
    std::cout << " Avg commit delay = " << (double)totalCommitDelay.load()/totalTrans << " Avg aborts = " << (double)totalAborts.load()/totalTrans << "\n";

    return 0;
}