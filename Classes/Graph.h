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
     * Finds a Station (vertex) in the graph's vertex set.
     * 
     * Time complexity: O(V) where V is the number of stations(vertices) in the graph
     * 
     * @param name Name of the Station to be found
     * @return A pointer to the desired Station, nullptr if the station is not found
     */
    Station* findVertex(const std::string& name) const;
    /**
     * Tries to add a vertex (Station pointer) to the graph's vertex set, checking if it already exists.
     * 
     * Time complexity: O(1)
     * 
     * @param station Pointer to the Station to be added
     * @return true if Station pointer is added, false if already is part of the vertex set
     */
    bool addVertex(Station* station);
    /**
     * Tries to remove an Edge (railway segment) whose ends are in the desired stations and is of the desired type
     * (STANDARD/ALFA).
     * 
     * Time Complexity: O(degree(v)), where degree(v) is the number of edges leaving the origin vertex v
     * 
     * @param orig Pointer to one of the segment ends Station
     * @param dest Pointer to one of the segment ends Station
     * @param alfa Whether the segment to remove is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return Bool if removal is successful, false otherwise
     */
    bool removeEdge(Station* orig, Station* dest, bool alfa);

    /**
     * Adds an edge to the sourc Station adjacent edges leading to the dest Station, with the desired weight and type of
     * segment.
     * 
     * Time Complexity: O(1)
     * 
     * @param sourc Pointer to the origin Station
     * @param dest Pointer to the destination Station
     * @param w Weight of the segment (capacity in terms of number of trains it can handle simultaneously)
     * @param alfa Whether the segment is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return Pointer to the newly added Edge, nullptr if one or more of the Stations is/are not found
     */
    Edge* addEdge(Station* sourc, Station* dest, double w, bool alfa);
    /**
     * Tries to add a bidirectional edge with ends on the desired stations, with the desired wheight and type of segment.
     * The method does this by adding two edges, one from sourc to dest and another from dest to sourc.
     * 
     * Time Complexity: O(1)
     * 
     * @param sourc Pointer to the origin Station (this and dest are interchangeable)
     * @param dest Pointer to the destination Station (this and sourc are interchangeable)
     * @param w Weight of the segment (capacity in terms of number of trains it can handle simultaneously)
     * @param alfa Whether the segment is of type STANDARD (false) or ALFA PENDULAR (true)
     * @return True if Edge is added, false otherwise (if one or more of the Stations is/are not found).
     */
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    /**
     * Graph's vertex set getter.
     * 
     * Time Complexity: O(1).
     * 
     * @return A copy of the std::vector<Station*> vertexSet.
     */
    std::vector<Station*> getVertexSet() const;
    
    /**
     * Returns a vector of Edge pointers with the path from a source vertex to a destination vertex, which has the least amount of Edges.
     * For that it uses the BFS algorithm to find the path.
     *
     * Time Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param dest
     * @return vector of Edge
     */
    std::vector<Edge*> path(Station* source, Station* dest) const;

    /**
     * Given a path, returns the bottleneck of that path, which is the minimum capacity of all the edges in the path.
     *
     * Time Complexity: O(P), where P is the number of edges in the path
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
     * Time Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O(V*E^2), where V is the number of stations and E is the number of edges in the graph
     *
     * @param destStation
     * @return number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid.
     */
    int maxTrainsAtStation(Station* destStation);

    /**
     * Returns a vector of Edge pointers with the path from a source vertex to a destination vertex, which has the lowest cost.
     * For this it uses the Dijkstra algorithm, but instead of a priority queue it uses a set.
     *
     * Time Complexity: O((V+E)*log(V)), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O((V+E)*log(V)), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
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
     * Time Complexity: O(V*E^2*log(V)), where V is the number of stations and E is the number of edges in the graph
     *
     * @param source
     * @param target
     * @param costLimit
     * @param print
     * @return
     */
    std::pair<int, double> maxTrainsMinCost(Station* source, Station* target, double costLimit, bool print = false);
    std::list<std::pair<Station*, Station*>> mostTrainsPair();
    void topK(std::map<std::string, int> &districtFlow, std::map<std::string, int> &municipalityFlow);

    /**
     * Prints the origin, the destination and the flow of all the edges in the graph, which have a flow greater than 0.
     *
     * Time Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph.
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
     * Time Complexity: O(V+E), where V is the number of stations and E is the number of edges in the graph.
     *
     * @param source
     * @return cost of the graph
     */
    int costBFS(Station* source);
};

#endif //DA_PROJ1_GRAPH_H
