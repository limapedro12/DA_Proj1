#ifndef DA_PROJ1_MUNICIPALITY_H
#define DA_PROJ1_MUNICIPALITY_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

/**
 * @brief A class for a Portuguese Municipality.
 *
 * Represents a municipality of Portugal by its name and includes pointers to the stations on it.
 */
class Municipality {
public:
    /**
     * Constructor. Receives a municipality name.
     * @param name
     */
    Municipality(const std::string& name);
    /**
     * Adds a given station pointer to the municipality's stations.
     * @param station
     */
    void addStation(Station* station);
    /**
     * Less than (Municipality A < Municipality B) comparison operator. Lexicographically compares the municipalities' names.
     * @param other
     * @return True if A's name is lexicographically lower than B's name, false otherwise.
     */
    bool operator<(const Municipality& other) const;
    /**
     * Municipality's name getter.
     * @return The string that is the Municipality's name.
     */
    std::string getName() const;
private:
    std::string name;
    std::vector<Station*> stations;
};


#endif //DA_PROJ1_MUNICIPALITY_H
