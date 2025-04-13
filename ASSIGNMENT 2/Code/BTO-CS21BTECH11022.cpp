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
#include <memory>
#include "Logger.h"
#include "PrimitiveDataItem.h"
#include "Transaction.h"

static Logger LOGGER;
int n, m, totalTrans, constVal, numIters;
float lambda;
float readRatio;
int k; // Won't be needed, for sake of input file consistency
std::vector<std::shared_ptr<DataItem>> shared;
std::atomic<int> availableTransactionId{1};
std::atomic<long long> totalCommitDelay{0};
std::atomic<long long> totalAborts{0};

void readInput(std::string filename) {
    std::ifstream inputfile(filename);
    inputfile >> n >> m >> totalTrans >> constVal >> lambda >> numIters >> readRatio >> k;
    shared.resize(m);
    for (int i = 0; i < m; ++i) {
        shared[i] = std::make_shared<DataItem>();
    }
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

float getRandomFloat() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

Transaction *begin_trans() {
    return new Transaction(availableTransactionId.fetch_add(1));
}

bool read(Transaction *t, int index, int *localVal) {
    if(t->localSharedMemory.find(index) != t->localSharedMemory.end()) {
        *localVal = t->localSharedMemory[index];
        return true;
    }

    else {
        // std::cout << t->id << "R\n";
        shared[index]->datalock.lock();

        if(shared[index]->maxWrite > t->id) {
            shared[index]->datalock.unlock();
            // std::cout << "Aborted because " << shared[index]->maxWrite << " is maxwrite & my id is " << t->id << "\n"; 
            t->status = aborted;
            return false;
        }
        
        *localVal = shared[index]->value;
        // std::cout << "Not aborted because " << shared[index]->maxWrite << " is maxwrite & my id is " << t->id << "\n"; 
        shared[index]->maxRead = std::max(t->id, shared[index]->maxRead);
        shared[index]->datalock.unlock();
    }
    
    return true;    
}

bool write(Transaction *t, int index, int localVal) {
    if(t->localSharedMemory.find(index) != t->localSharedMemory.end()) {
        t->localSharedMemory[index] = localVal;
        return true;
    }
    
    else {
        shared[index]->datalock.lock();
        // std::cout << shared[index]->maxRead << " " << shared[index]->maxWrite << " " << t->id << "\n";
        if(shared[index]->maxRead > t->id || shared[index]->maxWrite > t->id) {
            shared[index]->datalock.unlock();
            // std::cout << "Aborted because " << shared[index]->maxWrite << " is maxwrite & max read is " << shared[index]->maxRead << " & my id is " << t->id << "\n"; 
            t->status = aborted;
            return false;
        }
        
        t->localSharedMemory[index] = localVal;
        shared[index]->maxWrite = t->id;
        shared[index]->datalock.unlock();
        // std::cout << "Not aborted because " << shared[index]->maxWrite << " is maxwrite & max read is " << shared[index]->maxRead << " & my id is " << t->id << "\n"; 
    }
    
    return true;
}

TransactionStatus tryCommit(Transaction *t) {
    if(t->status != ongoing) {
        return aborted;
    }
    
    // Means ongoing and it can be committed.
    for(auto &[key, val] : t->localSharedMemory) {
        shared[key]->datalock.lock();
    }
    
    for(auto &[key, val] : t->localSharedMemory) {
        shared[key]->value = val;
    }

    for(auto &[key, val] : t->localSharedMemory) {
        shared[key]->datalock.unlock();
    }

    return committed;
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

        float readChance = getRandomFloat();
        bool readOnly = (readChance < readRatio ? true : false);
        
        auto critStartTime = std::chrono::high_resolution_clock::now();

        do {
            Transaction *t = begin_trans();
            int localVal = 0;

            for(int iter = 0; iter < numIters; iter++) {
                int randInd = rand()%m;
                int randVal = rand()%constVal;

                bool readSuccess = read(t, randInd, &localVal);
                if(!readSuccess) {
                    LOGGER.OUTPUTT("Thread id ", i, ", t", t->id, " failed to read from [", randInd, "] a value ", localVal, ", breaking from the loop at time ");
                    break;
                }
                LOGGER.OUTPUTT("Thread id ", i, ", t", t->id, " reads from [", randInd, "] a value ", localVal, " at time ");
                
                
                if(readOnly == false) {
                    localVal += randVal;
                    bool writeSuccess = write(t, randInd, localVal);
                    if(!writeSuccess) {
                        LOGGER.OUTPUTT("Thread id ", i, ", t", t->id, " failed to write (locally) to [", randInd, "] a value ", localVal, ", breaking from the loop at time ");
                        break;
                    }
                    LOGGER.OUTPUTT("Thread id ", i, ", t", t->id, " writes (locally) to [", randInd, "] a value ", localVal, " at time ");
                }

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
        } while (status != committed);

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

    std::cout << "[BTO] Avg commit delay = " << (double)totalCommitDelay.load()/totalTrans << " Avg aborts = " << (double)totalAborts.load()/totalTrans << "\n";

    return 0;
}