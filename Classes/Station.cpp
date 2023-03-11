#include "Station.h"

Station::Station(const std::string &name, District *district, Municipality *municipality, const std::string &township,
                 const std::string &line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

std::string Station::getName() const {
    return name;
}

void Station::setName(const std::string &name) {
    Station::name = name;
}

std::string Station::getTownship() const {
    return township;
}

void Station::setTownship(const std::string &township) {
    Station::township = township;
}

District *Station::getDistrict() const {
    return district;
}

void Station::setDistrict(District *district) {
    Station::district = district;
}

Municipality *Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(Municipality *municipality) {
    Station::municipality = municipality;
}

std::string Station::getLine() const {
    return line;
}

void Station::setLine(const std::string &line) {
    Station::line = line;
}
