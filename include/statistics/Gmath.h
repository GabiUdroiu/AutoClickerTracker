#pragma once
#include <vector>

class Gmath {
public:
    static double Mean(const std::vector<int>&);
    static double Median(std::vector<int>&);
    static int Mode(const std::vector<int>&);
    static int Range(const std::vector<int>&);
    static double Skewness(const std::vector<int>&);
    static double Kurtosis(const std::vector<int>&);
    static double SD(const std::vector<int>&); // StandardDeviation
    static double HighestCPS(const std::vector<int>&);

    static std::vector<int> FilterDelays(const std::vector<int>&, int); 
};

