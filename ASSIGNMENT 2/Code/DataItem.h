#ifndef DATAITEM_H
#define DATAITEM_H

#include <map>
#include <mutex>
#include "VersionedDataItem.h"

class DataItem {
public:
    std::map<int, VersionedDataItem> versions;  // key = version
    std::mutex datalock;

    DataItem() {
        VersionedDataItem initial;
        initial.version = 0;
        initial.valueInThisVersion = 0;
        // readList is already empty by default
        versions[0] = initial;
    }

    int getGreatestVersionLessThanMyId(int id) {
        int ans = -1;
        
        for(auto &[key, val] : versions) {
            // std::cout << "vsize = " << versions.size() << "\n";
            if(key < id) {
                ans = key;
            }
        }
        // std::cout << "\n";

        return ans;
    }
};

#endif // DATAITEM_H
