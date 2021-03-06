/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <set>
#include <limits>
#include <cmath>
#include <iostream>
#include "MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

    std::vector< std::vector<double> > dist;
    std::vector< std::vector<int> > path;
public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    Vertex<T> *start = findVertex(orig);
    if (start == NULL) return;
    for (Vertex<T> *vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    start->dist = 0;
    std::queue< Vertex<T>* > vertices;
    vertices.push(findVertex(orig));
    while (!vertices.empty()) {
        Vertex<T> *v = vertices.front();
        vertices.pop();
        for (Edge<T> edge : v->adj) {
            if (edge.dest->dist == INF) {
                vertices.push(edge.dest);
                edge.dest->dist = v->dist + 1;
                edge.dest->path = v;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    Vertex<T> *start = findVertex(origin);
    if (start == NULL) return;
    for (Vertex<T> *vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    start->dist = 0;
    MutablePriorityQueue< Vertex<T> > queue;
    queue.insert(start);
    while (!queue.empty()) {
        Vertex<T> *v = queue.extractMin();
        for (Edge<T> edge : v->adj) {
            if (edge.dest->dist > v->dist + edge.weight) {
                double oldDist = edge.dest->dist;
                edge.dest->dist = v->dist + edge.weight;
                edge.dest->path = v;
                if (oldDist == INF) queue.insert(edge.dest);
                else queue.decreaseKey(edge.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    Vertex<T> *start = findVertex(orig);
    if (start == NULL) return;
    for (Vertex<T> *vertex : vertexSet) {
        vertex->dist = INT_MAX;
        vertex->path = NULL;
    }
    start->dist = 0;
    for (int i = 1; i < vertexSet.size(); i++) {
        for (Vertex<T> *vertex : vertexSet) {
            for (Edge<T> edge : vertex->adj) {
                if (edge.dest->dist > vertex->dist + edge.weight) {
                    edge.dest->dist = vertex->dist + edge.weight;
                    edge.dest->path = vertex;
                }
            }
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    if (findVertex(origin) == NULL || findVertex(dest) == NULL) return res;
    Vertex<T> *v = findVertex(dest);
    while (v != NULL) {
        res.insert(res.begin(), v->info);
        v = v->path;
    }
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    int n = vertexSet.size();
    dist = std::vector< std::vector<double> >(n, std::vector<double>(n, INF));
    path = std::vector< std::vector<int> >(n, std::vector<int>(n, -1));
    for (Vertex<T> *vertex : vertexSet) {
        dist[vertex->info - 1][vertex->info - 1] = 0;
        path[vertex->info - 1][vertex->info - 1] = vertex->info - 1;
        for (Edge<T> edge : vertex->adj) {
            dist[vertex->info - 1][edge.dest->info - 1] = edge.weight;
            path[vertex->info - 1][edge.dest->info - 1] = edge.dest->info - 1;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    if (dist[orig - 1][dest - 1] == INF) return res; //there is no path from orig to dest
    T next = orig - 1;
    res.push_back(next + 1);
    while (next != (dest - 1)  && next != -1) {
        next = path[next][dest - 1];
        res.push_back(next + 1);
    }
    return res;
}


#endif /* GRAPH_H_ */
