#ifndef DA_PROJ1_DISTRICT_H
#define DA_PROJ1_DISTRICT_H

#include <string>
#include <vector>

#include "Station.h"

class District {
public:
    District(const std::string& name);
    void addStation(Station* station);
private:
    std::string name;
    std::vector<Station*> stations;
};


#endif //DA_PROJ1_DISTRICT_H
