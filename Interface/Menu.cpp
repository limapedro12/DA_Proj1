#include "Menu.h"

void Menu::mainMenu() {
    while (true) {
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n" <<
                  "1 - Carregar uma rede ferroviária (leitura e parsing dos dados)\n";
        if (dataReady) {
            std::cout << "2 - Informações básicas sobre a rede\n" <<
            "3 - Otimização de custo das operações\n" <<
            "4 - Fiabilidade da rede e sensibilidade a falhas\n\n";
        } else std::cout << "\nAs restantes opções apenas ficarão disponíveis quando carregar uma rede ferroviária.\n\n";

        std::cout << "0 - Sair do programa" << std::endl;

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            option = std::stoi(input);
            std::cout << "\n";
            if (option >= 0 && option <= 4) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) readData();
        else if (option == 2) basicMetrics();
        else if (option == 3) costOptimization();
        else if (option == 4) networkReliability();
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
        std::cout << "Escolha uma opção, escrevendo o número correspondente e pressionando ENTER.\n" <<
        "1 - Número máximo de comboios que podem viajar entre duas estações específicas\n" <<
        "2 - Par(es) de estações que requer(em) o maior número de comboios, ao tirar total partido de toda a rede\n" <<
        "3 - Top-k de municípios ou distritos com maiores necessidades.\n" <<
        "4 - Número máximo de comboios que podem chegar simultaneamente a uma dada estação, tendo em conta toda a rede\n" <<
        "0 - Menu anterior\n\n";

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            option = std::stoi(input);
            std::cout << "\n";
            if (option >= 0 && option <= 4) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1);
        else if (option == 2);
        else if (option == 3);
        else if (option == 4);
        else if (option == 0) return;
    }
}

void Menu::costOptimization() {
    /*
     * call necessary graph method(s)
     */
}

void Menu::networkReliability() {
     while (true) {
         std::cout << "Escolha uma opção, escrevendo o número correspondente e pressionando ENTER.\n" <<
         "1 - Número máximo de comboios que podem viajar entre duas estações específicas numa rede de conectividade reduzida\n" <<
         "2 - Top-k de estações mais afetadas por uma falha em cada segmento da rede\n" <<
         "0 - Menu anterior\n\n";

         std::string input;
         int option;

         while (true) {
             std::getline(std::cin, input);
             option = std::stoi(input);
             std::cout << "\n";
             if (option >= 0 && option <= 2) break;
             else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
         }

         if (option == 1);
         else if (option == 2);
         else if (option == 0) return;
     }
}
