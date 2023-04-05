#include "VertexEdge.h"

Station::Station(const std::string &name, District *district, Municipality *municipality, const std::string &township,
                 const std::string &line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

std::string Station::getName() const {
    return name;
}

void Station::setName(const std::string &name) {
    Station::name = name;
}

std::string Station::getTownship() const {
    return township;
}

void Station::setTownship(const std::string &township) {
    Station::township = township;
}

District *Station::getDistrict() const {
    return district;
}

void Station::setDistrict(District *district) {
    Station::district = district;
}

Municipality *Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(Municipality *municipality) {
    Station::municipality = municipality;
}

std::string Station::getLine() const {
    return line;
}

void Station::setLine(const std::string &line) {
    Station::line = line;
}

Edge * Station::addEdge(Station *d, double w, bool alfa) {
    auto newEdge = new Edge(this, d, w, alfa);
    adj.push_back(newEdge);
    return newEdge;
}

bool Station::removeEdge(Station *dest, bool alfa) {
    for (size_t i = 0; i < adj.size(); i++) {
        Edge* e = adj[i];
        if (e->getDest() == dest && e->isAlfa() == alfa) {
            adj.erase(adj.begin() + i);
            return true;
        }
    }
    return false;
}

std::vector<Edge*> Station::getAdj() const {
    return this->adj;
}

bool Station::isVisited() const {
    return this->visited;
}

void Station::setVisited(bool visited) {
    this->visited = visited;
}

double Station::getCost() const {
    return cost;
}

void Station::setCost(double cost) {
    Station::cost = cost;
}

void Station::print() const {
    std::cout << name << std::endl;
    for (Edge* e : adj) {
        std::cout << e->getDest()->name << ',';
        if (e->isAlfa()) std::cout << "ALFA PENDULAR\n";
        else std::cout << "STANDARD\n";
    }
    std::cout << std::endl;
}

int Station::getMaxBefore() const {
    return maxTrainsBefore;
}

void Station::setMaxBefore(int n) {
    maxTrainsBefore = n;
}

int Station::getMaxDiff() const {
    return maxTrainsDiff;
}

void Station::setMaxDiff(int n) {
    maxTrainsDiff = n;
}

Edge::Edge(Station *orig, Station *dest, double w, bool alfa): orig(orig), dest(dest), weight(w), alfa(alfa) {}

Station * Edge::getDest() const {
    return this->dest;
}

int Edge::getWeight() const {
    return this->weight;
}

Station * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

int Edge::getFlow() const {
    return flow;
}

void Edge::setWeight(int weight) {
    this->weight = weight;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(int flow) {
    this->flow = flow;
}

bool Edge::isAlfa() const {
    return alfa;
}

void Edge::setAlfa(bool alfa) {
    this->alfa = alfa;
}

int Edge::getCost() const{
    if(alfa)
        return 4;
    else
        return 2;
}
