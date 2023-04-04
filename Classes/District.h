#ifndef DA_PROJ1_DISTRICT_H
#define DA_PROJ1_DISTRICT_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;
/**
 * @brief A class for a Portuguese district.
 *
 * Represents a district of Portugal by its name and includes pointers to the stations on it.
 */
class District {
public:
    /**
     * Constructor. Receives a district name.
     * @param name
     */
    District(const std::string& name);
    /**
     * Adds a given station pointer to the district's stations.
     * @param station
     */
    void addStation(Station* station);
    /**
     * Less than (District A < District B) comparison operator. Lexicographically compares the districts' names.
     * @param other
     * @return True if A's name is lexicographically lower than B's name, false otherwise.
     */
    bool operator<(const District& other) const;
    /**
     * District name's getter.
     * @return The string that is the District's name.
     */
    std::string getName() const;
private:
    std::string name;
    std::vector<Station*> stations;
};

#endif //DA_PROJ1_DISTRICT_H
