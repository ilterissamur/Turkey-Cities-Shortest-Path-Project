#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>

class City
{
private:
    std::string name;
    int numOfNeighbors;
    std::unordered_map<std::string, int> neighbors;

public:
    City();
    City(std::string name, std::vector<std::string> neighbors, int n);
    void setNeighbors(std::unordered_map<std::string, int> neighbors);
    std::unordered_map<std::string, int> getNeigbors();
    std::vector<std::string> getNeighborNames();
    std::string getName();
    int getNumOfNeighbors();
    void printNeighbours();
};