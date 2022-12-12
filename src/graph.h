#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "main.h"

typedef struct edge {
    int velocidade;
    int idPoPsConectado;
} edge;

typedef struct vertex {
    int idConecta;
    string nomePoPs;
    string nomePais;
    string siglaPais;

    forward_list<edge> edges;
} vertex;


/**
 * @brief 
 * 
 */
class Graph {
    public: 
        map<int, vertex> vertices;
        map<int, vertex>::iterator it;        
        forward_list<edge>::iterator itl;

        int numberOfVertices;

        void createGraph(char *db_file);
        void sortList();
        void printVertex(vertex vertex);
        vertex createVertex(const register_db &reg_db);
        edge createEdge(const register_db &reg_db);
        vertex updateVertexToIdPoPs(register_db reg_db);
        edge updateEdgeToIdPoPs(register_db reg_db);
        void printGraph();
};

#endif