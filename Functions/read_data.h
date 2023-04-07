#ifndef DA_PROJ1_READ_DATA_H
#define DA_PROJ1_READ_DATA_H

#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "../Classes/Graph.h"
#include "../Classes/VertexEdge.h"
#include "../Classes/Municipality.h"
#include "../Classes/District.h"

/**
 * Reads the stations in a given csv file and populates a given graph with those stations.
 *
 * @param filename Path to the stations csv filename
 * @param graph Reference to the Graph to populate
 */
void readStations(const std::string& filename, Graph& graph);

/**
 * Reads the railway segments in a given csv file and populates a given graph with those stations.
 * Cannot be called before readStations().
 *
 * @param filename Path to network csv filename
 * @param graph Reference to the Graph to populate
 */
void readNetwork(const std::string& filename, Graph& graph);

#endif //DA_PROJ1_READ_DATA_H
