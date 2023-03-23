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
Edge* Graph::addEdge(Station* sourc, Station* dest, double w, bool alfa){
    auto v1 = findVertex(sourc->getName());
    auto v2 = findVertex(dest->getName());
    if (v1 == nullptr || v2 == nullptr)
        return nullptr;
    Edge* e = v1->addEdge(v2, w, alfa);
    return e;
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

using namespace std;

vector<Edge*> Graph::path(const string& source, const string& dest) const {
    std::vector<Edge*> res;
    unordered_map<Station*, Edge*> before;
    bool found = false;
    Station* v = findVertex(source);
    Station* dest_v = findVertex(dest);
    if(v == nullptr)
        return res;
    for(Station* b: vertexSet)
        b->setVisited(false);
    std::queue<Station*> q;
    q.push(v);
    before[v] = nullptr;
    v -> setVisited(true);
    while(!q.empty()){
        auto x = q.front();
        x->setVisited(true);
        q.pop();
        for(Edge* e: x->getAdj())
            if(!(e->getDest()->isVisited()) && 2 * e->getWeight() > e->getFlow()){
                e->getDest() -> setVisited(true);
                q.push(e->getDest());
                before[e->getDest()] = e;
                if(e->getDest() == dest_v) {
                    found = true;
                    break;
                }
            }
        if(found)
            break;
    }
    if(!found)
        return res;

    list<Edge*> temp;
    Edge* curr = before[dest_v];
    while(curr != nullptr){
        temp.push_front(curr);
        curr = before[curr->getOrig()];
    }

    res.resize(temp.size());
    copy(temp.begin(), temp.end(), res.begin());
    return res;
}

double Graph::findBottleneck(vector<Edge*> path){
    int capacity = numeric_limits<int>::max();
    for(Edge* e: path)
        capacity = min(capacity, 2*e->getWeight() - e->getFlow());
    return capacity;
}

Graph Graph::edmondsKarp(const string& source, const string& target) {
    for(Station* v: vertexSet)
        for(Edge* e: v->getAdj())
            e->setFlow(0);

    Graph residual = *this;

    vector<Edge*> p = residual.path(source, target);

    bool found = false;

    while(!p.empty()){
        found = true;
        double b = findBottleneck(p);
        for(Edge* e: p){
            e->setFlow(e->getFlow() + b);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - b);
        }
        p = residual.path(source, target);
    }

//------------------------------DELETE LATER----------------------------------
    for(Station* v: residual.getVertexSet())
        for(Edge* e: v->getAdj())
            if(e->getFlow() > 0)
                cout << e->getOrig()->getName() << " -" << e->getFlow() << "-> " << e->getDest()->getName()
                     << (e->isAlfa() ? " (ALFA) ":" (STANDARD) ") << endl;
    cout << endl;
//----------------------------------------------------------------------------

    if(!found)
        return Graph();

    return residual;
}

int Graph::maxFlow(const std::string& source, const std::string& target){
    Graph residual = edmondsKarp(source, target);

    if(residual.vertexSet.empty())
        return -1;

    int flow = 0;
    for(Edge* e: residual.findVertex(source)->getAdj()) {
        flow += e->getFlow();
    }

    return flow;
}

int Graph::maxTrainsAtStation(Station* t){

    Graph temp = *this;
    int max = 0;
    Station s("temp", nullptr, nullptr, "", "");
    temp.addVertex(&s);
    for(Station* v: vertexSet)
        if(v != t)
            temp.addBidirectionalEdge(&s, v, 1000000000, false);

    auto f = temp.path(s.getName(), t->getName());

    int ret = temp.maxFlow(s.getName(), t->getName());
    if(ret == -1)
        return 0;
    return ret;
}

int Graph::costBFS(const std::string& source){
    int cost = 0;
    Station* v = findVertex(source);
    if(v == nullptr)
        return 0;
    for(Station* b: vertexSet)
        b->setVisited(false);
    std::queue<Station*> q;
    q.push(v);
    v -> setVisited(true);
    while(!q.empty()){
        auto x = q.front();
        for(Edge* e: x->getAdj()) {
            if(e->getFlow() > 0)
                cost += e->getFlow() * (e->isAlfa() ? 4 : 2);
            if (!(e->getDest()->isVisited())) {
                e->getDest()->setVisited(true);
                q.push(e->getDest());
            }
        }
        q.pop();
    }
    return cost;
}

int Graph::cost(const std::string& source, const std::string& target){
    if(target == source)
        return 0;

    Graph residual = edmondsKarp(source, target);
    if(residual.vertexSet.empty())
        return -1;

    int cost = residual.costBFS(source);
    if(cost == 0)
        return -1;

    return cost;
}

struct compCost{
    bool operator()(const Station *a, const Station *b) const {
        return a->getCost() < b->getCost() || (a->getCost() == b->getCost() && a->getName() < b->getName());
    }
};

//returns the path from source to target with the minimum cost using the Dijkstra algorithm, but instead of a priority queue, it uses a set
vector<Edge*> Graph::pathDijkstra(const string& source, const string& dest) const {
    std::vector<Edge*> res;
    unordered_map<Station*, Edge*> before;
    bool found = false;
    Station* v = findVertex(source);
    Station* dest_v = findVertex(dest);
    if(v == nullptr)
        return res;
    for(Station* b: vertexSet) {
        b->setCost(numeric_limits<double>::max());
        b->setVisited(false);
    }

    std::set<Station*, compCost> q;
    v->setCost(0);

    for(Station* b: vertexSet)
        q.insert(b);

    before[v] = nullptr;
    v -> setVisited(true);
    while(!q.empty()){
        auto x = *q.begin();
        q.erase(q.begin());
        if(x->getName() == dest) {
            found = true; break;
        }
        x->setVisited(true);
        for(Edge* e: x->getAdj()) {
            if(2 * e->getWeight() <= e->getFlow())
                continue;
            if(e->getDest()->getCost() > e->getOrig()->getCost() + e->getCost()){
                q.erase(e->getDest());
                e->getDest()->setCost(e->getOrig()->getCost() + e->getCost());
                q.insert(e->getDest());
                before[e->getDest()] = e;
            }
        }
    }
    if(!found)
        return res;

    list<Edge*> temp;
    Edge* curr = before[dest_v];
    while(curr != nullptr){
        temp.push_front(curr);
        curr = before[curr->getOrig()];
    }

    res.resize(temp.size());
    copy(temp.begin(), temp.end(), res.begin());
    return res;
}

pair<int, vector<Edge*>> Graph::minCost(const std::string& source, const std::string& target){
    for(Station* v: vertexSet)
        for(Edge* e: v->getAdj())
            e->setFlow(0);

    vector<Edge*> p = pathDijkstra(source, target);
    if(p.empty())
        return make_pair(-1, p);

    int cost = 0;
    for(Edge* e: p)
        cost += e->getCost();

    return make_pair(cost, p);
}

pair<double, Graph> Graph::edmondsKarpMinCost(const std::string& source, const std::string& target, double costLimit){
    for(Station* v: vertexSet)
        for(Edge* e: v->getAdj())
            e->setFlow(0);

    Graph residual = *this;

    vector<Edge*> p = residual.pathDijkstra(source, target);

    bool found = false;
    bool ended = false;
    int pathCost = 0;

    while(!p.empty()) {
        found = true;
        double b = findBottleneck(p);
        for(Edge* e: p)
            pathCost += e->getCost();
        if (pathCost * b > costLimit){
            b = (int) costLimit / pathCost;
            ended = true;
        }
        costLimit -= pathCost * b;
        for(Edge* e: p){
            e->setFlow(e->getFlow() + b);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - b);
        }
        if(ended)
            break;
        p = residual.path(source, target);
        pathCost = 0;
    }

    if(!found)
        return make_pair(-1, Graph());

    return make_pair(costLimit, residual);
}

pair<int, double> Graph::maxTrainsMinCost(const std::string& source, const std::string& target, double costLimit){
    auto tt = edmondsKarpMinCost(source, target, costLimit);
    Graph residual = tt.second;
    double cost = costLimit - tt.first;

    if(residual.vertexSet.empty())
        return make_pair(-1, -1);

    int flow = 0;
    for(Edge* e: residual.findVertex(source)->getAdj()) {
        flow += e->getFlow();
    }

    return make_pair(flow, cost);
}

