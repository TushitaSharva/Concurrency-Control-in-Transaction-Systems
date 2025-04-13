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
std::atomic<int> clk{0};
std::atomic<long long> totalCommitDelay{0};
std::atomic<long long> totalAborts{0};

void readInput(std::string filename) {
    std::ifstream inputfile(filename);
    inputfile >> n >> m >> totalTrans >> constVal >> lambda >> numIters;
    shared.resize(m);
    LOGGER.x = 0; // For writing into the respective output file
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
    return new Transaction(availableTransactionId.fetch_add(1), clk.fetch_add(1));
}

void read(Transaction *t, int index, int *localVal) {
    shared[index].lock.lock();
    *localVal = shared[index].value;
    t->readSet.insert(index);
    shared[index].lock.unlock();

    return;    
}

void write(Transaction *t, int index, int localVal) {
    shared[index].lock.lock();
    t->localWrites[index] = localVal;
    t->writeSet.insert(index); // Unnecessary? Iterate over localWrites.first()?
    shared[index].lock.unlock();
    return;
}

/*
    Whenever a transaction is going to be committed, it should inform each data item in the write set that mine is the last commit so that whenever a new item checks in val-write phase, it doesn't have to iterate all end times. Locks aquired and then modified, hence at any point latest will be checked.
*/
TransactionStatus tryCommit(Transaction *t) {
    TransactionStatus status = commited;

    for(auto item: t->readSet) { // readSet = writeSet in program, so no need of union lock for now
        shared[item].lock.lock();
    }

    // Checking if my readSet's dataitems' writeList is not empty
    for(auto item: t->readSet) {
        if(shared[item].highest_endTime < t->start_time) { 
            // If highest_endTime < t->start_time: All transactions in that set have ended before I started.
            continue;
        }
        else if(shared[item].writeList.size() != 0) {
            // Means there is atleast one transaction that ran concurrently and is in write-set
            status = aborted;
        }
        if(status == aborted) {
            break;
        }
    }

    if(status == aborted) {
        for(auto item: t->readSet) {
            shared[item].lock.unlock();
        }
    }

    else if(status == commited) {
        auto commit_decide_time = clk.fetch_add(1);
        for(auto item: t->writeSet) { // writeset = readset, so all writes are written and also read locks are released. Can be thought as lock upgrade.
            shared[item].value = t->localWrites[item];
            shared[item].writeList.insert(t->id);
            shared[item].highest_endTime = commit_decide_time;
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
                LOGGER.OUTPUT("Thread id ", i, ", t", t->id, " reads from [", randInd, "] a value ", localVal, " at time ");
                
                localVal += randVal;
                
                write(t, randInd, localVal);
                LOGGER.OUTPUTT("Thread id ", i, ", t", t->id, " writes (locally) to [", randInd, "] a value ", localVal, " at time ");

                auto randTime = Timer(lambda);
                // sleep(randTime); // seconds delay
                usleep((int)Timer(lambda) *1e3); // seconds level delay
            }

            status = tryCommit(t);
            LOGGER.OUTPUTT(t->id, "th transaction's try commit resulted in ", status);
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

    std::cout << " Avg commit delay = " << (double)totalCommitDelay.load()/totalTrans << " Avg aborts = " << (double)totalAborts.load()/totalTrans << "\n";

    return 0;
}