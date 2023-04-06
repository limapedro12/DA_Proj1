#ifndef DA_PROJ1_MUNICIPALITY_H
#define DA_PROJ1_MUNICIPALITY_H

#include <string>
#include <vector>

#include "VertexEdge.h"

class Station;

/**
<<<<<<< HEAD
 * @brief A class for a Portuguese Municipality.
 *
 * Represents a municipality of Portugal by its name and includes pointers to the stations on it.\n
 * Note: all the methods time complexity is O(1), except where specified.
=======
 * @brief Class that represents a municipality
 *
 * This class represents a municipality and contains all the information about it,
 * such as its name and the stations that are in it.
>>>>>>> documentation2
 */
class Municipality {
public:
    /**
     * Constructor for Municipality
     *
     * @param name Municipality name
     */
    Municipality(const std::string& name);
    /**
     * Adds a given station pointer to the municipality's stations.
     *
     * @param station Station pointer
     */
    void addStation(Station* station);
    /**
     * Less than (Municipality A < Municipality B) comparison operator. Lexicographically compares the municipalities' names.
     *
     * @param other Other Municipality Pointer
     * @return True if A's name is lexicographically lower than B's name, false otherwise.
     */
    bool operator<(const Municipality& other) const;
    /**
     * Municipality's name getter.
     * @return The string that is the Municipality's name.
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
