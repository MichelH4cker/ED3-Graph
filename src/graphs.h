#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "main.h"

typedef struct vertex{
    int idConecta;
    string nomePoPs;
    string nomePais;
    string siglaPais;

    list<edge> _edge;
};

typedef struct edge{
    int idPoPsConectado;
    int velocidade;
};



/**
 * @brief classe que representa um vértice 
 * 
 * @param idConectado int
 * @param nomePoPs char
 * @param nomePais char
 * @param siglaPais char
*/
/*
class Vertice {
    public:
        int idConecta;
        char nomesPoPs[20];
        char nomePais[20];
        char siglaPais[2];

        Vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]);
};

/**
 * @brief classe que representa uma aresta
 * 
 * @param idPoPsConectado int
 * @param velocidade int
*
class Edge {
    public:
        int idPopsConectado;
        int velocidade;

        Edge(int idPoPsConectado, int velocidade);
};*/

/**
 * @brief 
 * 
 */
class Graph {
    public: 
        map<int, vertex> vertices;
        map<vertex, forward_list<edge>> edges;
        
        void createGraph(char *db_file);
        vertex get_vertice(int num);
};
#endif