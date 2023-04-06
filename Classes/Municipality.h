#ifndef DA_PROJ1_MUNICIPALITY_H
#define DA_PROJ1_MUNICIPALITY_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

/**
 * @brief Class that represents a municipality
 *
 * This class represents a municipality and contains all the information about it,
 * such as its name and the stations that are in it.
 */
class Municipality {
public:
    /**
     * Constructor for Municipality
     *
     * @param name
     */
    Municipality(const std::string& name);

    /**
     * Adds a station to the municipality
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
    bool operator<(const Municipality& other) const;

    /**
     * Municipality name getter
     *
     * @return municipality name
     */
    std::string getName() const;
private:
    /**
     * Municipality name
     */
    std::string name;

    /**
     * Vector of stations in the municipality
     */
    std::vector<Station*> stations;
};


#endif //DA_PROJ1_MUNICIPALITY_H
