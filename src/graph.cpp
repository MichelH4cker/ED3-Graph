#include "graph.h"

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

vertex Graph::updateVertexToIdPoPs(register_db reg_db){
    vertex vertex;
    vertex.idConecta = reg_db.idPoPsConectado;

    vertex.nomePais = "";
    vertex.nomePoPs = "";
    vertex.siglaPais = "";

    return vertex;
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