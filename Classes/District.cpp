#include "District.h"

District::District(const std::string &name) {
    this->name = name;
}

void District::addStation(Station *station) {
    stations.push_back(station);
}

bool District::operator<(const District &other) const {
    return name < other.name;
}

std::string District::getName() const {
    return name;
}
