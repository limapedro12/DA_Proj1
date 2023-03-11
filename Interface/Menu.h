#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H

#include <iostream>
#include <string>

#include "../Classes/Graph.h"
#include "../Functions/read_data.h"

class Menu {
public:
    void mainMenu();
private:
    Graph graph;
    bool dataReady = false;

    void readData();
    void basicMetrics();
};

#endif //DA_PROJ1_MENU_H
