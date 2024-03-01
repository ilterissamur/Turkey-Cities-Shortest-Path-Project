#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include "City.h"

class Graph
{
private:
    City selected;
    int numOfCities;
    std::vector<City> adjacencyList;

public:
    Graph();
    City selectCity(std::string name);
    void printCity();
    void kNearestCities();
    void shortestPath();
    int dist(std::string from, std::string to);
};