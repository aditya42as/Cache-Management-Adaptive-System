#include "cache_engine.h"

CacheEngine::CacheEngine(int cap) : capacity(cap) {}

void CacheEngine::decay_vitality() {
    // using right shift instead of divide by 2, saves cpu cycles
    for (auto& node : dll) {
        node.vitality_score = node.vitality_score >> 1; 
    }
}

LRUCache::LRUCache(int cap) : CacheEngine(cap) {}

string LRUCache::get(int key) {
    if (cache_map.find(key) == cache_map.end()) {
        return "MISS"; 
    }
    // bring to front because it was just used
    dll.splice(dll.begin(), dll, cache_map[key]);
    
    // reset vitality back to full
    cache_map[key]->vitality_score = 100;
    
    return cache_map[key]->value;
}

void LRUCache::put(int key, string value) {
    if (cache_map.find(key) != cache_map.end()) {
        cache_map[key]->value = value;
        cache_map[key]->vitality_score = 100;
        dll.splice(dll.begin(), dll, cache_map[key]);
        return;
    }
    
    // delete the last element if cache is full
    if (dll.size() >= capacity) {
        int lru_key = dll.back().key;
        cache_map.erase(lru_key);
        dll.pop_back();
    }
    
    dll.emplace_front(key, value);
    cache_map[key] = dll.begin();
}

FIFOCache::FIFOCache(int cap) : CacheEngine(cap) {}

string FIFOCache::get(int key) {
    if (cache_map.find(key) == cache_map.end()) {
        return "MISS";
    }
    return cache_map[key]->value;
}

void FIFOCache::put(int key, string value) {
    if (cache_map.find(key) != cache_map.end()) {
        cache_map[key]->value = value;
        return;
    }
    
    if (dll.size() >= capacity) {
        int oldest_key = dll.back().key;
        cache_map.erase(oldest_key);
        dll.pop_back();
    }
    
    dll.emplace_front(key, value);
    cache_map[key] = dll.begin();
}
