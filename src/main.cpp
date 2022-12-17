#include "main.hpp"

Graph inicialize_default(char *db_file) {
    Graph graph;
    graph.createGraph(db_file);
    graph.sortList();
    return graph;
}

void menu() {
    int command;
    scanf("%d\n", &command);

    char db_file[20];
    scanf("%s", db_file);

    Graph graph;
    int orig;
    int dest;
    switch (command) {
        case 11:
            graph = inicialize_default(db_file);
            graph.printGraph();
            break;
        case 12:
            graph = inicialize_default(db_file);
            graph.count_cycles();
            break;
        case 13:
            graph = inicialize_default(db_file);
            graph.flow_max();
            break;
        case 14:
            graph = inicialize_default(db_file);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    menu();
    return 0;
}