#ifndef DA_PROJ1_DISTRICT_H
#define DA_PROJ1_DISTRICT_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

class District {
public:
    District(const std::string& name);
    void addStation(Station* station);
    bool operator<(const District& other) const;
    std::string getName() const;
private:
    std::string name;
    std::vector<Station*> stations;
};

#endif //DA_PROJ1_DISTRICT_H
