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

void readStations(const std::string& filename, Graph& graph);
void readNetwork(const std::string& filename, Graph& graph);

#endif //DA_PROJ1_READ_DATA_H
