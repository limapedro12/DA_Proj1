#include "Graph.h"

/*
 * Auxiliary function to find a vertex with a given content.
 */
Station* Graph::findVertex(const std::string& name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const std::string& name) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getName() == name)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Station* station) {
    if (findVertex(station->getName()) != nullptr)
        return false;
    vertexSet.push_back(station);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(Station* sourc, Station* dest, double w, bool alfa){
    auto v1 = findVertex(sourc->getName());
    auto v2 = findVertex(dest->getName());
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, alfa);
    return true;
}

bool Graph::addBidirectionalEdge(Station* sourc, Station* dest, double w, bool alfa) {
    auto v1 = findVertex(sourc->getName());
    auto v2 = findVertex(dest->getName());
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, alfa);
    auto e2 = v2->addEdge(v1, w, alfa);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

std::vector<Station*> Graph::getVertexSet() const {
    return vertexSet;
}
