#include "District.h"

District::District(const std::string &name) {
    this->name = name;
}

void District::addStation(Station *station) {
    stations.push_back(station);
}
