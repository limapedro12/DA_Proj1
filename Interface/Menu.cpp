#include "Menu.h"

void Menu::mainMenu() {
    while (true) {
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n" <<
                  "1 - Carregar uma rede ferroviária (leitura e parsing dos dados).\n";
        if (dataReady) {
            std::cout << "2 - ..." << std::endl;
        } else std::cout << "\nAs restantes opções apenas ficarão disponíveis quando carregar uma das redes disponíveis.\n\n";

        std::cout << "0 - Sair do programa" << std::endl;

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            option = std::stoi(input);
            std::cout << "\n";
            if (option >= 0 && option <= 1) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) readData();
        else if (option == 0) {
            std::cout << "Obrigado por usar o nosso programa!\n\nFrancisco Alves, Pedro Lima e Pedro Januário\n";
            return;
        }
    }
}

void Menu::readData() {
    while (true) {
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n" <<
        "1 - Rede completa\n" <<
        "0 - Menu anterior\n\n";

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            option = std::stoi(input);
            std::cout << "\n";
            if (option >= 0 && option <= 1) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) {
            Graph g;
            this->graph = g;
            readStations("../Project1Data/stations.csv", graph);
            readNetwork("../Project1Data/network.csv", graph);
            dataReady = true;
            return;
        } else if (option == 0) return;
    }
}

void Menu::basicMetrics() {
    while (true) {

    }
}
