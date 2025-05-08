#include "ClickProcessor.h"
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

ClickProcessor::ClickProcessor()
    : startTime(high_resolution_clock::now()), clickCounter(0) {}

int ClickProcessor::getTickIndex(double ms) {
    return (int)(floor(ms / 50.0));
}

void ClickProcessor::recordClick() {
    auto now = high_resolution_clock::now();
    double elapsedMs = duration_cast<milliseconds>(now - startTime).count();
    int currentTick = getTickIndex(elapsedMs);
    lastClickTime = now;  // track last click time
    
    int tickDelta = currentTick;
    if(!tickIndices.empty()) {
        int lastTick = tickIndices.back();
        tickDelta = currentTick - lastTick;
    }

    tickIndices.push_back(currentTick);
    clickTimestamps.push_back(elapsedMs);

    if(tickDelta >= 0) {
        delays.push_back(tickDelta);
    }

    ++clickCounter;
}

const vector<int>& ClickProcessor::getDelays() const {
    return delays;
}

const vector<int>& ClickProcessor::getTickIndices() const {
    return tickIndices;
}

double ClickProcessor::getCPS() {
    if(clickTimestamps.empty()) return 0;

    double now = duration_cast<milliseconds>(
        high_resolution_clock::now() - startTime
    ).count();

    // Remove old timestamps (older than 1 second)
    clickTimestamps.erase(
        std::remove_if(clickTimestamps.begin(), clickTimestamps.end(),
            [now](double t) { return now - t > 1000; }),
        clickTimestamps.end()
    );
    double cps = static_cast<double>(clickTimestamps.size());
    if(cps > maxCPS)
        maxCPS = cps;
    return cps;
}

int ClickProcessor::getClickCount() const {
    return clickCounter;
}

double ClickProcessor::getMaxCPS() const {return maxCPS;}

void ClickProcessor::reset() {
    delays.clear();
    tickIndices.clear();
    clickTimestamps.clear();
    clickCounter = 0;
    maxCPS = 0;
    startTime = high_resolution_clock::now();
}
