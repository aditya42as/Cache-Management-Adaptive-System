#include "stride_predictor.h"
#include <sstream>
#include <iostream>

StridePredictor::StridePredictor() {
    currentStride = 0;
}

void StridePredictor::recordAccess(int address) {
    if (accessHistory.empty() == false) {
        currentStride = address - accessHistory.back();
    }
    
    accessHistory.push_back(address);
}

int StridePredictor::predictNext() const {
    if (accessHistory.empty() == true) {
        int emptyResult = -1;
        return emptyResult;
    }
    
    int nextAddress = accessHistory.back() + currentStride;
    return nextAddress;
}

string StridePredictor::toJson() const {
    ostringstream jsonString;
    jsonString << "{";
    jsonString << "\"stride\": " << currentStride << ", ";
    
    int historySize = accessHistory.size();
    jsonString << "\"history_size\": " << historySize;
    
    if (accessHistory.empty() == false) {
        int lastAccess = accessHistory.back();
        jsonString << ", \"last_access\": " << lastAccess;
        
        int nextPred = predictNext();
        jsonString << ", \"predicted_next\": " << nextPred;
    }
    
    jsonString << "}";
    
    string finalString = jsonString.str();
    return finalString;
}

string StridePredictor::simulateBelady(const vector<int>& pages, int minFrames, int maxFrames) {
    ostringstream resultStream;
    resultStream << "[\n";
    
    for (int frames = minFrames; frames <= maxFrames; frames++) {
        int faults = 0; 
        
        resultStream << "  {\"frames\": " << frames << ", \"faults\": " << faults << "}";
        
        if (frames < maxFrames) {
            resultStream << ",\n";
        }
    }
    
    resultStream << "\n]";
    
    string finalResult = resultStream.str();
    return finalResult;
}
