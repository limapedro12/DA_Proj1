#include "VertexEdge.h"

Vertex::Vertex(int id): id(id) {}

Edge * Vertex::addEdge(Vertex *d, double w, bool alfa) {
    auto newEdge = new Edge(this, d, w, alfa);
    adj.push_back(newEdge);
    return newEdge;
}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

Station* Vertex::getStation() const {
    return station;
}

void Vertex::setStation(Station *station) {
    this->station = station;
}

Edge::Edge(Vertex *orig, Vertex *dest, double w, bool alfa): orig(orig), dest(dest), weight(w), alfa(alfa) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

bool Edge::isAlfa() const {
    return alfa;
}

void Edge::setAlfa(bool alfa) {
    this->alfa = alfa;
}
