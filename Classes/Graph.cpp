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

bool Graph::removeEdge(Station *orig, Station *dest, bool alfa) {
    if (!(orig->removeEdge(dest, alfa))) return false;
    return dest->removeEdge(orig, alfa);
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
                cout << e->getOrig()->getName() << " -" << e->getFlow() << "-> " << e->getDest()->getName() << endl;
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
    if(f.empty())
        cout << "\n\n\nempty\n\n\n" << endl;

    int ret = temp.maxFlow(s.getName(), t->getName());
    if(ret == -1)
        return 0;
    return ret;

//    vector<Station*> stations;
//    int max = 0;
//    for(Station* v: vertexSet)
//        if(v != s){
//            int flow = maxFlow(v->getName(), s->getName());
//            if(flow > max) {
//                max = flow;
//                stations.clear();
//                stations.push_back(v);
//            } else if(flow == max)
//                stations.push_back(v);
//        }
//    return {max, stations};
}
