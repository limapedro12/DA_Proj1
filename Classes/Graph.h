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

class Graph {
public:
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Station* findVertex(const std::string& name) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station* station);
    bool removeEdge(Station* orig, Station* dest, bool alfa);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    Edge* addEdge(Station* sourc, Station* dest, double w, bool alfa);
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    std::vector<Station*> getVertexSet() const;

//    void createResidualGraph(const Graph& g);
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
    std::list<std::pair<Station*, Station*>> mostTrainsPair();

private:
    std::vector<Station *> vertexSet;    // vertex set

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string& name) const;
    int costBFS(Station* source);
};

#endif //DA_PROJ1_GRAPH_H
