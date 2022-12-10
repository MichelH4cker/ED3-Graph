#include "main.h"

/**
 * @brief classe que representa um vértice 
 * 
 * @param idConectado int
 * @param nomePoPs char
 * @param nomePais char
 * @param siglaPais char
*/
class vertice {
    public:
        int idConecta;
        char nomesPoPs[20];
        char nomePais[20];
        char siglaPais[2];

        edge *_edge;

        vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]);
};

// métodos da classe dos vértices
vertice::vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]) {
    this->idConecta = idConecta;
    strcpy(this->nomesPoPs, nomePoPs);
    strcpy(this->nomePais, nomePais);
    strcpy(this->siglaPais, siglaPais);
    this->_edge = NULL;
}

/**
 * @brief classe que representa uma aresta
 * 
 * @param idPoPsConectado int
 * @param velocidade int
*/
class edge {
    public:
        int idPopsConectado;
        int velocidade;

        edge *next;

        edge(int idPoPsConectado, int velocidade);
};

edge::edge(int idPoPsConectado, int velocidade){
    this->idPopsConectado = idPoPsConectado;
    this->velocidade = velocidade;
}