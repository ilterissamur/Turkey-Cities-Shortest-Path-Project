#include <iostream>
#include "Graph.h"

int displayMenu();

int main()
{
    Graph g;
    int selection = displayMenu();

    while (selection != 5)
    {
        system("cls");

        if (selection == 1)
        {
            std::string name;
            std::cout << "Enter city: ";
            std::cin >> name;
            system("cls");
            g.selectCity(name);
        }
        else if (selection == 2)
        {
            g.printCity();
        }
        else if (selection == 3)
        {
            g.kNearestCities();
        }
        else if (selection == 4)
        {
            g.shortestPath();
        }

        selection = displayMenu();
    }

    return 0;
}

int displayMenu()
{
    int selection;

    std::cout << "1- Select City" << std::endl;
    std::cout << "2- Print Selected City" << std::endl;
    std::cout << "3- List K Closest Cities" << std::endl;
    std::cout << "4- Find Shortest Path" << std::endl;
    std::cout << "5- Exit" << std::endl;

    std::cout << "Choose your selection: ";
    std::cin >> selection;

    while (selection < 1 || selection > 5)
    {
        std::cout << "Wrong selection, please select again: ";
        std::cin >> selection;
    }

    return selection;
}
