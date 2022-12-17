#include "graph.hpp"


const int _inf = 9999999;

int Graph::bfs(vertex origin, int destiny) {
    it = vertices.find(origin.idConecta);
    it->second.parent = -2;

    //cout << "MANO" << endl;
    vertex current = origin;

    queue<int> _queue;
    _queue.emplace(current.idConecta);
    int flow_path[numberOfVertices];
    flow_path[origin.idConecta] = _inf;

    while (!_queue.empty()) {
        int v = _queue.front();
        _queue.pop();
        /*
        if (v == destiny)
            return flow_path[v];
        */
        current = vertices.find(v)->second;

        map<int, vertex>::iterator aux_it;
        //cout << "comeca o for" << endl;
        for (itl = current.edges.begin(); itl != current.edges.end(); ++itl) {
            aux_it = vertices.find(itl->idPoPsConectado);
            //cout << "0.0" << endl;
            if (aux_it->second.parent == -1 && itl->capacity == itl->velocidade) {
                aux_it->second.parent = current.idConecta;
                //int new_flow = itl->velocidade;
                //cout << ",.,.,.,." << endl;
                
                cout << "Ta no vértice: " << current.idConecta << ", vai pro: " << aux_it->second.idConecta << ", a velocidade na aresta atual: " << itl->velocidade << endl;
                flow_path[aux_it->second.idConecta] = min(flow_path[current.idConecta], itl->velocidade);
                //cout << "ioioio" << endl;

                if (aux_it->second.idConecta == current.idConecta) {
                   return flow_path[aux_it->second.idConecta];
                }

                _queue.push(aux_it->second.idConecta);
            }
        }
    }
    return 0;
}

void Graph::edmond_karp (int origin, int destiny) {
        int max_flow = 0;

        for(it = vertices.begin(); it != vertices.end(); ++it) {
            it->second.parent = -1;
            for (itl = vertices[it->first].edges.begin(); itl != vertices[it->first].edges.end(); ++itl)
                itl->capacity = itl->velocidade;
        }

        //cout << "desisto!!!!!!!" << endl;
        //vector<int> parents;
        vertex v_origin = vertices.find(origin)->second;

        //cout << "bfkvbka" << endl;
        vector<int> pred;
        //edge pred[numberOfVertices];
        for (int i = 0; i < numberOfVertices; i++) {
            pred.push_back(-1);
        }
        int new_flow;
        //cout << "o que ta acontecenu?" << endl;
        while (1) {
            //pred[] = bfs(v_origin, destiny);
            new_flow = bfs(v_origin, destiny);
            //if (new_flow == 0)
            //    break;

            //cout << "saiu da busca" << endl;
            queue<int> _queue;
            _queue.push(destiny);

            //cout << "hmmmm o.O" << endl;
            while (!_queue.empty()) {
                int current = _queue.front();
                _queue.pop();
                it = vertices.find(current);
                for (itl = vertices[current].edges.begin(); itl != vertices[current].edges.end(); ++itl) {
                    if (pred[itl->idPoPsConectado] == -1 && itl->idPoPsConectado != origin && itl->capacity >= itl->velocidade) {
                        pred[itl->idPoPsConectado] = itl->idPoPsConectado;
                        _queue.push(itl->idPoPsConectado);
                    }
                }
            }
            if (pred[destiny] != -1) {
                int df = _inf;

                for (itl = it->second.edges.begin(); itl != it->second.edges.end(); ++itl) {
                    df = min(df, itl->velocidade);
                    itl->capacity = 0;
                }
                //cout << "df: " << df << endl;
                max_flow += df;
            }
            if (new_flow == 0)
                break;

        }

        cout << "Fluxo máximo entre " << origin << " e " << destiny << ": ";
        if (max_flow != 0)
            cout  << max_flow << "Mbps";
        else
            cout << -1;
        cout << endl;
}