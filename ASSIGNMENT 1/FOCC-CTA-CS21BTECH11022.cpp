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
#include "DataItem.h"
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
    LOGGER.x = 1; // For writing into the respective output file
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
    t->readSet.insert(index);
    shared[index].readList.insert(t->id);
    shared[index].lock.unlock();
    return;
}

void write(Transaction *t, int index, int localVal) {
    t->localWrites[index] = localVal;
    t->writeSet.insert(index); // Unnecessary? Iterate over localWrites.first()?
    
    return;
}

TransactionStatus tryCommit(Transaction *t) {

    TransactionStatus status = commited;

    for(auto item:t->writeSet) {
        shared[item].lock.lock();
    }

    // Now we acquired locks on all data items. If any other transaction acquires lock after this,
    // By then this transaction's valwrite phase will be done, so not concurrent anymore
    // So removing from readlist here
    for(auto item: t->readSet) { // But because readset = writeset, we don't have to lock, lock is already with us
        shared[item].readList.erase(t->id);
    }

    // Checking if my writeset's dataitems' readlist is not empty
    for(auto item: t->writeSet) {
        if(shared[item].readList.size() != 0) {
            status = aborted;
        }

        if(status == aborted) {
            break;
        }
    }

    if(status == aborted) {
        for(auto item: t->writeSet) {
            shared[item].lock.unlock();
        }
    }

    if(status == commited) { // if this is a committed transaction, then update local write too and then unlock
        for(auto item: t->writeSet) {
            shared[item].value = t->localWrites[item];
            shared[item].lock.unlock();
        }
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
                // sleep(randTime); // seconds delay
                usleep((int)Timer(lambda) *1e3); // seconds level delay
            }

            status = tryCommit(t);
            
            LOGGER.OUTPUTT(t->id, "th transaction tryCommit resulted in ", status, " at time ");

            if(status == aborted) {
                abortCnt++;
            }
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
    std::cout << "Average Commit Delay = " << (double)totalCommitDelay.load()/totalTrans << " Average aborts = " << (double)totalAborts.load()/totalTrans << "\n";

    return 0;
}