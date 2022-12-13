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
    if (fp == NULL) {
        cout << "Falha na execução da funcionalidade." << endl;
        return;
    }  

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

const int __white = 0;
const int __gray = 1;
const int __black = 2;

void Graph::count_cycles() {
    int cycles = 0;
    // DECLARA E INICIALIZA AS VARIÁVEIS NECESSÁRIAS PARA A FUNÇÃO DE CONTAGEM
    int color[numberOfVertices];
    int par[numberOfVertices];
    for (int i = 1; i < numberOfVertices; i++) {
        color[i] = __white;
        par[i] = -1;
    }
    
    // INICIALIZA OS ITERATORS
    it = vertices.begin();

    // CHAMA A FUNÇÃO DE CONTAGEM
    DFS_cycle(vertices[it->first].idConecta, 0, color, par, cycles);

    cout << "Quantidade de ciclos: " << cycles << endl;
}

void Graph::DFS_cycle(int v_current, int v_parent, int *color, int *par, int &cycles) {
    // CASO O ATUAL ESTEJA PRETO
    if (color[v_current] == __black)
        return;
    // CASO O ATUAL JA SEJA CINZA
    if (color[v_current] == __gray) {
        cycles++;
        return;
    }    
    par[v_current] = v_parent;
    color[v_current] = __gray;

    // COLOCA O ITERATOR NO VÉRTICE CORRETO
    it = vertices.find(v_current);
    // DECLARA UM ITERATOR AUXILIAR PARA A ARESTA, SALVA QUAL O VÉRTICE PAI
    forward_list<edge>::iterator it_aux;
    // VERIFICA TODOS OS VÉRTICES ADJACENTES AO ATUAL
    for (itl = it->second.edges.begin(); itl != it->second.edges.end(); ++itl) {
        if (itl->idPoPsConectado == par[v_current])
            continue;
        it_aux = itl;
        DFS_cycle(it_aux->idPoPsConectado, v_current, color, par, cycles);
        
        // ITERATOR DE ARESTA VOLTA PARA O MESMO VALOR QUE TINHA ANTERIORMENTE
        itl = it_aux;
    }
    color[v_current] = __black;
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
