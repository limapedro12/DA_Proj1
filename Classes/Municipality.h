#ifndef DA_PROJ1_MUNICIPALITY_H
#define DA_PROJ1_MUNICIPALITY_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

class Municipality {
public:
    Municipality(const std::string& name);
    void addStation(Station* station);
    bool operator<(const Municipality& other) const;
    std::string getName() const;
private:
    std::string name;
    std::vector<Station*> stations;
};


#endif //DA_PROJ1_MUNICIPALITY_H
