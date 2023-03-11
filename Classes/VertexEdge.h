#ifndef DA_PROJ1_VERTEXEDGE_H
#define DA_PROJ1_VERTEXEDGE_H

#include <vector>

#include "Station.h"

class Edge;

class Vertex {
public:
    Vertex(int id);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;

    void setId(int info);
    void setVisited(bool visited);

    Edge * addEdge(Vertex *dest, double w, bool alfa);

    Station* getStation() const;
    void setStation(Station* station);
private:
    int id;
    std::vector<Edge *> adj;
    bool visited = false;

    Station* station;
};

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, bool isAlfa);

    Vertex * getDest() const;
    double getWeight() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setReverse(Edge *reverse);
    void setFlow(double flow);
    bool isAlfa() const;
    void setAlfa(bool alfa);
private:
    Vertex * dest;
    double weight;

    bool selected = false;

    Vertex *orig;
    Edge *reverse = nullptr;

    double flow;

    bool alfa; // false if service is STANDARD, true if ALFA PENDULAR
};


#endif //DA_PROJ1_VERTEXEDGE_H
