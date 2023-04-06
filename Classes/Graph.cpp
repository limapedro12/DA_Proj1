#include "Graph.h"
#include <list>
#include <map>

Station* Graph::findVertex(const std::string& name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

int Graph::findVertexIdx(const std::string& name) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getName() == name)
            return i;
    return -1;
}

bool Graph::addVertex(Station* station) {
    if (findVertex(station->getName()) != nullptr)
        return false;
    vertexSet.push_back(station);
    return true;
}

bool Graph::removeEdge(Station *orig, Station *dest, bool alfa) {
    if (!(orig->removeEdge(dest, alfa))) return false;
    return dest->removeEdge(orig, alfa);
}

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

vector<Edge*> Graph::path(Station* source, Station* dest) const {
    std::vector<Edge*> res;
    unordered_map<Station*, Edge*> before;
    bool found = false;
    Station* v = source;
    Station* dest_v = dest;
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

Graph Graph::edmondsKarp(Station* source, Station* target) {
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

    if(!found)
        return Graph();

    return residual;
}

void Graph::printFlow(){
    for(Station* v: vertexSet)
        for(Edge* e: v->getAdj())
            if(e->getFlow() > 0)
                cout << e->getOrig()->getName() << " -" << e->getFlow() << "-> " << e->getDest()->getName()
                     << (e->isAlfa() ? " (ALFA) ":" (STANDARD) ") << endl;
    cout << endl;
}

int Graph::maxFlow(Station* source, Station* target, bool print){
    Graph residual = edmondsKarp(source, target);
    if(print)
        residual.printFlow();

    if(residual.vertexSet.empty())
        return -1;

    int flow = 0;
    for(Edge* e: residual.findVertex(source->getName())->getAdj()) {
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

    auto f = temp.path(&s, t);

    int ret = temp.maxFlow(&s, t);
    if(ret == -1)
        return 0;
    return ret;
}

int Graph::costBFS(Station* source){
    int cost = 0;
    Station* v = source;
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

int Graph::cost(Station* source, Station* target, bool print){
    if(target == source)
        return 0;

    Graph residual = edmondsKarpMinCost(source, target, numeric_limits<double>::max());
    if(print)
        residual.printFlow();

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
vector<Edge*> Graph::pathDijkstra(Station* source, Station* dest) const {
    std::vector<Edge*> res;
    unordered_map<Station*, Edge*> before;
    bool found = false;
    Station* v = source;
    Station* dest_v = dest;
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
        if(x->getName() == dest->getName()) {
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

pair<int, vector<Edge*>> Graph::minCost(Station* source, Station* target){
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

Graph Graph::edmondsKarpMinCost(Station* source, Station* target, double costLimit){
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
        p = residual.pathDijkstra(source, target);
        pathCost = 0;
    }

    if(!found)
        return Graph();

    return residual;
}

pair<int, double> Graph::maxTrainsMinCost(Station* source, Station* target, double costLimit, bool print){
    Graph residual = edmondsKarpMinCost(source, target, costLimit);

    if(print)
        residual.printFlow();

    int cost = 0;
    for(Station* v: residual.vertexSet)
        for(Edge* e: v->getAdj())
            if(e->getFlow() > 0)
                cost += e->getCost() * e->getFlow();

    if(residual.vertexSet.empty())
        return make_pair(-1, -1);

    int flow = 0;
    for(Edge* e: residual.findVertex(source->getName())->getAdj()) {
        flow += e->getFlow();
    }

    return make_pair(flow, cost);
}

std::list<std::pair<Station*, Station*>> Graph::mostTrainsPair() {

    Graph* g = this;
    int maxflow=-10;
    std::list<std::pair<Station*, Station*>> maxflowstations;

    std::map<Station*, double> weightSumMap;
    for (Station* stationPtr : vertexSet) {
        double weightSum = 0;
        for (Edge* edge : stationPtr->getAdj()) {
            weightSum += 2*(edge->getWeight());
        }
        weightSumMap[stationPtr] = weightSum;
    }

    // sort the map in descending order of their weightSum
    std::vector<std::pair<Station*, double>> sortedStations(
            weightSumMap.begin(), weightSumMap.end());
    std::sort(sortedStations.begin(), sortedStations.end(),
              [](const std::pair<Station*, double>& a,
                 const std::pair<Station*, double>& b) {
                  return a.second > b.second;
              });

    for (auto it1 = sortedStations.begin(); it1 != sortedStations.end(); ++it1) {
        Station* stationPtr1 = it1->first;
        if (it1->second < maxflow) {
            break;
        }
        for (auto it2 = it1; it2 != sortedStations.end(); ++it2) {
            Station* stationPtr2 = it2->first;
            if (it2->second < maxflow) {
                break;
            }
            if (stationPtr1->getName() == stationPtr2->getName()) {
                continue;
            }
            else {
                int flow = maxFlow(stationPtr1, stationPtr2);
                if(flow>maxflow) {
                    maxflow=flow;
                    maxflowstations.clear(); //apagar tudo da lista dupla de estações

                    maxflowstations.push_back(std::make_pair(stationPtr1, stationPtr2)); //adicionar par de estações à lista de estações com maxflow maior;
                }

                else if(flow==maxflow) {
                    maxflowstations.push_back(std::make_pair(stationPtr1, stationPtr2)); //adicionar par à lista de estações com maxflow maior;
                }
            }
        }
    }

    return maxflowstations;
}

template <typename K, typename V>
bool cmp(const pair<K, V>& a, const pair<K, V>& b) {
    return a.second > b.second;
}

void sortMapsByDescendingValue(std::map<District*, int>& districtflow, std::map<Municipality*, int>& municipalityflow) {
    // Sort districtflow by descending order of values
    vector<pair<District*, int>> districtVec(districtflow.begin(), districtflow.end());
    sort(districtVec.begin(), districtVec.end(), cmp<District*, int>);

    // Sort municipalityflow by descending order of values
    vector<pair<Municipality*, int>> municipalityVec(municipalityflow.begin(), municipalityflow.end());
    sort(municipalityVec.begin(), municipalityVec.end(), cmp<Municipality*, int>);

    // Clear original maps
    districtflow.clear();
    municipalityflow.clear();

    // Re-populate maps with sorted values
    for (const auto& [key, value] : districtVec) {
        districtflow[key] = value;
    }

    for (const auto& [key, value] : municipalityVec) {
        municipalityflow[key] = value;
    }
}
