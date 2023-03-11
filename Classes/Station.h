#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>

#include "Municipality.h"
#include "District.h"

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
private:
    std::string name;
    District* district;
    Municipality* municipality;
    std::string township;
    std::string line;
};


#endif //DA_PROJ1_STATION_H
