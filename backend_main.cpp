#include "core_cpp/cache_engine.h"
#include "predictor/stride_predictor.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

int main() {
    // combine member 1 and member 2 codes
    LRUCache lru_cache(4); 
    StridePredictor predictor;
    
    // fake memory block requests
    vector<int> memory_accesses = {1000, 1008, 1016, 1024, 2048, 2048, 1016};
    
    cout << "{\"status\": \"C++ Backend Started Successfully\"}" << endl;
    
    for (int addr : memory_accesses) {
        predictor.record_access(addr);
        
        string result = lru_cache.get(addr);
        bool is_hit = (result != "MISS");
        
        if (!is_hit) {
            lru_cache.put(addr, "MEMORY_BLOCK");
        }
        
        // print out json for the python dashboard to capture
        cout << "{\"event\": \"access\", \"address\": " << addr 
             << ", \"hit\": " << (is_hit ? "true" : "false") 
             << ", \"stride_info\": " << predictor.to_json() << "}" << endl;
                  
        Sleep(1500); 
    }
    
    return 0;
}
