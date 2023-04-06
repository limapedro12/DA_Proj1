#ifndef DA_PROJ1_GRAPH_H
#define DA_PROJ1_GRAPH_H

#include <string>
#include <set>
#include <vector>
#include <string>
#include <limits>
#include <list>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <map>

#include "VertexEdge.h"

struct minCostReturn;

/**
 * @brief A graph class for a railway network.
 *
 * The Graph class is the "main" class of the program, since it contains all the objects that model the railway network.
 * It also comprehends all the algorithms necessary to perform the desired operations and calculations. As stated in
 * other places, the graph's nodes/vertexes are objects of the Station class, each one containing their adjacent railway
 * segments, represented by the Edge class.
 */
class Graph {
public:
    /**
     * Finds a Station (vertex) in the graph's vertex set.\n Time complexity: O(|V|).
     * @param name Name of the Station to be found
     * @return A pointer to the desired Station, nullptr if the station is not found
     */
    Station* findVertex(const std::string& name) const;
    /**
     * Tries to add a vertex (Station pointer) to the graph's vertex set, checking if it already exists.\n Time complexity: O(|V|).
     * @param station Pointer to the Station to be added
     * @return true if Station pointer is added, false if already is part of the vertex set
     */
    bool addVertex(Station* station);
    /**
     * Tries to remove an Edge (railway segment) whose ends are in the desired stations and is of the desired type
     * (STANDARD/ALFA).\n Time Complexity: O(|E|).
     * @param orig Pointer to one of the segment ends Station
     * @param dest Pointer to one of the segment ends Station
     * @param alfa Whether the segment to remove is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return Bool if removal is successful, false otherwise
     */
    bool removeEdge(Station* orig, Station* dest, bool alfa);

    /**
     * Adds an edge to the sourc Station adjacent edges leading to the dest Station, with the desired weight and type of
     * segment.\n Time Complexity: O(|V|).
     * @param sourc Pointer to the origin Station
     * @param dest Pointer to the destination Station
     * @param w Weight of the segment (capacity in terms of number of trains it can handle simultaneously)
     * @param alfa Whether the segment is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return Pointer to the added Edge, nullptr if one or more of the Stations is/are not found
     */
    Edge* addEdge(Station* sourc, Station* dest, double w, bool alfa);
    /**
     * Tries to add a bidirectional edge with ends on the desired stations, with the desired wheight and type of segment.
     * \n Time Complexity: O(|V|).
     * @param sourc Pointer to the origin Station (this and dest are interchangeable)
     * @param dest Pointer to the destination Station (this and sourc are interchangeable)
     * @param w Weight of the segment (capacity in terms of number of trains it can handle simultaneously)
     * @param alfa Whether the segment is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return True if Edge is added, false otherwise (if one or more of the Stations is/are not found).
     */
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    /**
     * Graph's vertex set getter.\n Time Complexity: O(1).
     * @return A copy of the std::vector<Station*> vertexSet.
     */
    std::vector<Station*> getVertexSet() const;


    std::vector<Edge*> path(Station* source, Station* dest) const;
    double findBottleneck(std::vector<Edge*> path);
    Graph edmondsKarp(Station* source, Station* target);
    int maxFlow(Station* source, Station* target);
    int maxTrainsAtStation(Station* station);
    int cost(Station* source, Station* target);

    std::vector<Edge*> pathDijkstra(Station* source, Station* dest) const;
    std::pair<int, std::vector<Edge*>> minCost(Station* source, Station* target);
    Graph edmondsKarpMinCost(Station* source, Station* target, double costLimit);
    std::pair<int, double> maxTrainsMinCost(Station* source, Station* target, double costLimit);
    std::list<std::pair<Station*, Station*>> mostTrainsPair(std::map<District*, int>& districtflow, std::map<Municipality*, int>& municipalityflow);

private:
    std::vector<Station *> vertexSet;    // vertex set

    int findVertexIdx(const std::string& name) const;
    int costBFS(Station* source);
};

#endif //DA_PROJ1_GRAPH_H
