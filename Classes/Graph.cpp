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



using namespace std;

//void Graph::createResidualGraph(const Graph& g) {
//    for(Station* v: g.getVertexSet())
//        addVertex(v->getId());
//
//    for(Station* v: g.getVertexSet())
//        for(Edge* e_or: v->getAdj()) {
//            bool found = false;
//            for (Edge *er_or: e_or->getDest()->getAdj())
//                if (er_or->getDest() == e_or->getOrig()) {
//                    found = true;
//                    addEdge(e_or->getOrig()->getId(), e_or->getDest()->getId(), e_or->getWeight()+er_or->getWeight());
//                    Edge* e = findVertex(e_or->getOrig()->getId())->getAdj().back();
//                    addEdge(e_or->getDest()->getId(), e_or->getOrig()->getId(), e_or->getWeight()+er_or->getWeight());
//                    Edge* er = findVertex(e_or->getDest()->getId())->getAdj().back();
//                    e->setFlow(er_or->getWeight());
//                    er->setFlow(e_or->getWeight());
//                    e->setReverse(er_or);
//                    er->setReverse(e_or);
//                    originalEdges.insert({e, e_or});
//                    originalEdges.insert({er, er_or});
//                    break;
//                }
//            if(!found){
//                addEdge(e_or->getOrig()->getId(), e_or->getDest()->getId(), e_or->getWeight());
//                if(vertexSet.empty()) cout << "empty" << endl;
//                Edge* e = findVertex(e_or->getOrig()->getId())->getAdj().back();
//                addEdge(e_or->getDest()->getId(), e_or->getOrig()->getId(), e_or->getWeight());
//                Edge *er = findVertex(e_or->getDest()->getId())->getAdj().back();
//                e->setFlow(0);
//                er ->setFlow(e_or->getWeight());
//                e->setReverse(er);
//                er->setReverse(e);
//                originalEdges.insert({e, e_or});
//            }
//        }
//}

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
        q.pop();
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

void Graph::edmondsKarp(const string& source, const string& target) {
    Graph residual = *this;

    vector<Edge*> p = residual.path(source, target);

//    for(auto i : p)
//        cout << i->getOrig()->getId() << ", "; cout << p.back()->getDest()->getId() << endl;

    while(!p.empty()){
        double b = findBottleneck(p);
        for(Edge* e: p){
            e->setFlow(e->getFlow() + b);
            e->getReverse()->setFlow(e->getReverse()->getFlow() - b);
        }
        p = residual.path(source, target);
    }

    for(Station* v: residual.getVertexSet())
        for(Edge* e: v->getAdj())
            if(e->getFlow() >= 0)
                cout << e->getOrig()->getName() << " -" << e->getFlow() << "-> " << e->getDest()->getName() << endl;
}
