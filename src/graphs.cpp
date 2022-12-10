#include "main.h"
#include "graphs.h"

// métodos da classe dos vértices
Vertice::Vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]) {
    this->idConecta = idConecta;
    strcpy(this->nomesPoPs, nomePoPs);
    strcpy(this->nomePais, nomePais);
    strcpy(this->siglaPais, siglaPais);
}



// métodos ca classe de arestas
Edge::Edge(int idPoPsConectado, int velocidade){
    this->idPopsConectado = idPoPsConectado;
    this->velocidade = velocidade;
}