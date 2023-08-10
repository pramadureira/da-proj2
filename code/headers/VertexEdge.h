#ifndef VERTEXEDGE_H
#define VERTEXEDGE_H

#include <vector>
#include <climits>

#include "MutablePriorityQueue.h"

class Edge;

struct Coords {
    double longitude;
    double latitude;
};

class Vertex {
public:
    Vertex(int id);
    ~Vertex();

    int getId() const;
    bool isVisited() const;
    double getDist() const;
    Edge *getPath() const;
    Coords* getCoords() const;
    std::vector<int>& getDestVertexVector();

    void add(std::vector<Edge *> &vec, Edge *edge);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    void setCoords(double longitude, double latitude);

    /*
     * Auxiliary function to add an outgoing edge to a vertex (this),
     * with a given destination vertex (d) and edge weight (w).
     */
    Edge * addEdge(Vertex *dest, double w);
    bool operator<(Vertex & vertex) const;

    std::vector<Edge *> adj;        // outgoing edges

protected:
    friend class MutablePriorityQueue<Vertex>;

    int id;                         // identifier
    std::vector<int> dest_vertex;   // incoming edges

    // auxiliary fields
    bool visited = false;           // used by DFS, BFS, Prim ...
    double dist = 0;                // used to know the distance of the vertex
    Edge *path = nullptr;           // created by MST
    Coords *coords = nullptr;       // used by Haversine

    int queueIndex = 0; 		    // required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double dist);
    Vertex * getDest() const;
    double getDistance() const;
    Vertex * getOrig() const;
protected:
    Vertex * dest;
    double dist = 0.0;

    // auxiliary fields
    Vertex *orig;
};

#endif //VERTEXEDGE_H
