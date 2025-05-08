#include "Statistics/Gmath.h"
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

std::vector<int> Gmath::FilterDelays(const std::vector<int>& delays, int n) {
    std::vector<int> filteredDelays;
    for(int delay : delays) {
        if(delay < n) {
            filteredDelays.push_back(delay);
        }
    }
    return filteredDelays;
}

double Gmath::Mean(const vector<int>& data) {
    if(data.empty()) return 0;
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double Gmath::Median(vector<int>& data) {
    if (data.empty()) return 0;
    sort(data.begin(), data.end());
    size_t n = data.size();
    if(n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

int Gmath::Mode(const vector<int>& data) {
    if(data.empty()) return 0;
    unordered_map<int, int> frequency;
    for(int val : data) {
        frequency[val]++;
    }
    int mode = data[0];
    int maxCount = 0;
    for(const auto& entry : frequency) {
        if(entry.second > maxCount) {
            maxCount = entry.second;
            mode = entry.first;
        }
    }
    return mode;
}

int Gmath::Range(const vector<int>& data) {
    if(data.empty()) return 0;
    auto minMax = minmax_element(data.begin(), data.end());
    return *minMax.second - *minMax.first;
}

double Gmath::Skewness(const vector<int>& data) {
    if(data.size() < 3) return 0;
    double mean = Mean(data);
    double n = data.size();
    double numerator = 0;
    double denominator = 0;
    for(int val : data) {
        numerator += pow(val - mean, 3);
        denominator += pow(val - mean, 2);
    }
    double skewness = (n / ((n - 1) * (n - 2))) * (numerator / pow(denominator / n, 1.5));
    return skewness;
}

double Gmath::Kurtosis(const vector<int>& data) {
    if(data.size() < 4) return 0;
    double mean = Mean(data);
    double n = data.size();
    double fourthMoment = 0;
    double secondMoment = 0;
    for(int val : data) {
        fourthMoment += pow(val - mean, 4);
        secondMoment += pow(val - mean, 2);
    }
    double kurtosis = (n * (n + 1) * fourthMoment) / ((n - 1) * (n - 2) * (n - 3) * pow(secondMoment, 2)) - (3 * (n - 1) * (n - 1)) / ((n - 2) * (n - 3));
    return kurtosis;
}
//StandardDeviation == SD
double Gmath::SD(const vector<int>& data) {
    if(data.empty()) return 0;
    double mean = Mean(data);
    double sumOfSquares = 0;
    for(int val : data) {
        sumOfSquares += pow(val - mean, 2);
    }
    return sqrt(sumOfSquares / data.size());
}

double Gmath::HighestCPS(const vector<int>& delays) {
    std::vector<int> filteredDelays = FilterDelays(delays, 10);
    if(filteredDelays.empty()) return 0;

    double maxCPS = 0;
    int totalClicks = 0;
    double totalTime = 0;

    // Iterate over filtered delays and calculate CPS
    for(size_t i = 0; i < filteredDelays.size(); ++i) {
        totalClicks++;
        totalTime += filteredDelays[i] / 1000.0; // Convert to seconds

        double currentCPS = totalClicks / totalTime;
        maxCPS = std::max(maxCPS, currentCPS);
    }

    return maxCPS;
}
