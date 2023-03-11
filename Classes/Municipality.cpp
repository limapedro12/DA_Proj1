#include "Municipality.h"

Municipality::Municipality(const std::string &name) {
    this->name = name;
}

void Municipality::addStation(Station *station) {
    stations.push_back(station);
}

bool Municipality::operator<(const Municipality &other) const {
    return name < other.name;
}

std::string Municipality::getName() const {
    return name;
}
