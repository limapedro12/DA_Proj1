#include <iostream>
#include "Interface/Menu.h"

int main() {
    /*Graph graph;
    readStations("Project1Data/stations.csv", graph);
    readNetwork("Project1Data/network.csv", graph);

//    for(auto d : all_districts)
//        std::cout << d -> getName() << std::endl;
//
//    for(auto m : all_municipalities)
//        std::cout << m -> getName() << std::endl;

//    for(auto v : graph.getVertexSet()) {
//        std::cout << v->getName() << ", " << v->getDistrict()->getName() << ", " << v->getMunicipality()->getName()
//                  << ", " << v->getTownship() << ", " << v->getLine() << std::endl;
//        for(auto e : v->getAdj())
//            std::cout << "----- " << e->getDest()->getName() << ", " << e->getWeight() << ", " << e->isAlfa() << std::endl;
//    }


    graph.edmondsKarp("Porto Campanhã", "Lisboa Oriente");*/

    Menu menu;
    menu.mainMenu();

    return 0;
}
