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
        "2 - Rede completa (sem caracteres não-ASCII)\n" <<
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

        if (option == 1) {
            Graph g;
            this->graph = g;
            readStations("../Project1Data/stations.csv", graph);
            readNetwork("../Project1Data/network.csv", graph);
            dataReady = true;
            return;
        } else if (option == 2) {
            Graph g;
            this->graph = g;
            readStations("../Project1Data/stations_ascii.csv", graph);
            readNetwork("../Project1Data/network_ascii.csv", graph);
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
        "3 - Top-k de municípios e distritos com maiores necessidades.\n" <<
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

        if (option == 1) basicMetrics1();
        else if (option == 2) basicMetrics2();
        else if (option == 3) basicMetrics3();
        else if (option == 4) basicMetrics4();
        else if (option == 0) return;
    }
}

void Menu::costOptimization() {
    Station* source;
    while (true) {
        std::cout << "Introduza o nome da estação de origem:\n";

        std::string input;
        std::getline(std::cin, input);

        source = graph.findVertex(input);
        if (source != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Station* dest;
    while (true) {
        std::cout << "Introduza o nome da estação de destino:\n";

        std::string input;
        std::getline(std::cin, input);

        dest = graph.findVertex(input);
        if (dest != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    /*
     * chamar funções do grafo
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

void Menu::basicMetrics1() {
    Station* source;
    while (true) {
        std::cout << "Introduza o nome da estação de origem:\n";

        std::string input;
        std::getline(std::cin, input);

        source = graph.findVertex(input);
        if (source != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Station* dest;
    while (true) {
        std::cout << "Introduza o nome da estação de destino:\n";

        std::string input;
        std::getline(std::cin, input);

        dest = graph.findVertex(input);
        if (dest != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }
}

void Menu::basicMetrics2() {
    /*
     * chamar método grafo
     */
}

void Menu::basicMetrics3() {
    while (true) {
        std::cout << "Qual o tamanho do top (k do top-k)?\n";

        std::string input;
        std::getline(std::cin, input);

        int k = stoi(input);

        if (k > 0) break;
        std::cout << "Número inválido. Por favor introduza um inteiro positivo.\n\n";
    }

    /*
     * chamar método grafo
     */
}

void Menu::basicMetrics4() {
    /*
     * chamar método grafo
     */
}

