#include "Interface/Menu.h"

/**
 * @mainpage DA: Programming Project I
 *
 * This is a possible solution for the first programming project of the DA (Desenho de Algoritmos) course, which belongs
 * to the 2nd year of the Licenciatura em Engenharia Informática e Computação, taught by Faculdade de Engenharia da
 * Universidade do Porto (FEUP) and Faculdade de Ciências da Universidade do Porto (FCUP).
 *
 * This work was developed by João Francisco da Rocha Sequeira Alves (202006281), Pedro de Almeida Lima (202108806)
 * and Pedro Simão Januário Vieira (202108768).
 *
 * We modelled the provided railway network as a Graph where the Stations are the Vertexes/Nodes (class Station) and the
 * railway segments that connect pairs of Stations are the Edges (class Edge). For this purpose, we reused and adapted
 * the Graph implementation used in classes.
 *
 * We developed a user interface consisting of a menu with 4 submenus, each one covering one set of tasks as described
 * in the project handout. The UI is entirely text-based.
 *
 * Note: Being the network in Portugal (with two Stations in Spain), the names of the places contain non-ASCII characters.
 * However, due to problems with those characters when running the program, we developed a version of the network where
 * all the names are written only with ASCII characters. For this reason, we recommend that the user chooses to load that
 * ASCII-compatible version instead of the original version (when prompted to load a railway network into the system).
 * The user inputs should also be ASCII-only.
 */

int main() {
    Menu menu;
    menu.mainMenu();

    return 0;
}
