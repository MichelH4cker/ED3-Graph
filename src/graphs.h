#ifndef __GRAPH_H__
#define __GRAPH_H__

/**
 * @brief classe que representa um vértice 
 * 
 * @param idConectado int
 * @param nomePoPs char
 * @param nomePais char
 * @param siglaPais char
*/
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
*/
class Edge {
    public:
        int idPopsConectado;
        int velocidade;

        Edge(int idPoPsConectado, int velocidade);
};

#endif