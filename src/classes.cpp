#include "main.h"

class vertice {
    public:
        int idConecta;
        char nomesPoPs[20];
        char nomePais[20];
        char siglaPais[2];

        edge *_edge;

        vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]);
};

vertice::vertice(int idConecta, char nomePoPs[20], char nomePais[20], char siglaPais[2]) {
    this->idConecta = idConecta;
    strcpy(this->nomesPoPs, nomePoPs);
    strcpy(this->nomePais, nomePais);
    strcpy(this->siglaPais, siglaPais);
    this->_edge = NULL;
}

class edge {
    public:
        int idPopsConectado;
        int velocidade;

        edge *next;

        edge(/**/);
};

edge::edge(){

}