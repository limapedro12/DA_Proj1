#ifndef DA_PROJ1_GRAPH_H
#define DA_PROJ1_GRAPH_H

#include <vector>
#include <string>

#include "VertexEdge.h"

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
    bool addEdge(Station* sourc, Station* dest, double w, bool alfa);
    bool addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa);

    std::vector<Station*> getVertexSet() const;
private:
    std::vector<Station *> vertexSet;    // vertex set

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string& name) const;
};


#endif //DA_PROJ1_GRAPH_H
