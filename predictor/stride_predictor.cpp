#include "stride_predictor.h"
#include <sstream>
#include <iostream>

StridePredictor::StridePredictor() : current_stride(0) {}

void StridePredictor::record_access(int address) {
    // calc the diff between current and last access
    if (!access_history.empty()) {
        current_stride = address - access_history.back();
    }
    access_history.push_back(address);
}

int StridePredictor::predict_next() const {
    if (access_history.empty()) return -1;
    return access_history.back() + current_stride;
}

string StridePredictor::to_json() const {
    // stringstream to build the json string
    ostringstream json;
    json << "{";
    json << "\"stride\": " << current_stride << ", ";
    json << "\"history_size\": " << access_history.size();
    if (!access_history.empty()) {
        json << ", \"last_access\": " << access_history.back();
        json << ", \"predicted_next\": " << predict_next();
    }
    json << "}";
    return json.str();
}

string StridePredictor::simulate_belady(const vector<int>& pages, int min_frames, int max_frames) {
    ostringstream result;
    result << "[\n";
    
    // loop different queue sizes to see fault rates
    for (int frames = min_frames; frames <= max_frames; ++frames) {
        int faults = 0; 
        
        result << "  {\"frames\": " << frames << ", \"faults\": " << faults << "}";
        if (frames < max_frames) result << ",\n";
    }
    result << "\n]";
    return result.str();
}
