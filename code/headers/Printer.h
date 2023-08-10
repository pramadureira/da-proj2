#ifndef FEUP_DA_PROJ2_PRINTER_H
#define FEUP_DA_PROJ2_PRINTER_H

#include "Graph.h"
#include "Reader.h"

#include <fstream>

class Printer {
public:
    Printer();
    Printer(const std::string& edgesPath);

    /**
     * This function prints the content of the current graph.
     * Complexity: O(V+E) V-> number of vertices; E-> number of edges
     */
    void printContent();

    /**
     * Prints the cost and path of a graph using a brute force approach of the TSP, as well as it's execution time. \n
     * Complexity: O(V!) V-> number of vertices
     */
    void printCostAndPath();

    /**
     * Prints the cost and path of a graph using the triangular approach of the TSP, as well as it's execution time. \n
     * Complexity: O((V+E)*log V) V-> number of vertices; E-> number of edges
     * @param isShippingGraph A flag variable indicating whether the graph represents the shipping graph.
     */
    void printCostAndPathTAH(bool isShippingGraph);

     /**
      * Prints the cost and path of our heuristic algorithm, as well as it's execution time. \n
      * Complexity: Complexity: O(V⁴) V-> number of vertices
      */
    void printCostAndPathHeuristic();
private:
    Graph graph;
};

#endif //FEUP_DA_PROJ2_PRINTER_H
