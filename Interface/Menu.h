#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H

#include <iostream>
#include <string>

#include "../Classes/Graph.h"
#include "../Functions/read_data.h"

#include <string>
/**
 * @brief A UI Menu class.
 *
 * This is a class that provides the program's UI menu.
 */
class Menu {
public:
    /**
     * Provides the main menu.
     */
    void mainMenu();
private:
    Graph graph;
    bool dataReady = false;

    /**
     * Reads the data (stations + railways) from a desired network.
     */
    void readData();

    /**
     * Provides the submenu that gives access to basic metrics about the train network.
     */
    void basicMetrics();
    /**
     * Provides the submenu that gives access to information that can help optimize network operating costs.
     */
    void costOptimization();
    /**
     * Provides the submenu that gives access to information on network reliability.
     */
    void networkReliability();

    /**
     * Provides information on the maximum number of trains that can travel simultaneously between two given stations,
     * calling the necessary algorithm.
     */
    void basicMetrics1();
    /**
     * Provides information on what are the pairs of stations that require the most amount of trains when taking full
     * advantage of the network capacity, calling the necessary algorithm.
     */
    void basicMetrics2();
    /**
     * Provides a top-k municipalities and districts regarding their transportation needs, calling the
     * necessary algorithms.
     */
    void basicMetrics3();
    /**
     * Reports the maximum number of trains that can arrive at a given station, taking into consideration the entire
     * railway grid, calling the necessary algorithms.
     */
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

    /**
     * Prompts the user to remove one or more railway segments, thus generating a reduced connectivity network. Provides
     * information on the maximum number of trains that can travel between two given stations in that network, calling the
     * necessary algorithm.
     */
    void networkReliability1();
    /**
     * Provides a top-k of the stations that are more affected by a given segment failure, calling the necessary algorithm.
     */
    void networkReliability2();

    std::string stationsFile;
    std::string networkFile;
};

#endif //DA_PROJ1_MENU_H
