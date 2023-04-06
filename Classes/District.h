#ifndef DA_PROJ1_DISTRICT_H
#define DA_PROJ1_DISTRICT_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

/**
 * @brief Class that represents a district
 *
 * This class represents a district and contains all the information about it,
 * such as its name and the stations that are in it.
 */
class District {
public:
    /**
     * Constructor for District
     *
     * @param name
     */
    District(const std::string& name);

    /**
     * Adds a station to the district
     *
     * @param station
     */
    void addStation(Station* station);

    /**
     * Operator < overload
     *
     * @param other
     * @return
     */
    bool operator<(const District& other) const;

    /**
     * District name getter
     *
     * @return district name
     */
    std::string getName() const;
private:
    /**
     * District name
     */
    std::string name;

    /**
     * Vector of stations in the district
     */
    std::vector<Station*> stations;
};

#endif //DA_PROJ1_DISTRICT_H
