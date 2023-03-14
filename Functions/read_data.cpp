#include <iostream>
#include "read_data.h"

std::set<District*> all_districts;
std::set<Municipality*> all_municipalities;

void readStations(const std::string& filename, Graph& graph){
    std::ifstream file(filename);
    std::string doc_line;
    std::getline(file, doc_line);

    while(std::getline(file, doc_line)){
        std::string name, municipality, district, township, line;
        std::istringstream iss(doc_line);
        std::getline(iss, name, ',');
        std::getline(iss, district, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, township, ',');
        std::getline(iss, line);

        District* d = new District(district);
        auto f = all_districts.find(d);
        if(f == all_districts.end())
            all_districts.insert(d);
        else {
            d = *f;
        }

        Municipality* m = new Municipality(municipality);
        auto f2 = all_municipalities.find(m);
        if(f2 == all_municipalities.end())
            all_municipalities.insert(m);
        else {
            m = *f2;
        }

        Station* s = new Station(name, d, m, township, line);
        d->addStation(s);
        m->addStation(s);

        graph.addVertex(s);
    }
}

void readNetwork(const std::string& filename, Graph& graph){
    std::ifstream file(filename);
    std::string doc_line;
    std::getline(file, doc_line);

    while(std::getline(file, doc_line)){
        std::string source, dest, weight, alfa;
        std::istringstream iss(doc_line);
        std::getline(iss, source, ',');
        std::getline(iss, dest, ',');
        std::getline(iss, weight, ',');
        std::getline(iss, alfa);

        if(stoi(weight) == 0)
            continue;
        else if(stoi(weight)/2 >= 1000000000)
            throw(std::invalid_argument("Weight can't be larger than 2000000000"));

        graph.addBidirectionalEdge(graph.findVertex(source), graph.findVertex(dest), std::stoi(weight)/2, alfa == "ALFA PENDULAR");
    }
}
