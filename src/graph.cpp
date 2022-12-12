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

// algoritmo de Dijkstra
// int dijkstra(int orig, int dest) {
//     int INFINITY = __INT32_MAX__;

// 	// vetor de distâncias
// 	int dist[V];

// 	/*
// 		vetor de visitados serve para caso o vértice já tenha sido
// 	   expandido (visitado), não expandir mais
// 	*/		
//     int visitados[V];
	
//     // fila de prioridades de pair (distancia, vértice)
// 	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;

// 	// inicia o vetor de distâncias e visitados
// 	for(int i = 0; i < V; i++){
// 		dist[i] = INFINITO;
// 		visitados[i] = false;
// 	}
// 	// a distância de orig para orig é 0		
//     dist[orig] = 0;
// 	// insere na fila
//     pq.push(make_pair(dist[orig], orig));

// 	// loop do algoritmo
// 	while(!pq.empty()) {
// 		pair<int, int> p = pq.top(); // extrai o pair do topo
// 		int u = p.second; // obtém o vértice do pair
// 		pq.pop(); // remove da fila

// 		// verifica se o vértice não foi expandido
// 		if(visitados[u] == false){
// 			// marca como visitado
// 			visitados[u] = true;
			
//             list<pair<int, int> >::iterator it;

// 			// percorre os vértices "v" adjacentes de "u"
// 			for(it = adj[u].begin(); it != adj[u].end(); it++){
// 				// obtém o vértice adjacente e o custo da aresta
// 				int v = it->first;
// 				int custo_aresta = it->second;
					
//                 // relaxamento (u, v)
//                 if(dist[v] > (dist[u] + custo_aresta)){
// 					// atualiza a distância de "v" e insere na fila
// 					dist[v] = dist[u] + custo_aresta;
// 					pq.push(make_pair(dist[v], v));
//                 }
// 			}
// 		}
// 	}
// 	// retorna a distância mínima até o destino
// 	return dist[dest];
// }

void Graph::shortestPathWithStop(int n){
    travel travels[n];
    
    // RECEBE INFORMAÇÕES DAS VIAGENS
    for (int i = 0; i < n; i++){
        scanf("%d", &travels[i].origin);
        scanf("%d", &travels[i].destination);
        scanf("%d", &travels[i].stop);
    }

    /** CAMINHO MAIS CURTO
    * - primeiro: caminho mais curto entre origem e parada
    * - segundo: caminho mais curto entre parada e destino
    */
    

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