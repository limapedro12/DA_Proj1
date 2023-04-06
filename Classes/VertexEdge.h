#ifndef DA_PROJ1_StationEDGE_H
#define DA_PROJ1_StationEDGE_H

#include <iostream>
#include <vector>
#include <string>

#include "Municipality.h"
#include "District.h"

class Edge;
class Municipality;
class District;

/**
 * @brief A class that represents a Station, being a node of the network graph.
 *
 * Given that we represent the railway network as a graph, the stations are the graph's nodes.\n
 * A Station is represented by its name, pointers to its District and its Municipality, its Township (Parish - Freguesia)
 * and the line it belongs to (North Line, Minho Line...). Contains its adjacent railway segments.\n
 * Note: all the methods time complexity is O(1), except where specified.
 */
class Station {
public:
    /**
     * Constructor for Station
     * @param name String with the Station's name
     * @param district Pointer to the Station's District
     * @param municipality Pointer to the Station's Municipality
     * @param township String with the Station's Township name
     * @param line String with the Station's line name
     */
    Station(const std::string& name, District* district, Municipality* municipality, const std::string& township, const std::string& line);
    /**
     * Station's District pointer getter.
     * @return Pointer to the Station's District.
     */
    District *getDistrict() const;
    /**
     * Station's District setter.
     * @param district District pointer
     */
    void setDistrict(District *district);
    /**
     * Station's Municipality getter.
     * @return Pointer to the Station's Municipality.
     */
    Municipality *getMunicipality() const;
    /**
     * Station's Municipality setter.
     * @param municipality Municipality pointer
     */
    void setMunicipality(Municipality *municipality);
    /**
     * Station's line getter.
     * @return The string that is the Station's line name.
     */
    std::string getLine() const;
    /**
     * Station's line setter.
     * @param line Line name string
     */
    void setLine(const std::string &line);
    /**
     * Station's township getter.
     * @return The string that is the Station's township name.
     */
    std::string getTownship() const;
    /**
     * Station's township setter.
     * @param township Township name string
     */
    void setTownship(const std::string &township);
    /**
     * Station's name getter.
     * @return The string that is the Station's name.
     */
    std::string getName() const;
    /**
     * Station's name setter.
     * @param name Name string
     */
    void setName(const std::string &name);

    /**
     * Method only used in the Dijkstra algorithm.
     * It returns the current cost of the station
     * @return station's cost
     */
    double getCost() const;

    /**
     * Method only used in the Dijkstra algorithm
     * It sets the current cost of the station
     * @param cost station's cost
     */
    void setCost(double cost);

    /**
     * Returns the vector of edges that the station is connected to
     *
     * @return vector of edges
     */
    std::vector<Edge *> getAdj() const;

    /**
     * Returns true if the station has been visited, false otherwise
     *
     * @return true if the station has been visited, false otherwise
     */
    bool isVisited() const;

    /**
     * Sets the visited status of the station
     *
     * @param visited
     */
    void setVisited(bool visited);

    /**
     * Adds a railway segment (an edge of the network graph) adjacent to the Station.
     *
     * @param dest Pointer to the destination Station of the Edge to add
     * @param w Edge's capacity in terms of the number of trains it cand handle simultaneously
     * @param alfa Whether the segment is STANDARD (false) or ALFA PENDULAR (true).
     * @return A pointer to the added graph Edge (object of class Edge).
     */
    Edge * addEdge(Station *dest, double w, bool alfa);

    /**
     * Tries to remove a railway segment (an edge of the network graph) adjacent to the station.
     *
     * Time Complexity: O(|E|) where |E| is the number of edges of the station.
     *
     * @param dest Pointer to the destination Station of the Edge to remove
     * @param alfa Whether the segment if STANDARD (false) or ALFA PENDULAR (true).
     * @return True if desired segment was found and removed, false otherwise.
     */
    bool removeEdge(Station* dest, bool alfa);
private:
    /**
     * String with the station's name
     */
    std::string name;

    /**
     * Pointer to the station's district
     */
    District* district;

    /**
     * Pointer to the station's municipality
     */
    Municipality* municipality;

    /**
     * String with the station's township
     */
    std::string township;

    /**
     * String with the station's line
     */
    std::string line;

    /**
     * Vector of edges that the station is connected to
     */
    std::vector<Edge *> adj;

    /**
     * Boolean that indicates if the station has been visited(used in various algorithms)
     */
    bool visited = false;

    /**
     * Auxiliary variable only used in the Dijkstra algorithm, which indicates the current cost of the station
     */
    double cost;
};

/**
 * @brief A class that represents a railway segment between two Stations, being an Edge of the network graph.
 *
 * Given that we represent the railway network as a graph, the edges/segments are the graph's edges.\n
 * An Edge is represented by its origin and destination Stations (note that the Edges are bidirectional) and its
 * capacity in terms of the number of trains that can travel on it simultaneously (weight).\n
 * Note: all the methods time complexity is O(1), except where specified.
 */
class Edge {
public:
    /**
     * Constructor for Edge
     * @param orig Pointer to origin Station
     * @param dest Pointer to destination Station
     * @param w Capacity of the segment in terms of the number of trains it can handle simultaneously
     * @param isAlfa Whether the segment is STANDARD (false) or ALFA PENDULAR (true)
     */
    Edge(Station *orig, Station *dest, double w, bool isAlfa);

    /**
     * Edge's destination Station getter.
     * @return Pointer to the destination Station
     */
    Station * getDest() const;
    /**
     * Weight (capacity in terms of trains the Edge can handle simultaneously) getter.
     * @return Integer with the weight
     */
    int getWeight() const;
    /**
     * Edge's origin Station getter.
     * @return Pointer to the origin Station
     */
    Station * getOrig() const;
    /**
     * Returns the reverse Edge (origin and destination Stations switched).
     * @return Pointer to the reverse Edge
     */
    Edge *getReverse() const;
    /**
     * Flow getter (used in Max Flow algorithms).
     * @return Integer with the current flow in a Max Flow algorithm
     */
    int getFlow() const;

    /**
     * Edge weight setter.
     * @param weight Integer with the weight
     */
    void setWeight(int weight);
    /**
     * Reverse Edge (origin an destination switched) setter.
     * @param reverse Pointer to the reverse Edge
     */
    void setReverse(Edge *reverse);
    /**
     * Flow (used in Max Flow algorithms) setter.
     * @param flow Integer with the current flow
     */
    void setFlow(int flow);
    /**
     * Type of segment getter.
     * @return True if ALFA PENDULAR, false if STANDARD.
     */
    bool isAlfa() const;
    /**
     * Type of segment setter.
     * @param alfa Boolean true if ALFA PENDULAR, false if STANDARD
     */
    void setAlfa(bool alfa);

    /**
     * Returns the cost of the edge, 4 if it the service is Alfa Pendular, 2 if it is Standard
     * @return cost of the edge
     */
    int getCost() const;
private:
    /**
     * Pointer to the edge's destination
     */
    Station * dest;

    /**
     * Integer with the edge's weight
     */
    int weight;

    /**
     * Pointer to the edge's origin
     */
    Station *orig;

    /**
     * Pointer to the edge's reverse edge, by default it is nullptr
     */
    Edge *reverse = nullptr;

    /**
     * Auxiliary variable used in various algorithms that stores the current flow of the edge
     */
    int flow;

    /**
     * Boolean that indicates if the type of service of the edge, it is true if it is an Alfa Pendular service, false if it is a Standard service
     */
    bool alfa;
};

#endif //DA_PROJ1_StationEDGE_H
