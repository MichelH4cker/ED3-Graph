#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include "main.hpp"

typedef struct edge {
    int velocidade;
    int idPoPsConectado;
} edge;

typedef struct vertex {
    int idConecta;
    string nomePoPs;
    string nomePais;
    string siglaPais;

    forward_list<edge> edges;
} vertex;

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool my_compare (const edge x,const edge y);

/**
 * @brief 
 * 
 */
class Graph {
    public: 
        map<int, vertex> vertices;
        map<int, vertex>::iterator it;        
        forward_list<edge>::iterator itl;

        int numberOfVertices;

        /**
         * @brief Create a Graph object
         * 
         * @param db_file 
         */
        void createGraph(char *db_file);

        /**
         * @brief 
         * 
         */
        void sortList();

        /**
         * @brief 
         * 
         * @param vertex 
         */
        void printVertex(vertex vertex);
        
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
         * @brief 
         * 
         * @param reg_db 
         * @return vertex 
         */
        vertex updateVertexToIdPoPs(register_db reg_db);
        
        /**
         * @brief 
         * 
         * @param reg_db 
         * @return edge 
         */
        edge updateEdgeToIdPoPs(register_db reg_db);
      
        /**
         * @brief 
         * 
         */
        void printGraph();
};

#endif