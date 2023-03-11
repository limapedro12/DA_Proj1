#ifndef DA_PROJ1_MUNICIPALITY_H
#define DA_PROJ1_MUNICIPALITY_H

#include <string>
#include <vector>

#include "Station.h"

class Municipality {
public:
    Municipality(const std::string& name);
    void addStation(Station* station);
private:
    std::string name;
    std::vector<Station*> stations;
};


#endif //DA_PROJ1_MUNICIPALITY_H
