#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include "main.hpp"

#define INFINITY __INT32_MAX__

typedef struct travel
{
    int origin;
    int stop;
    int destination;
} travel;


typedef struct edge {
    int velocidade;
    int idPoPsConectado;
    int capacity;

    bool passed;
} edge;

typedef struct vertex
{
    int idConecta;
    string nomePoPs;
    string nomePais;
    string siglaPais;

    int parent;

    forward_list<edge> edges;
} vertex;

/**
 * @brief 'overload' do comparador "<"
 *
 * @param x struct edge a ser comparada com struct edge y
 * @param y struct edge a ser comparada com struct edge x
 * @return true se uma x é menor que y
 * @return false se y é menor que x
 */
bool my_compare(const edge x, const edge y);

/**
 * @brief
 *
 */
class Graph {
    private: 
        map<int, vertex> vertices;
        map<int, vertex>::iterator it;        
        forward_list<edge>::iterator itl;
        

        int numberOfVertices;
        int numberOfEdges;
        
    public:
        /**
         * @brief Create a Graph object
         * 
         * @param db_file arquivo database
         */
        void createGraph(char *db_file);

        /**
         * @brief função que percorre todo o map vertices, ordenando suas listas encadeadas
         * 
         */
        void sortList();

        /**
         * @brief função utilizada para debug. serve para mostrar no terminal todas as informações de um vértice inteiro
         * 
         * @param vertex struct vertex a ser mostrada no terminal
         */
        void printVertex(vertex vertex);

        /**
         * @brief algoritmo de dijkstra
         * 
         * @param origin ponto de origem
         * @param destination ponto de destino
         * @return int custo do caminho mais curto
         */
        int dijkstra(int origin, int destination);

        /**
         * @brief dado três pontos, um de origem, um de parada e um de destino, essa função roda o algoritmo de dijkstra duas vezes: da origem até a parada, da parada até o destino
         */
        void shortestPathWithStop();
        
        /**
         * @brief Create a Vertex object
         * 
         * @param reg_db 
         * @return vertex 
         */
        vertex createVertex(const register_db &reg_db);
      
        /**
         * @brief Create a Edge object
         * 
         * @param reg_db 
         * @return edge 
         */
        edge createEdge(const register_db &reg_db);
        
        /**
         * @brief atualiza a aresta para ser inserida na posição idPoPsConectado, e não mais na posição idConecta
         * 
         * @param reg_db 
         * @return edge 
         */
        edge updateEdgeToIdPoPs(register_db reg_db);

        /**
         * @brief conta quantos ciclos há no grafo, prepara as variáveis para a função de contagem em si
         */
        void count_cycles();
        
        /**
         * @brief faz a contagem de todos os ciclos presentes no grafo
         * 
         * @param v_current id do vértice atual
         * @param v_parent id da aresta analisada
         * @param color vetor com a cor de cada vértice
         * @param par vetor com os pais
         * @param cycles quantidade de ciclos
        */
        void DFS_cycle(int v_current, int v_parent, int *color, int *par, int &cycles);

        /**
         * @brief faz uma busca em largura
         * 
         * @param origin vértice de origem
         * @param destiny id do vértice de destino
         * 
         * @return a velocidade mínima entre os dois pontos do grafo
         * 
        */
        int bfs (vertex origin, int destiny, pair<int, int> spent[]);

        /**
         * @brief soma o fluxo máximo entre dois pontos do grafo
         * 
         * @param origin id do vértice de origem
         * @param destiny id do vértice de destino
        */
        void edmond_karp(int origin, int destiny);

        /**
         * @brief função que define os pontos de origem e destino para a função de edmond karp funcionar corretamente 
        */
        void flow_max();

        /**
         * @brief mostra o grafo no terminal
         * 
         */
        void printGraph();
};

#endif