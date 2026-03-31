#ifndef STRIDE_PREDICTOR_H
#define STRIDE_PREDICTOR_H

#include <vector>
#include <string>

using namespace std;

class StridePredictor {
private:
    vector<int> accessHistory;
    int currentStride;

public:
    StridePredictor();
    void recordAccess(int address);
    int predictNext() const;
    string toJson() const;
    static string simulateBelady(const vector<int>& pages, int minFrames, int maxFrames);
};

#endif
