#pragma once
#include <vector>
#include <chrono>

class ClickProcessor {
public:
    ClickProcessor();
    void recordClick();
    void reset();
    const std::vector<int>& getDelays() const;
    const std::vector<int>& getTickIndices() const;
    int getClickCount() const;
    double getCPS();
    double getMaxCPS() const;
    

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::vector<int> delays;
    std::vector<int> tickIndices;
    std::vector<double> clickTimestamps;
    std::chrono::high_resolution_clock::time_point lastClickTime;
    int clickCounter;
    double maxCPS = 0;
    int getTickIndex(double);
};
