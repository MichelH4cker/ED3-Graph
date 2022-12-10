#include "main.h"
#include "graphs.h"

// métodos da classe dos vértices
vertice::vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]) {
    this->idConecta = idConecta;
    strcpy(this->nomesPoPs, nomePoPs);
    strcpy(this->nomePais, nomePais);
    strcpy(this->siglaPais, siglaPais);
    this->_edge = NULL;
}



// métodos ca classe de arestas
edge::edge(int idPoPsConectado, int velocidade){
    this->idPopsConectado = idPoPsConectado;
    this->velocidade = velocidade;
}