#ifndef FEUP_DA_PROJ2_READER_H
#define FEUP_DA_PROJ2_READER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include "Graph.h"

class Reader {
public:
    /**
     * The method reads an edges file and stores the data in both the nodes and edges of the graph.
     * @param in edges file ifstream
     * @param graph
     */
    static void readEdges(std::ifstream &in, Graph& graph);

    /**
     * The method reads a nodes file and stores the coordinates data in the nodes of the graph.
     * @param in nodes file ifstream
     * @param graph
     */
    static void readNodes(std::ifstream &in, Graph& graph);

};

#endif //FEUP_DA_PROJ2_READER_H
