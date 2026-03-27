#ifndef STRIDE_PREDICTOR_H
#define STRIDE_PREDICTOR_H

#include <vector>
#include <string>

using namespace std;

class StridePredictor {
private:
    vector<int> access_history;
    int current_stride;

public:
    StridePredictor();
    
    // save the block address
    void record_access(int address);
    
    // guess the next address based on difference
    int predict_next() const;
    
    // make it json so python can parse it easily
    string to_json() const;
    
    // test belady anomaly curve
    static string simulate_belady(const vector<int>& pages, int min_frames, int max_frames);
};

#endif
