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
 * @brief Class that represents a station
 *
 * This class represents a station and contains all the information about it,
 * such as its name, district, municipality, township and line.
 * It also contains a vector of edges that it is connected to.
 */
class Station {
public:
    /**
     * Constructor for Station
     *
     * @param name
     * @param district
     * @param municipality
     * @param township
     * @param line
     */
    Station(const std::string& name, District* district, Municipality* municipality, const std::string& township, const std::string& line);

    /**
     * District getter
     * @return station's district
     */
    District *getDistrict() const;

    /**
     * District setter
     * @param district
     */
    void setDistrict(District *district);

    /**
     * Municipality getter
     * @return station's municipality
     */
    Municipality *getMunicipality() const;

    /**
     * Municipality setter
     * @param municipality
     */
    void setMunicipality(Municipality *municipality);

    /**
     * Line getter
     * @return station's line
     */
    std::string getLine() const;

    /**
     * Line setter
     * @param line
     */
    void setLine(const std::string &line);

    /**
     * Township getter
     * @return station's township
     */
    std::string getTownship() const;

    /**
     * Township setter
     * @param township
     */
    void setTownship(const std::string &township);

    /**
     * Name getter
     * @return station's name
     */
    std::string getName() const;

    /**
     * Name setter
     * @param name
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
     * @param cost
     */
    void setCost(double cost);

    /**
     * Returns the vector of edges that the station is connected to
     * @return vector of edges
     */
    std::vector<Edge *> getAdj() const;

    /**
     * Returns true if the station has been visited, false otherwise
     * @return true if the station has been visited, false otherwise
     */
    bool isVisited() const;

    /**
     * Sets the visited status of the station
     * @param visited
     */
    void setVisited(bool visited);

    /**
     * Adds an edge to the station's vector of edges
     *
     * @param dest
     * @param w
     * @param alfa
     * @return pointer to the new edge
     */
    Edge * addEdge(Station *dest, double w, bool alfa);

    /**
     * Removes an edge from the station's vector of edges
     *
     * @param dest
     * @param alfa
     * @return true if the edge was removed, false otherwise
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
 * @brief Class that represents an edge
 *
 * This class represents an edge and contains all the information about it,
 * such as its origin, destination, weight, reverse edge.
 * It also contains a boolean that indicates if the edge is an alfa pendular service.
 */
class Edge {
public:
    /**
     * Constructor for Edge
     *
     * @param orig
     * @param dest
     * @param w
     * @param isAlfa
     */
    Edge(Station *orig, Station *dest, double w, bool isAlfa);

    /**
     * Destination getter
     * @return edge's destination
     */
    Station * getDest() const;

    /**
     * Weight getter
     * @return edge's weight
     */
    int getWeight() const;

    /**
     * Origin getter
     * @return edge's origin
     */
    Station * getOrig() const;

    /**
     * Reverse edge getter
     * @return reverse edge
     */
    Edge *getReverse() const;

    /**
     * Method used in various algorithms to get the current flow of the edge
     * @return current flow of the edge
     */
    int getFlow() const;

    /**
     * Weight setter
     * @param weight
     */
    void setWeight(int weight);

    /**
     * Reverse edge setter
     * @param reverse
     */
    void setReverse(Edge *reverse);

    /**
     * Flow setter
     * @param flow
     */
    void setFlow(int flow);

    /**
     * Returns true if the edge' service is Alfa Pendular, false if it is a Standard
     * @return true if the edge' service is Alfa Pendular, false if it is a Standard
     */
    bool isAlfa() const;

    /**
     * Sets the type of service of the edge, if alfa is true, the service is Alfa Pendular, if it is false, the service is Standard
     * @param alfa
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
