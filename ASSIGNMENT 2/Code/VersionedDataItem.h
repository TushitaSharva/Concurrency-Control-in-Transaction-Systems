#ifndef VERSION_DATAITEM_H
#define VERSION_DATAITEM_H

#include <set>

class VersionedDataItem {
public:
    int version;
    int valueInThisVersion;
    std::set<int> readList;

    int getLargestInReadList() {
        if(readList.empty()) {
            return -1;
        }
        
        return *readList.rbegin(); // or throw an exception if preferred
    }
};

#endif
