#include "Municipality.h"

Municipality::Municipality(const std::string &name) {
    this->name = name;
}

void Municipality::addStation(Station *station) {
    stations.push_back(station);
}
