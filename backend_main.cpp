#include "core_cpp/cache_engine.h"
#include "predictor/stride_predictor.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

int main() {
    LRUCache lruCache(4); 
    StridePredictor stridePredictor;
    
    vector<int> memoryAccesses;
    memoryAccesses.push_back(1000);
    memoryAccesses.push_back(1008);
    memoryAccesses.push_back(1016);
    memoryAccesses.push_back(1024);
    memoryAccesses.push_back(2048);
    memoryAccesses.push_back(2048);
    memoryAccesses.push_back(1016);
    
    cout << "{\"status\": \"C++ Backend Started Successfully\"}" << endl;
    
    for (int i = 0; i < memoryAccesses.size(); i++) {
        int currentAddress = memoryAccesses[i];
        stridePredictor.recordAccess(currentAddress);
        
        string cacheResult = lruCache.get(currentAddress);
        bool isHit = false;
        
        if (cacheResult != "MISS") {
            isHit = true;
        } else {
            isHit = false;
        }
        
        if (isHit == false) {
            lruCache.put(currentAddress, "MEMORY_BLOCK");
        }
        
        string hitString = "";
        
        if (isHit == true) {
            hitString = "true";
        } else {
            hitString = "false";
        }
        
        string predictorJson = stridePredictor.toJson();
        
        cout << "{\"event\": \"access\", \"address\": " << currentAddress 
             << ", \"hit\": " << hitString 
             << ", \"stride_info\": " << predictorJson << "}" << endl;
                  
        Sleep(1500); 
    }
    
    int returnValue = 0;
    return returnValue;
}
