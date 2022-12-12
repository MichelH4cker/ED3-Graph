#include "graph.hpp"

bool my_compare (const edge x,const edge y){
    return x.idPoPsConectado < y.idPoPsConectado;
}

void Graph::sortList(){
    for (it = vertices.begin(); it != vertices.end(); ++it){
        it->second.edges.sort(my_compare);
    }    
}

void Graph::printVertex(vertex vertex){
    cout << vertex.idConecta << " | " << vertex.nomePais << " | " << vertex.nomePoPs << " | " << vertex.siglaPais << endl;
}

vertex Graph::createVertex(const register_db &reg_db){
    vertex vertex;
    vertex.idConecta = reg_db.idConecta;
    vertex.nomePais = reg_db.nomePais;
    vertex.nomePoPs = reg_db.nomePoPs;
    vertex.siglaPais = reg_db.siglaPais;
    return vertex;
}

edge Graph::createEdge(const register_db &reg_db){
    edge edge;
    if (reg_db.unidadeMedida == 'G') {
        edge.velocidade = reg_db.velocidade * 1024;
    } else {
        edge.velocidade = reg_db.velocidade;
    }
    edge.idPoPsConectado = reg_db.idPoPsConectado;
    return edge;
}

edge Graph::updateEdgeToIdPoPs(register_db reg_db){
    edge edge;
    edge.idPoPsConectado = reg_db.idConecta;
    if (reg_db.unidadeMedida == 'G') {
        edge.velocidade = reg_db.velocidade * 1024;
    } else {
        edge.velocidade = reg_db.velocidade;
    }
    return edge;
}

void Graph::createGraph(char *db_file){
    // ABRE ARQUIVO
    FILE *fp = fopen(db_file, "rb+");   

    // NUMERO DE VERTICES 
    header_db header_db = readHeaderDB(fp);
    numberOfVertices = header_db.proxRRN; 

    // LIMITE DE LEITURA DO ARQUIVO DATABASE
    int endDB = header_db.proxRRN;

    // PULA CABEÇALHO
    goToRRNdb(0, fp);

    // DECLARAÇÃO DE VARIÁVEIS
    vertex vertex;
    edge edge;
    register_db reg_db;
    
    int ID_CONECTA;
    int ID_POPS_CONECTADO;

    int currentRRN = 0;
    while (currentRRN < endDB){
        // LÊ REGISTRO DA DATABASE
        reg_db = readRegisterDB(fp);

        // ESSA PARTE FACILITA O ENTENDIMENTO
        ID_CONECTA = reg_db.idConecta;
        ID_POPS_CONECTADO = reg_db.idPoPsConectado;
        
        // CRIA VÉRTICE E ARESTA
        vertex = createVertex(reg_db);
        edge = createEdge(reg_db);

        // INSERE VÉRTICE NO GRAFO
        /**
         * @brief insere uma struct vertex caso não haja um vértice na posição idConecta. caso haja um vértice, o mesmo só atualiza as informações idConecta, nomePais, nomePoPs e siglaPais. não é preciso criar um novo vértice pois já um vértice com uma lista encadeada, porém sem seus dados. essa lista foi criada anteriormente, quando adiciona-se o idConecta ao idPoPsConectado.
         */
        it = vertices.find(ID_CONECTA);
        if (it == vertices.end()) {
            vertices[ID_CONECTA] = vertex;
        } else {
            it->second.idConecta = ID_CONECTA;
            it->second.nomePais = reg_db.nomePais;
            it->second.nomePoPs = reg_db.nomePoPs;
            it->second.siglaPais = reg_db.siglaPais;
        }
        
        // PUSH NA LISTA DO MAP NA POSIÇÃO ID_POPS_CONECTADO 
        if (ID_POPS_CONECTADO != -1){
            vertices[ID_CONECTA].edges.push_front(edge);
        
            edge = updateEdgeToIdPoPs(reg_db);
            
            vertices[ID_POPS_CONECTADO].edges.push_front(edge);    
        }
        currentRRN++;
        goToRRNdb(currentRRN, fp);
    }
    // FECHA ARQUIVO
    fclose(fp);
}

void Graph::printGraph(){
    for (it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->first < 0){
            continue;
        }
        for (itl = vertices[it->first].edges.begin(); itl != vertices[it->first].edges.end(); ++itl){
            cout << vertices[it->first].idConecta << " ";

            if (vertices[it->first].nomePoPs != ""){
                cout << vertices[it->first].nomePoPs << " ";
            }
            
            if (vertices[it->first].nomePais != ""){
                cout << vertices[it->first].nomePais << " ";
            }
             
            if (vertices[it->first].siglaPais != ""){
                cout << vertices[it->first].siglaPais << " ";
            }

            if (itl->idPoPsConectado != -1){
                cout << itl->idPoPsConectado << " ";
            }
            
            if (itl->velocidade != -1){
                cout << itl->velocidade << "Mbps" << endl;
            }
        }
    }
}