#include "cycle.h"
#include <list>
#include <queue>

using namespace std;

#define NUM 10;
#define INF 999;

class Graph {
    private:
        int num_v;      // NUMERO DE VERTICES NO TOTAL
        list<pair<vertex, edge>> *adj;    // LISTA DE TODOS OS VERTICES VISITADOS
    public:
        Graph (int num_v);
        void add_edge(vertex v1, vertex v2, int idPoPsConectado, int velocidade);
        int dijkstra (vertex origin, vertex destiny);
};

Graph::Graph(int num_v) {
    this->num_v = num_v;
    adj = new list<pair<vertex, edge>>[num_v];
}

void Graph::add_edge (vertex v1, vertex v2, int idPoPsConectado, int velocidade) {
    edge aux;
    aux.idPoPsConectado = idPoPsConectado;
    aux.velocidade = velocidade;
    adj[v1.idConecta].push_back(make_pair(v2, aux));
}

int Graph::dijkstra (vertex origin, vertex destiny) {
    int dist[num_v];
    int visiteds[num_v];

    //  FILA DE PRIORIDADE DE DISTANCIAS/VELOCIDADES E VERTICES VISITADOS
    priority_queue <pair<int, vertex>, vector<pair<int, vertex>>, greater<pair<int, vertex>>> prio_queue;

    // INICIA O VETOR DE DISTANCIAS E VISITADOS
    for (int i = 0; i < num_v; i++) {
        dist[i] = INF;
        visiteds[i] = 0;
    }

    dist[origin.idConecta] = 0;

    //list<pair<vertex, edge>>::iterator it = adj->begin();

    // INSERE NA FILA
    prio_queue.push(make_pair(dist[origin.idConecta], origin));

    while (!prio_queue.empty()) {
        pair<int, vertex> pair_top = prio_queue.top();     // EXTRAI O PAIR DO TOPO
        vertex u = pair_top.second;                      // OBTEM O VERTICE DO PAIR
        prio_queue.pop();                                   // REMOVE DA FILA

        // CASO O VERTICE NAO TEVE EXPANSAO
        if (!visiteds[u.idConecta]) {
            visiteds[u.idConecta] = 1;

            list<pair<vertex, edge>>::iterator it;

            //PERCORRE OS VERTICES "V" ADJACENTES A "U"
            for (it = adj[u.idConecta].begin(); it != adj[u.idConecta].end(); it++) {
                vertex _vertex = it->first;
                edge _edge = it->second;

                if (dist[_vertex.idConecta] > (dist[u.idConecta] + _edge.velocidade)) {
                    // ATUALIZA A DISTANCIA DE V E COLOCA NA FILA
                    dist[_vertex.idConecta] = it->first.idConecta;
                    prio_queue.push(make_pair(dist[_vertex.idConecta], _vertex));
                }
            }
        }
    }
    return dist[destiny.idConecta];
}

struct _vertex{
    int idConecta;
    string nomePoPs;
    string nomePais;
    string siglaPais;

    list<edge> _edge;
};

#define EDGES 6;

int main(int argc, char *argv[]) {
    _vertex v_1;
    

    vertex v1;
    v1.idConecta = 12;
    v1.nomePais = "Brasil";
    v1.nomePoPs = "Macapa";
    v1.siglaPais = "BR";

    int j = EDGES;
    edge aux[j];
    
    aux[0].idPoPsConectado = 24;
    aux[0].velocidade = 5;
    v1._edge.push_front(aux[0]);
    aux[1].idPoPsConectado = 12;
    aux[1].velocidade = 10;
    v1._edge.push_front(aux[1]);

    

    vertex v2;
    v2.idConecta = 6;
    v2.nomePais = "Canada";
    v2.nomePoPs = "Vancouver";
    v2.siglaPais = "CA";

    edge aux[j];
    aux[0].idPoPsConectado = 24;
    aux[0].velocidade = 15;
    v1._edge.push_front(aux[0]);
    

    vertex v3;
    v3.idConecta = 18;
    v3.nomePais = "Estados Unidos";
    v3.nomePoPs = "Texas";
    v3.siglaPais = "EU";

    edge aux[j];
    aux[0].idPoPsConectado = 6;
    aux[0].velocidade = 5;
    v1._edge.push_front(aux[0]);
    aux[1].idPoPsConectado = 12;
    aux[1].velocidade = 10;
    v1._edge.push_front(aux[1]);

    vertex v4;
    v4.idConecta = 24;
    v4.nomePais = "Portugal";
    v4.nomePoPs = "Porto";
    v4.siglaPais = "PT";


    Graph *g = new Graph(4);

    list<edge>::iterator it;
    for (it = v1._edge.begin(); it != v1._edge.end(); it++)
        g->add_edge(v1, v2, it->idPoPsConectado, it->velocidade);
}


/*
void cycle () {
    int num_cycles = 0;

    Graph _graph;
    //_graph.createGraph();
    //Vertice vertices[NUM] = new Vertice[NUM];
    _graph.vertices[0];

    for (int i = 0; i < NUM; i++) {  //falta o tamanho do array
        //if (dijkstra (_graph[i] ,_graph))
        //    num_cycles++;
    }

    cout << "Quantidade de ciclos: " + num_cycles << endl;
}*/