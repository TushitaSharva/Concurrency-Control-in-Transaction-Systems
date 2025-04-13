#ifndef DATAITEM_H
#define DATAITEM_H

#include <set>
#include <mutex>
#include <climits>

class DataItem {
public:
    int value;
    int maxRead;
    int maxWrite;
    std::mutex datalock;

    DataItem() {
        value = 0;
        maxRead = INT_MIN;
        maxWrite = INT_MIN;
    }
};

#endif // DATAITEM_H
