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


#endif