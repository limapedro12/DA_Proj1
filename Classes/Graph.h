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

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    Edge* addEdge(Station* sourc, Station* dest, double w, bool alfa);
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    std::vector<Station*> getVertexSet() const;

//    void createResidualGraph(const Graph& g);
    std::vector<Edge*> path(const std::string& source, const std::string& dest) const;
    double findBottleneck(std::vector<Edge*> path);
    Graph edmondsKarp(const std::string& source, const std::string& target);
    int maxFlow(const std::string& source, const std::string& target);
    int maxTrainsAtStation(Station* station);
    int cost(const std::string& source, const std::string& target);

    std::vector<Edge*> pathDijkstra(const std::string& source, const std::string& dest) const;
    std::pair<int, std::vector<Edge*>> minCost(const std::string& source, const std::string& target);
    std::pair<double, Graph>  edmondsKarpMinCost(const std::string& source, const std::string& target, double costLimit);
    std::pair<int, double> maxTrainsMinCost(const std::string& source, const std::string& target, double costLimit);

//    Graph copyGraph();
//    minCostReturn copyGraphHashSet();

private:
    std::vector<Station *> vertexSet;    // vertex set

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string& name) const;
    int costBFS(const std::string& source);
};

//struct minCostReturn {
//    Graph copy;
//    std::unordered_map<Edge*, Edge*> edgeMapNewToOld;
//    std::unordered_map<Edge*, Edge*> edgeMapOldToNew;
//};

#endif //DA_PROJ1_GRAPH_H
