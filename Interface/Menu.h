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

    void costOptimization1();
    void costOptimization2();
    void costOptimization3();

    void networkReliability1();
    void networkReliability2();

    std::string stationsFile;
    std::string networkFile;
};

#endif //DA_PROJ1_MENU_H
