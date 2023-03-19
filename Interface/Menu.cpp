#include "Menu.h"

void clear() {for (int i = 0; i < 50; i++) std::cout << std::endl;}
void wait() {std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin.get();}

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
        int option = -1;

        while (true) {
            std::getline(std::cin, input);
            if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) option = std::stoi(input);
            std::cout << "\n";
            if (dataReady) {
                if (option >= 0 && option <= 4) break;
            } else if (option == 0 || option == 1) break;
            std::cout << "Opção inválida. Por favor tente novamente.\n\n";
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
        int option = -1;

        while (true) {
            std::getline(std::cin, input);
            if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) option = std::stoi(input);
            std::cout << "\n";
            if (option >= 0 && option <= 2) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) {
            Graph g;
            this->graph = g;
            readStations("../Project1Data/stations.csv", graph);
            readNetwork("../Project1Data/network.csv", graph);
            stationsFile = "../Project1Data/stations.csv";
            networkFile = "../Project1Data/network.csv";
            dataReady = true;
            return;
        } else if (option == 2) {
            Graph g;
            this->graph = g;
            readStations("../Project1Data/stations_ascii.csv", graph);
            readNetwork("../Project1Data/network_ascii.csv", graph);
            stationsFile = "../Project1Data/stations_ascii.csv";
            networkFile = "../Project1Data/network_ascii.csv";
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
        int option = -1;

        while (true) {
            std::getline(std::cin, input);
            if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) option = std::stoi(input);
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
        std::cout << "Introduza o nome da estação de origem: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        source = graph.findVertex(input);
        if (source != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Station* dest;
    while (true) {
        std::cout << "Introduza o nome da estação de destino: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

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
         int option = -1;

         while (true) {
             std::getline(std::cin, input);
             if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) option = std::stoi(input);
             std::cout << "\n";
             if (option >= 0 && option <= 2) break;
             else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
         }

         if (option == 1) networkReliability1();
         else if (option == 2) networkReliability2();
         else if (option == 0) return;
     }
}

void Menu::basicMetrics1() {
    Station* source;
    while (true) {
        std::cout << "Introduza o nome da estação de origem: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        source = graph.findVertex(input);

        if (source != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Station* dest;
    while (true) {
        std::cout << "Introduza o nome da estação de destino: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        dest = graph.findVertex(input);
        if (dest != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    clear();
    int m = graph.maxFlow(source -> getName(), dest -> getName());
    if (m != -1)
        std::cout << "Número máximo de comboios que podem viajar entre " << source->getName() << " e " << dest->getName() << " é " << m << "\n\n";
    else
        std::cout << "Não existe caminho entre " << source->getName() << " e " << dest->getName() << "\n\n";

    //int i = 1;
    wait();
    clear();
}

void Menu::basicMetrics2() {
    /*
     * chamar método grafo
     */
}

void Menu::basicMetrics3() {
    while (true) {
        std::cout << "Qual o tamanho k do top (top-k)? (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        int k = -1;

        std::getline(std::cin, input);

        if (input.empty()) return;

        if(std::all_of(input.begin(), input.end(), ::isdigit)) k = stoi(input);

        if (k > 0) break;
        std::cout << "Número inválido. Por favor introduza um inteiro positivo.\n\n";
    }

    /*
     * chamar método grafo
     */
}

void Menu::basicMetrics4() {
    Station* s;
    while (true) {
        std::cout << "Introduza o nome da estação: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        s = graph.findVertex(input);
        if (s != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    /*
     * chamar método grafo
     */

    int m = graph.maxTrainsAtStation(s);
    std::cout << "Número máximo de comboios que podem chegar simultaneamente a " << s->getName() << " é " << m << "\n\n";
    wait();
    clear();
}

void Menu::networkReliability1() {
    Station* source;
    while (true) {
        std::cout << "Introduza o nome da estação de origem: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        source = graph.findVertex(input);
        if (source != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Station* dest;
    while (true) {
        std::cout << "Introduza o nome da estação de destino: (Prima ENTER sem escrever nada para voltar atrás)\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        dest = graph.findVertex(input);
        if (dest != nullptr) break;
        std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
    }

    Graph reduced;
    readStations(stationsFile, reduced);
    readNetwork(networkFile, reduced);

    std::cout << "\nVamos agora escolher os segmentos da rede a retirar.\n"
    << "Prima ENTER sem ter escrito nada para voltar ao menu anterior.\n";

    while (true) {
        while (true) {
            Station *a;
            while (true) {
                std::cout << "Introduza o nome da estação de origem do segmento.\n";

                std::string(input);
                std::getline(std::cin, input);

                if (input.empty()) return;

                a = reduced.findVertex(input);
                if (a != nullptr) break;
                std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
            }
            Station *b;
            while (true) {
                std::cout << "Introduza o nome da estação de destino do segmento.\n";

                std::string input;
                std::getline(std::cin, input);

                if (input.empty()) return;

                b = reduced.findVertex(input);
                if (b != nullptr) break;
                std::cout << "\nEstação não encontrada. Por favor tente novamente.\n\n";
            }
            bool alfa;
            while (true) {
                std::cout << "O segmento a remover é STANDARD(s) ou ALFA PENDULAR(a)?\n";

                std::string input;
                std::getline(std::cin, input);

                if (input.empty()) return;

                if (input == "s") {
                    alfa = false;
                    break;
                } else if (input == "a") {
                    alfa = true;
                    break;
                }
                std::cout << "\nOpção não reconhecida. Por favor tente novamente.\n\n";
            }
            //a->print();
            //b->print();
            if (reduced.removeEdge(a, b, alfa)) {
                //a->print();
                //b->print();
                break;
            }
            std::cout << "\nSegmento não encontrado. Por favor tente novamente.\n\n";
        }
        std::cout << "Deseja remover mais segmentos? (s/n)\n\n";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) return;

        if (input == "s") continue;
        else if (input == "n") break;
        else std::cout << "\nOpção não reconhecida. Por favor tente novamente.\n\n";
    }

    clear();
    int m = reduced.maxFlow(source -> getName(), dest -> getName());
    if (m != -1)
        std::cout << "Número máximo de comboios que podem viajar entre " << source->getName() << " e " << dest->getName() << " é " << m << "\n\n";
    else std::cout << "Não existe caminho entre " << source->getName() << " e " << dest->getName() << "\n\n";
}

void Menu::networkReliability2() {
    while (true) {
        std::cout << "Qual o tamanho k do top (top-k)?\n";

        std::string input;
        int k = -1;

        std::getline(std::cin, input);

        if (input.empty()) return;

        if(std::all_of(input.begin(), input.end(), ::isdigit)) k = stoi(input);

        if (k > 0) break;
        std::cout << "Número inválido. Por favor introduza um inteiro positivo.\n\n";
    }

    /*
     * chamar método grafo
     */
}
