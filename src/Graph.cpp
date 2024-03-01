#include "Graph.h"

Graph::Graph()
{
    this->numOfCities = 0;
    int numberOfNeighbors = 0;

    //------------------------------------------------------------------------------------------------ read 1st file

    std::ifstream file;
    file.open("adjacent_cities.txt", std::ios::in);

    std::string line;
    std::string name;
    std::string temp;
    std::vector<std::string> neighbourCities;

    if (!file.is_open())
    {
        std::cerr << "Error at opening adjacent_cities.txt" << std::endl;
        exit(1);
    }

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, name, ',');

        while (std::getline(iss, temp, ','))
        {
            neighbourCities.push_back(temp);
            numberOfNeighbors++;
        }

        adjacencyList.push_back(City(name, neighbourCities, numberOfNeighbors));
        this->numOfCities++;
        numberOfNeighbors = 0;
        neighbourCities.clear();
    }

    file.close();

    //------------------------------------------------------------------------------------------------ read 2nd file

    file.open("city_distances.txt", std::ios::in);

    if (!file.is_open())
    {
        std::cerr << "Error at opening city_distances.txt" << std::endl;
        exit(1);
    }

    std::string cities;
    std::getline(file, cities);

    int i = 0;

    std::unordered_map<std::string, int> neighbours;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::getline(iss, temp, ';');
        std::getline(iss, temp, ';');

        std::string tempCities = cities;
        std::istringstream issCities(tempCities);
        std::getline(issCities, name, ';');
        std::getline(issCities, name, ';');

        neighbourCities = adjacencyList[i].getNeighborNames();
        int size = neighbourCities.size();

        while (std::getline(iss, temp, ';'))
        {
            std::getline(issCities, name, ';');
            for (int k = 0; k < size; k++)
            {
                if (name == neighbourCities[k])
                {
                    neighbours[name] = stoi(temp);
                }
            }
        }

        adjacencyList[i].setNeighbors(neighbours);
        neighbours.clear();
        i++;
    };
}

City Graph::selectCity(std::string name)
{
    for (int i = 0; i < numOfCities; i++)
    {
        if (adjacencyList[i].getName() == name)
        {
            selected = adjacencyList[i];
            return adjacencyList[i];
        }
    }

    std::cout << "There is no exist " << name << " city please enter again: ";
    std::cin >> name;
    selected = selectCity(name);
    return selected;
}

void Graph::printCity()
{
    if (selected.getName() == "")
    {
        std::cout << "First you must select a city" << std::endl;
        std::string name;
        std::cout << "Enter city: ";
        std::cin >> name;
        system("cls");
        selectCity(name);
    }

    selected.printNeighbours();
    std::cout << "\n";
}

auto cmp = [](const std::pair<std::string, int> a, const std::pair<std::string, int> b)
{ return a.second > b.second; };

void Graph::kNearestCities()
{
    if (selected.getName() == "")
    {
        std::cout << "First you must select a city" << std::endl;
        std::string name;
        std::cout << "Enter city: ";
        std::cin >> name;
        system("cls");
        selectCity(name);
    }

    int k;
    std::cout << "Enter k: ";
    std::cin >> k;
    system("cls");

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> pq(cmp);
    std::unordered_map<std::string, int> result;
    int counter = 0;

    for (auto it : selected.getNeigbors())
    {
        pq.push(it);
    }

    while (counter != k)
    {
        std::pair<std::string, int> topCity = pq.top();
        pq.pop();

        if (result.find(topCity.first) != result.end())
        {
            continue;
        }
        else
        {
            result[topCity.first] = topCity.second;
            counter++;

            for (int i = 0; i < numOfCities; i++)
            {
                if (adjacencyList[i].getName() == topCity.first)
                {
                    for (auto neighbor : adjacencyList[i].getNeigbors())
                    {
                        if (result.find(neighbor.first) != result.end() || neighbor.first == selected.getName())
                        {
                            continue;
                        }
                        else
                        {
                            pq.push(std::make_pair(neighbor.first, topCity.second + neighbor.second));
                        }
                    }
                }
            }
        }
    }

    for (auto it : result)
    {
        std::cout << it.first << " " << it.second << std::endl;
    }

    std::cout << "\n";
}
int Graph::dist(std::string from, std::string to)
{
    for (int i = 0; i < numOfCities; i++)
    {
        if (adjacencyList[i].getName() == from)
        {
            for (auto x : adjacencyList[i].getNeigbors())
            {
                if (x.first == to)
                {
                    return x.second;
                }
            }
        }
    }
}

void Graph::shortestPath()
{
    if (selected.getName() == "")
    {
        std::cout << "First you must select a city" << std::endl;
        std::string name;
        std::cout << "Enter city: ";
        std::cin >> name;
        system("cls");
        selectCity(name);
    }

    std::string goal;
    std::cout << "Enter goal city: ";
    std::cin >> goal;
    system("cls");

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> pq(cmp);
    std::unordered_map<std::string, int> costs;
    std::unordered_map<std::string, std::string> previousCity;

    std::string start = selected.getName();
    std::string tempStart = start;
    costs[start] = 0;

    for (int i = 0; i < numOfCities; i++)
    {
        costs[adjacencyList[i].getName()] = INT_MAX;
    }

    pq.push(std::make_pair(start, 0));

    while (!pq.empty())
    {
        std::pair<std::string, int> topCity = pq.top();
        pq.pop();

        if (topCity.first == goal)
        {
            break;
        }

        for (int i = 0; i < numOfCities; i++)
        {
            if (adjacencyList[i].getName() == topCity.first)
            {
                for (std::pair<std::string, int> neighbor : adjacencyList[i].getNeigbors())
                {
                    if (topCity.second + neighbor.second < costs[neighbor.first])
                    {
                        costs[neighbor.first] = topCity.second + neighbor.second;
                        previousCity[neighbor.first] = topCity.first;
                        pq.push(std::make_pair(neighbor.first, topCity.second + neighbor.second));
                    }
                }
            }
        }
    }

    std::vector<std::string> path;
    std::string current = goal;

    while (current != start && previousCity.find(current) != previousCity.end())
    {
        path.insert(path.begin(), current);
        current = previousCity[current];
    }

    int size = path.size();
    path.insert(path.begin(), start);
    int d = 0;
    for (int i = 0; i < size; i++)
    {
        d += dist(path[i], path[i + 1]);
        std::cout << path[i] << "(" << d << ") --> ";
    }

    std::cout << goal << " ";
    std::cout << "\n";
}