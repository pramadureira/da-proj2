#ifndef FEUP_DA_PROJ2_GRAPH_H
#define FEUP_DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

class Graph {
public:

    /**
     * Finds a vertex with a given id in the graph. \n
     * Complexity: O(1)
     * @param id
     * @return A pointer to the found vertex (nullptr if not found)
     */
    Vertex* findVertex(const int &id);

     /**
     * Adds a vertex with a given id to a graph. \n
     * Complexity: O(V) V-> number of vertices
     * @param id The id of the new vertex
     * @return A pointer to the newly added vertex
     */
    Vertex* addVertex(const int &id);

     /**
     * Adds a bidirectional edge between two vertices in the graph with a specified weight. \n
     * Complexity: O(V) V-> number of vertices
     * @param v1 Pointer to the first vertex
     * @param v2 Pointer to the second vertex
     * @param w The weight of the edge
     * @return True if the edge was added successfully, false otherwise
     */
    bool addBidirectionalEdge(Vertex* v1, Vertex* v2, double w);

    /**
     * Calculate the distance between two vertices. \n
     * Complexity: O(1)
     * @param source Pointer to the source vertex
     * @param dest Pointer to the destination vertex
     * @return The distance between the two vertices if there is an edge between them,or -1.0 if not
     */
    double dist(Vertex* source, Vertex* dest);

    /**
     * Calculates the Haversine distance between two vertex. \n
     * Complexity: O(1)
     * @param v1 Pointer to the first vertex
     * @param v2 Pointer to the second vertex
     * @return The Haversine distance between the two vertex
     */
    double Haversine(Vertex* v1, Vertex* v2);

    /**
     * Calculates the distance between the two vertices using the existing distance stored in the edge. If
     * there is no edge, it uses the Haversine formula to calculate the distance. \n
     * Complexity: O(1)
     * @param v1 Pointer to the first vertex
     * @param v2 Pointer to the second vertex
     * @return The distance between the two vertices
     */
    double calculateDistance(Vertex *v1,Vertex *v2);


    /**
     * Adds the IDs of the destination vertices, for each vertex, to the destination vertex vector. \n
     * Complexity: O(V) V-> number of vertices
     */
    void addVectorPath();

    /**
     * Performs a depth-first search (DFS) starting from a given vertex. \n
     * Complexity: O(V*n) V-> number of vertices; n-> number of vertices in the vector
     * @param v Pointer to the starting vertex for the DFS
     * @param visited Reference to a vector to store the visited vertices
     */
    void dfs(Vertex* v, std::vector<Vertex*>& visited);

    /**
     * Creates the Minimum Spanning Tree (MST) of the graph using Prim's algorithm. \n
     * Complexity: O((V+E)*log V) V-> number of vertices; E-> number of edges
     * @return Vector containing the vertices of the Minimum Spanning Tree (MST)
     */
    std::vector<Vertex *> mstPrim();

    /**
     * This function performs the backtracking algorithm to find the shortest path that visits all the vertices in
     * the graph. \n
     * Complexity: O(V!) V-> number of vertices
     * @param path Reference to a vector of vertices that represents the shortest path found so far
     * @param currPath Vector of vertices that represents the current path being explored
     * @param currCost Double that represents the current cost of the path being explored
     * @param bestCost Reference to a double that represents the cost of the best path found so far
     */
    void backtracking(std::vector<Vertex*> &path, std::vector<Vertex*> currPath, double currCost, double &bestCost, int
    index);

    /**
     * Calculates the shipping cost. \n
     * Complexity: O(V) V-> number of vertices
     * @param path A vector of vertices representing the dfs path of the shipping
     * @return The shipping cost for the given path
     */
    double calculateShipping(std::vector<Vertex*> &path);

    /**
    * Finds the shortest path that visits all vertices in the graph using the nearest neighbour algorithm. \n
    * Complexity: O(V+E) V-> number of vertices; E-> number of edges
    * @param path Reference to a vector of vertices that represents the shortest path found
    * @return Double that represents the cost of the best path
    */
    double nearestNeighbour(std::vector<Vertex *> &path);

    /**
     * Finds the shortest path that visits all vertices in the graph using the backtracking algorithm. \n
     * Complexity: O(V!) V-> number of vertices
     * @param path Reference to a vector of vertices that represents the shortest path found so far
     * @return Double that represents the cost of the best path
     */
    double tspBT(std::vector<Vertex*> &path);

    /**
    * Finds the shortest path that visits all vertices in the graph using the Triangular Approximation Heuristic
    * algorithm. \n
    * Complexity: O(V) V-> number of vertices
    * @param path Reference to a vector of vertices that represents the shortest path found so far
    * @return Double that represents the cost of the best path
    */
    double tspTriangular(std::vector<Vertex*> &path);

    /**
    * Finds the shortest path that visits all vertices in the graph using our own heuristic. \n
    * Complexity: Complexity: O(V⁴) V-> number of vertices
    * @param path Reference to a vector of vertices that represents the shortest path found
    * @return Double that represents the cost of the best path
    */
    double tspHeuristic(std::vector<Vertex *> &path);

    /**
    * Returns the number of vertices in the graph.
    * Complexity: O(1)
    * @return The number of vertices in the graph.
    */
    int getNumVertex() const;

    /**
    * Returns a vector containing all the vertices in the graph.
    * Complexity: O(1)
    * @return A vector containing all the vertices in the graph.
    */
    std::vector<Vertex *> getVertexSet() const;

protected:
    std::vector<Vertex*> vertexSet;
};

#endif //FEUP_DA_PROJ2_GRAPH_H
