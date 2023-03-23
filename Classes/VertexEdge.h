#ifndef DA_PROJ1_StationEDGE_H
#define DA_PROJ1_StationEDGE_H

#include <vector>
#include <string>

#include "Municipality.h"
#include "District.h"

class Edge;

class Municipality;
class District;

class Station {
public:
    Station(const std::string& name, District* district, Municipality* municipality, const std::string& township, const std::string& line);
    District *getDistrict() const;
    void setDistrict(District *district);
    Municipality *getMunicipality() const;
    void setMunicipality(Municipality *municipality);
    std::string getLine() const;
    void setLine(const std::string &line);
    std::string getTownship() const;
    void setTownship(const std::string &township);
    std::string getName() const;
    void setName(const std::string &name);

    double getCost() const;
    void setCost(double cost);
    
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    void setVisited(bool visited);
    Edge * addEdge(Station *dest, double w, bool alfa);

//    bool operator<(const Station &rhs) const;
private:
    std::string name;
    District* district;
    Municipality* municipality;
    std::string township;
    std::string line;
    
    std::vector<Edge *> adj;
    bool visited = false;

    double cost;
};

class Edge {
public:
    Edge(Station *orig, Station *dest, double w, bool isAlfa);

    Station * getDest() const;
    int getWeight() const;
    Station * getOrig() const;
    Edge *getReverse() const;
    int getFlow() const;

    void setWeight(int weight);
    void setReverse(Edge *reverse);
    void setFlow(int flow);
    bool isAlfa() const;
    void setAlfa(bool alfa);

    int getCost() const;
private:
    Station * dest;
    int weight;

    bool selected = false;

    Station *orig;
    Edge *reverse = nullptr;

    int flow;

    bool alfa; // false if service is STANDARD, true if ALFA PENDULAR
};


#endif //DA_PROJ1_StationEDGE_H
