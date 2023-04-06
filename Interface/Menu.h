#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H

#include <iostream>
#include <string>

#include "../Classes/Graph.h"
#include "../Functions/read_data.h"

#include <string>

class Menu {
public:
    void mainMenu();
private:
    Graph graph;
    bool dataReady = false;

    void readData();
    void basicMetrics();
    void costOptimization();
    void networkReliability();

    void basicMetrics1();
    void basicMetrics2();
    void basicMetrics3();
    void basicMetrics4();

    /**
     * Reports the minimum cost of operating all trains between two stations, being the railway network at its maximum capacity.
     */
    void costOptimization1();

    /**
     * Provides the path with the minimum cost between two stations
     */
    void costOptimization2();

    /**
     * Provides information about how many trains can be operated between two stations, given a cost limit.
     */
    void costOptimization3();

    void networkReliability1();
    void networkReliability2();

    std::string stationsFile;
    std::string networkFile;
};

#endif //DA_PROJ1_MENU_H
