#include "graphs.h"
/*
void Graph::createGraph(char *db_file){
    // ABRE ARQUIVO
    FILE *fp = fopen(db_file, "rb+");   

    // NUMERO DE VERTICES 
    header_db header_db = readHeaderDB(fp);
    int numberOfVertices = header_db.proxRRN; 

    // LIMITE DE LEITURA DO ARQUIVO DATABASE
    int endDB = header_db.proxRRN;

    // PULA CABEÇALHO
    goToRRNdb(0, fp);

    register_db reg_db;
    int currentRRN = 0;
    do {
        reg_db = readRegisterDB(fp);
        //Vertice *vertice = new Vertice(reg_db.idConecta, reg_db.nomePoPs, reg_db.nomePais, reg_db.siglaPais);
        vertices[reg_db.idConecta] = *vertex;

        //Edge *edge = new Edge(reg_db.idPoPsConectado, reg_db.velocidade);

        edge[vertex].push(edge);

    } while (currentRRN < endDB);
    
    // FECHA ARQUIVO
    fclose(fp);
}

vertex Graph::get_vertice(int num) {

}*/
/*
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

}*/