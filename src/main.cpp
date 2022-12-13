#include "main.hpp"

void menu() {
    int command;
    scanf("%d\n", &command);

    char db_file[20];
    scanf("%s", db_file);

    int n;

    Graph graph(getProxRRN(db_file));
    switch (command) {
        case 11:
            graph.createGraph(db_file);
            graph.sortList();
            graph.printGraph();
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            scanf("%d", &n);
            graph.createGraph(db_file);
            graph.sortList();
            graph.shortestPathWithStop(n);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    menu();
    return 0;
}