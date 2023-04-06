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

/**
 * @brief Class that uses a graph to represents the railway network.
 *
 * This graph is implemented using an adjacency list.
 * Each vertex represents a station, and each edge represents a connection between two stations.
 * The class includes the necessary methods for manipulating the graph data structure and to solve the requested problems.
 */
class Graph {
public:
    /**
     * Method to find a vertex with a given its name.
     *
     * Temporal Complexity: O(V), where V is the number of stations in the graph
     *
     * @param name
     * @return Station pointer
     */
    Station* findVertex(const std::string& name) const;

    /**
     *  Adds a vertex with to the graph, given a pointer to the station.
     *  Returns true if successful, and false if a vertex with that content already exists.
     *
     *  Temporal Complexity: O(1)
     *
     *  @param station
     *  @return true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station* station);

    /**
     * Removes a vertex with a given content or info (in) from a graph (this).
     * Returns true if successful, and false if a vertex with that content does not exist.
     *
     * Temporal Complexity: O(degree(v)), where degree(v) is the number of edges leaving the origin vertex v
     *
     * @param orig
     * @param dest
     * @param alfa
     * @return true if successful, and false if a vertex with that content does not exist.
     */
    bool removeEdge(Station* orig, Station* dest, bool alfa);

    /**
     * Adds an edge to a graph, given the pointers of the source and the
     * destination vertices and the edge weight (w).
     * Returns a pointer to the newly created edge if successful, and nullptr otherwise.
     *
     * Temporal Complexity: O(1)
     *
     * @param sourc
     * @param dest
     * @param w
     * @param alfa
     * @return a pointer to the newly created edge if successful, and nullptr otherwise.
     */
    Edge* addEdge(Station* sourc, Station* dest, double w, bool alfa);

    /**
     * Adds an bidirectional edge to the graph, by creating two directed edges,
     * given the pointers of its two ends and the edge weight (w).
     * Returns true if successful, and false if the one of the endpoints does not exist.
     *
     * Temporal Complexity: O(1)
     *
     * @param sourc
     * @param dest
     * @param w
     * @param alfa
     * @return true if successful, and false if the one of the endpoints does not exist.
     */
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    /**
     * Returns a vector with all the vertices of a graph (this).
     *
     * Temporal Complexity: O(1)
     */
    std::vector<Station*> getVertexSet() const;

//    void createResidualGraph(const Graph& g);
    /**
     * Returns a vector of Edge pointers with the path from a source vertex to a destination vertex, which has the least amount of Edges.
     * For that it uses the BFS algorithm to find the path.
     *
     * Temporal Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param dest
     * @return vector of Edge
     */
    std::vector<Edge*> path(Station* source, Station* dest) const;

    /**
     * Given a path, returns the bottleneck of that path, which is the minimum capacity of all the edges in the path.
     *
     * Temporal Complexity: O(P), where P is the number of edges in the path
     *
     * @param path
     * @return the bottleneck of that path
     */
    double findBottleneck(std::vector<Edge*> path);

    /**
     * Runs the Edmonds-Karp algorithm to find the maximum flow from a source vertex to a destination vertex.
     * For that this method uses the path() method to find the path with the least amount of edges.
     * Returns the residual graph after the algorithm has finished.
     *
     * Temporal Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @return the residual graph
     */
    Graph edmondsKarp(Station* source, Station* target);

    /**
     * Uses the edmondsKarp() method to find residual graph associated with a certain source and destination vertex.
     * Then, it uses the residual graph to find the maximum flow from the source to the destination.
     * For that it sums the flow of all the edges leaving the source vertex.
     * It also has a boolean parameter, which if true, prints all the paths in the residual graph which have a flow greater than 0(printFlow()).
     *
     * Temporal Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @param print
     * @return maximum flow from the source to the destination
     */
    int maxFlow(Station* source, Station* target, bool print = false);

    /**
     * This method creates a new temporary graph, which is a copy of the original graph.
     * Then it adds a new vertex to the temporary graph, which will be the source vertex.
     * After that we add a new edge from the temporary vertex to each vertex in the original graph, except the destination vertex.
     * Then we run the Edmonds-Karp algorithm(edmondsKarp() method) on the temporary graph, with the temporary vertex as the source and the destination vertex as the destination,
     * and we return the maximum flow found.
     *
     * Temporal Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
     *
     * @param destStation
     * @return number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid.
     */
    int maxTrainsAtStation(Station* destStation);

    /**
     * Returns a vector of Edge pointers with the path from a source vertex to a destination vertex, which has the lowest cost.
     * For this it uses the Dijkstra algorithm, but instead of a priority queue it uses a set.
     *
     * Temporal Complexity: O((V+E)*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param dest
     * @return
     */
    std::vector<Edge*> pathDijkstra(Station* source, Station* dest) const;

    /**
     * Runs the Dijkstra algorithm to find the minimum cost from a source vertex to a destination vertex.
     * For that this method uses the pathDijkstra() method to find the path with the lowest cost.
     * Returns the minimum cost and the corresponding path.
     *
     * Temporal Complexity: O((V+E)*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @return the minimum cost and the corresponding path
     */
    std::pair<int, std::vector<Edge*>> minCost(Station* source, Station* target);

    /**
     * Runs a variation of Edmonds-Karp algorithm to find the maximum flow from a source vertex to a destination vertex
     * The variation is that the algorithm uses the Dijkstra Algorithm to find the augmentation paths, instead of the BFS,
     * so that the residual graph obtained is the residual graph with the lowest possible cost,
     * and stops when the cost of the path is greater than a given cost limit.
     * For that this method uses the pathDijkstra() method to find the path with the lowest cost.
     * Returns the residual graph after the algorithm has finished.
     *
     * Temporal Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @param costLimit
     * @return maximum flow from the source to the destination
     */
    Graph edmondsKarpMinCost(Station* source, Station* target, double costLimit);

    /**
     * Uses the edmondsKarpMinCost() method without cost limit(i.e. with the costLimit set to numeric_limits<double>::max()) to find residual graph associated with a certain source and destination vertex.
     * Then, it uses the residual graph to find the the cost of the network running at its maximum capacity from the source to the destination.
     * For that it uses the method costBFS() to find the cost of the residual graph.
     * It also has a boolean parameter, which if true, prints all the paths in the residual graph which have a flow greater than 0(printFlow()).
     *
     * Temporal Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @param print
     * @return the cost of the network running at its maximum capacity from the source to the destination
     */
    int cost(Station* source, Station* target, bool print = false);

    /**
     * Uses the edmondsKarpMinCost() method to find residual graph associated with a certain source and destination vertex and specified cost limit.
     * Then, it uses the residual graph to find the the flow from the source to the destination in the residual graph
     * and the number of trains that can be sent from the source to the destination without exceeding the cost limit.
     * For the flow it sums the flow of all the edges leaving the source vertex,
     * and for the cost it iterates through all the edges in the residual graph and sums the cost of all the edges with a flow greater than 0.
     * It also has a boolean parameter, which if true, prints all the paths in the residual graph which have a flow greater than 0(printFlow()).
     *
     * Temporal Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @param costLimit
     * @param print
     * @return
     */
    std::pair<int, double> maxTrainsMinCost(Station* source, Station* target, double costLimit, bool print = false);
    std::list<std::pair<Station*, Station*>> mostTrainsPair();

    /**
     * Prints the origin, the destination and the flow of all the edges in the graph, which have a flow greater than 0.
     *
     * Temporal Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph.
     */
    void printFlow();

private:
    /**
     * vector of pointers to all station(vertices) in the graph
     */
    std::vector<Station *> vertexSet;    // vertex set

    /**
     * Private method that returns the cost of a graph, which is the sum of the cost of all the edges in the graph with a flow greater than 0.
     *
     * Temporal Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph.
     *
     * @param source
     * @return cost of the graph
     */
    int costBFS(Station* source);
};

#endif //DA_PROJ1_GRAPH_H
