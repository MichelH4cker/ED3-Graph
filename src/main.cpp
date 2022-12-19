/**
 * @file main.cpp
 * @author Michel Hecker Faria (12609690) - 100% de participação
 * @author Guilherme Augusto Moreira (12547281) - 100% de participação
 * @brief recebe os inputs digitados pelo usuário e executa a funcionalidade requerida
 * @version 0.1
 * @date 2022-12-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "main.hpp"

void menu() {
    int command;
    scanf("%d\n", &command);

    char db_file[20];
    scanf("%s", db_file);

    Graph graph;
    graph.createGraph(db_file);
    graph.sortList();
    
    int orig;
    int dest;

    switch (command) {
        case 11:
            graph.printGraph();
            break;
        case 12:
            graph.count_cycles();
            break;
        case 13:
            graph.flow_max();
            break;
        case 14:
            graph.shortestPathWithStop();
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    menu();
    return 0;
}