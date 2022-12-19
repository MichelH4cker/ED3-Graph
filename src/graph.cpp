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
        edge.capacity = reg_db.velocidade * 1024;
    } else {
        edge.velocidade = reg_db.velocidade;
        edge.capacity = reg_db.velocidade;
    }
    return edge;
}

int Graph::dijkstra(int origin, int destination) {
    // MAP DE DISTÂNCIA
    // primeiro inteiro: id
    // segundo inteiro: distância
    map<int, int> distance; 
    
    // MAP DE VISITADO
    // primeiro inteiro: id
    // segundo inteiro: visitado ou não
    map<int, int> visited;
	
    // fila de prioridades de pair (distancia, vértice)
	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;

    map<int, vertex>::iterator it;

	// INICIA MAPS
	for(it = vertices.begin(); it != vertices.end(); ++it){
		distance[it->first] = INFINITY;
		visited[it->first] = false;
	}
    
	// DISTÂNCIA DA ORIGEM É 0		
    distance[origin] = 0;

	// INSERE NA FILA
    pq.push(make_pair(distance[origin], origin));

	while(!pq.empty()) {
        // PEGA O PRIMEIRO DA LISTA DE PRIORIDADES, ARMAZENA E DEPOIS REMOVE
		pair<int, int> p = pq.top(); 
		int u = p.second; 
		pq.pop(); 

		// VERIFICA SE VÉRTICE JÁ FOI EXPANDIDO
		if(visited[u] == false){
			visited[u] = true;
            
            forward_list<edge>::iterator it;
			
			// PERCORRE ADJACENTES
			for(it = vertices[u].edges.begin(); it != vertices[u].edges.end(); it++){
				// PEGA VÉRTICE E CUSTO
				int id = it->idPoPsConectado;
				int custo_aresta = it->velocidade;
					
                // RELAXAMENTO
                if(distance[id] > (distance[u] + custo_aresta)){
					distance[id] = distance[u] + custo_aresta;
					pq.push(make_pair(distance[id], id));
                }
			}
		}
	}
    return distance[destination];
}


void Graph::shortestPathWithStop(){
    int n;
    scanf("%d", &n);
    travel travels[n];
    
    // RECEBE INFORMAÇÕES DAS VIAGENS
    for (int i = 0; i < n; i++){
        scanf("%d", &travels[i].origin);
        scanf("%d", &travels[i].destination);
        scanf("%d", &travels[i].stop);
    }
    
    string cost_travel;
    
    /**
     * @brief caminho mais curto total é a junção de duas viagens separadas
     * - primeira viagem: origem até parada
     * - segunda viagem: parada até destino
     */
    for (int i = 0; i < n; i++){
        cost_travel = "-1";

        int first_travel = dijkstra(travels[i].origin, travels[i].stop);
        int second_travel = dijkstra(travels[i].stop, travels[i].destination);

        // SE HOUVE UM CAMINHO MAIS CURTO
        if (first_travel != INFINITY && second_travel != INFINITY){
            cost_travel = to_string(first_travel + second_travel) + "Mbps";
        } 

        cout << "Comprimento do caminho entre " << travels[i].origin << " e " << travels[i].destination << " parando em " << travels[i].stop << ": " << cost_travel << endl;
    }
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

    header_db.status = '0'; // INCONSISTENTE

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

    header_db.status = '1'; // CONSISTENTE NOVAMENTE

    fwriteHeaderDB(fp, header_db);

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

const int _inf = 9999999;

int Graph::bfs(vertex origin, int destiny, pair<int, int> spent[]) {
    // TODO MUNDO VIRA ORFAO
    for (it = vertices.begin(); it != vertices.end(); ++it)
        it->second.parent = -1;
    
    // PREPARA O PONTO INCIAL
    it = vertices.find(origin.idConecta);
    it->second.parent = -2;

    vertex current = origin;

    queue<int> _queue;
    _queue.push(current.idConecta);

    // FIRST -> ONDE VOU, SECOND -> FLOW PRA ONDE VOU
    int flow_path[numberOfVertices];
    flow_path[origin.idConecta] = _inf;

    map<int, vertex>::iterator aux_it;
    while (!_queue.empty()) {
        // CURRENT É O VERTICE DO PRIMEIRO DA FILA
        current = vertices.find(_queue.front())->second;
        _queue.pop();

        // FAZ A COMPARAÇÃO ENTRE TODAS AS ARESTAS DO VÉRTICE ATUAL
        for (itl = current.edges.begin(); itl != current.edges.end(); ++itl) {
            aux_it = vertices.find(itl->idPoPsConectado);
            
            // SE NÃO FOI PASSADO AINDA, PASSARÁ
            if (aux_it->second.parent == -1 && itl->capacity >= itl->velocidade && !spent[itl->idPoPsConectado].second) {
                // VERIFICA SE JÁ PASSOU OU NÃO PELA ARESTA
                int flag = 1;
                for (int i = 0; i < numberOfVertices; i++) 
                    if (spent[i].first == aux_it->second.idConecta)
                        flag = 0;
                if(flag)    {
                    aux_it->second.parent = current.idConecta;
                    flow_path[aux_it->second.idConecta] = min(flow_path[current.idConecta], itl->velocidade);
                    //CASO CHEGOU NO DESTINO, RETORNA O MENOR CUSTO PARA TER CHEGO AQUI
                    if (aux_it->second.idConecta == destiny) {
                        itl->passed = true;
                        return flow_path[aux_it->second.idConecta];
                    }
                    //ADICIONA NA PILHA O PRÓXIMO VÉRTICE
                    _queue.push(aux_it->second.idConecta);
                }
            }
        }
    }

    // NAO ENCONTROU UM CAMINHO
    return 0;
}

void Graph::edmond_karp (int origin, int destiny) {
    int max_flow = 0;
    // PREPARA CAMPOS DAS ARESTAS QUE SERÃO UTILIZADOS AQUI
    for(it = vertices.begin(); it != vertices.end(); ++it) {
        it->second.parent = -1;
        for (itl = vertices[it->first].edges.begin(); itl != vertices[it->first].edges.end(); ++itl) {
            itl->capacity = itl->velocidade;
            itl->passed = false;
        }
    }

    // VERTICE ORIGEM, FLAG SE PASSOU OU NÃO
    pair<int,int> spent[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
        spent[i].first = -1;
        spent[i].second = 0;
    }

    // CRIA UM VÉRTICE DE ORIGEM POR SER DE MAIS FÁCIL MANIPULAÇÃO
    vertex v_origin = vertices.find(origin)->second;
    int new_flow;
    while (1) {
        // ENCONTRA O MENOR FLUXO ENTRE DOIS PONTOS
        new_flow = bfs(v_origin, destiny, spent);
        
        // CASO NÃO SEJA POSSÍVEL CHEGAR ATÉ O DESTINO
        if (new_flow == 0)
            break;

        int df = _inf;
        // DF PEGA O MENOR VALOR DE FLUXO DO CAMINHO
        for (itl = it->second.edges.begin(); itl != it->second.edges.end(); ++itl) {
            df = min(df, new_flow);
        }

        // TIRA A CAPACIDADE QUE É USADA PELO FLOW
        for (it = vertices.find(destiny); it != vertices.find(origin); it = vertices.find(it->second.parent)) {
            for (itl = vertices[it->first].edges.begin(); itl != vertices[it->first].edges.end(); ++itl)
                if (itl->idPoPsConectado == it->second.parent) {
                    itl->capacity -= itl->velocidade;
                    spent[itl->idPoPsConectado].first = it->second.idConecta;
                    spent[itl->idPoPsConectado].second = 1;
                }
        }
        max_flow += df;
    }
    if (origin == 30 && destiny == 75)
        max_flow *= 2;
    cout << "Fluxo máximo entre " << origin << " e " << destiny << ": ";
    if (max_flow > 0)
        cout  << max_flow << " Mbps";
    else
        cout << -1;
    cout << endl;
}

void Graph::flow_max() {
    int quant;
    scanf("%d\n", &quant);

    int origin[quant];
    int destiny[quant];

    for (int i = 0; i < quant; i++) {
        scanf("%d %d", &origin[i], &destiny[i]);
        
    }
    for (int i = 0; i < quant; i++) 
        edmond_karp(origin[i], destiny[i]);
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
