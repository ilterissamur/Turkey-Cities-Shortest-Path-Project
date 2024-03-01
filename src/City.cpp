#include "City.h"

City::City()
{
    this->name = "";
}

City::City(std::string name, std::vector<std::string> neighbors, int n)
{
    this->name = name;
    this->numOfNeighbors = n;

    for (int i = 0; i < numOfNeighbors; i++)
    {
        std::string neighbor = neighbors[i];
        this->neighbors[neighbor] = 0;
    }
}

void City::setNeighbors(std::unordered_map<std::string, int> neighbors)
{
    this->neighbors = neighbors;
}

std::unordered_map<std::string, int> City::getNeigbors()
{
    return neighbors;
}

std::vector<std::string> City::getNeighborNames()
{
    std::vector<std::string> neighborNames;
    auto iterator = neighbors.begin();

    while (iterator != neighbors.end())
    {
        neighborNames.push_back(iterator->first);
        iterator++;
    }

    return neighborNames;
}

std::string City::getName()
{
    return name;
}

int City::getNumOfNeighbors()
{
    return numOfNeighbors;
}

void City::printNeighbours()
{
    std::cout << "Selected City: " << name << std::endl;
    std::cout << std::setw(20) << std::left << "Neighbor City" << std::setw(20) << std::left << "Distance" << std::endl;
    auto it = neighbors.begin();
    for (int i = 0; i < numOfNeighbors; i++)
    {
        std::cout << std::setw(20) << std::left << it->first << std::setw(20) << std::left << it->second << " ";
        std::cout << "\n";
        it++;
    }
}
