#include "Analyzer.h"
#include "ClickProcessor.h"
#include "Gmath.h"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void Analyzer::analyze(const vector<int>& delays) {
    if(delays.empty()) return;

    int ones = 0, totalOnes = 0, maxOnes = 0;
    int zeros = 0, maxZeros = 0, zerosCount = 0;
    int sample = 0;
    double tickSum = 0;

    for(int delay : delays) {
        tickSum += delay;

        ++sample;

        if(delay == 1) {
            ++ones;
            ++totalOnes;
        } else {
            maxOnes = max(maxOnes, ones);
            ones = 0;
        }

        if(delay == 0) {
            ++zeros;
            ++zerosCount;
        } else {
            maxZeros = max(maxZeros, zeros);
            zeros = 0; //reset the consecutive sequence of zeros
        }
    }

    double tick = 0.0;
    for(int delay : delays) {
        if (delay < 10)
            tick += delay / 20.0;
    }

    maxOnes = max(maxOnes, ones);
    maxZeros = max(maxZeros, zeros);

    double avgTick = tickSum / delays.size();
    double avgCps = (sample + zerosCount) / tick;
    double consistency = ((double)(totalOnes) / delays.size()) * 100.0;

    double doubleClickPct = ((double)(count(delays.begin(), delays.end(), 0)) / delays.size()) * 100.0;

    cout << "Sample size: " << delays.size() << ": #debug# " << sample << endl;
    cout << "Average Tick Delay: " << avgTick << endl;
    cout << "Average CPS: " << avgCps << endl;
    if(maxOnes > 7) cout << "(Uncertain because high consecutive ones)" << endl;
    cout << "Doubleclicks: " << count(delays.begin(), delays.end(), 0) << endl;
    cout << "Total ones: " << totalOnes << endl;
    cout << "Max Consecutive Ones: " << maxOnes << endl;
    cout << "Max Consecutive Zeros: " << maxZeros << endl;
    cout << "Consistency: " << consistency << "%" << endl;
    cout << "Percentage Doubleclicks: " << doubleClickPct << "%" << endl;

    //Using GMATH class
    vector<int> filteredDelays = Gmath::FilterDelays(delays, 10);

    vector<int> delaysCopy = delays; //copy to prevent modify the original
    double mean = Gmath::Mean(delaysCopy);
    double median = Gmath::Median(delaysCopy);
    int mode = Gmath::Mode(delaysCopy);
    int range = Gmath::Range(filteredDelays);
    double skewness = Gmath::Skewness(delaysCopy);
    double kurtosis = Gmath::Kurtosis(delaysCopy);
    double stdDev = Gmath::SD(delaysCopy); //StandardDeviation
    double highestCPS = Gmath::HighestCPS(delaysCopy);

    cout << "Mean: " << mean << endl;
    cout << "Median: " << median << endl;
    cout << "Mode: " << mode << endl;
    cout << "Range: " << range << endl;
    cout << "Skewness: " << skewness << endl;
    cout << "Kurtosis: " << kurtosis << endl;
    cout << "Standard Deviation: " << stdDev << endl;
}
