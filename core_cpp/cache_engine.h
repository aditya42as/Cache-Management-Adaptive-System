#ifndef CACHE_ENGINE_H
#define CACHE_ENGINE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

// My node struct for the DLL 
struct CacheNode {
    int key;
    string value;
    int vitality_score; // used for the adaptive aging thing
    
    CacheNode(int k, string v) : key(k), value(v), vitality_score(100) {}
};

class CacheEngine {
protected:
    int capacity;
    list<CacheNode> dll; // doubly linked list for O(1) stuff
    unordered_map<int, list<CacheNode>::iterator> cache_map; // map to find nodes fast
    
public:
    CacheEngine(int cap);
    virtual ~CacheEngine() = default;
    
    virtual string get(int key) = 0;
    virtual void put(int key, string value) = 0;
    
    // bit-shift math to decrease score
    void decay_vitality();
};

class LRUCache : public CacheEngine {
public:
    LRUCache(int cap);
    string get(int key) override;
    void put(int key, string value) override;
};

class FIFOCache : public CacheEngine {
public:
    FIFOCache(int cap);
    string get(int key) override;
    void put(int key, string value) override;
};

#endif
