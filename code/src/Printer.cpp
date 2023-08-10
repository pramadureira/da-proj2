#include "../headers/Printer.h"
#include <chrono>

Printer::Printer() = default;

Printer::Printer(const std::string& edgesPath) {
    std::ifstream edgesIn(edgesPath);
    Reader::readEdges(edgesIn, graph);
    if(edgesPath.find("real_graphs") != std::string::npos) {
        std::string nodesPath = edgesPath;
        size_t pos = nodesPath.find("edges");
        if (pos != std::string::npos) {
            nodesPath.replace(pos, 5, "nodes");
            std::ifstream nodesIn(nodesPath);
            Reader::readNodes(nodesIn, graph);
        }
    }
}

void Printer::printContent() {
    int m = 0;
    for(auto v: graph.getVertexSet()){
        if(v->getCoords() != nullptr)
            std::cout <<
                      "NODE: " << v->getId() <<
                      " || LATITUDE: " << v->getCoords()->latitude <<
                      " || LONGITUDE: " << v->getCoords()->longitude <<
                      std::endl;
        for(auto e: v->adj) {
            if (e == nullptr) {
                std::cout << "SOURCE: null || DEST: null" << std::endl;
                continue;
            }
            std::cout << "SOURCE: " << e->getOrig()->getId() << " || DEST: " << e->getDest()->getId() << " || DISTANCE: " << e->getDistance() << std::endl;
            m++;
        }

    }
    std::cout << "Edges count: " << m << " || VERTICES: " << graph.getVertexSet().size()<<std::endl;

}

void Printer::printCostAndPath() {
    std::vector<Vertex*> path;

    auto start = std::chrono::high_resolution_clock::now();

    double cost = graph.tspBT(path);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Path:";
    for (auto v : path) {
        std::cout << " " << v->getId();
    }
    std::cout << std::endl;
    std::cout << "Cost: " << cost << std::endl;

    std::cout << std::endl;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;
}

void Printer::printCostAndPathTAH(bool isShippingGraph) {
    std::vector<Vertex*> path;
    auto firstVertex = graph.findVertex(0);
    auto start = std::chrono::high_resolution_clock::now();
    double total_cost = 0.0;
    auto mst = graph.mstPrim();

    graph.addVectorPath();

    for(auto v : graph.getVertexSet()){
        v->setVisited(false);
    }

    graph.dfs(firstVertex,path);

    if(isShippingGraph) total_cost = graph.calculateShipping(path);
    else total_cost = graph.tspTriangular(path);

    auto end = std::chrono::high_resolution_clock::now();

    std:: cout << "Path: ";
    for (auto v : path){
        std::cout << v->getId() << " -> ";
    }
    std::cout << "0" << std::endl;
    std::cout << "Cost: " << total_cost << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;

}

void Printer::printCostAndPathHeuristic() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Vertex*> path;

    double total_cost = graph.tspHeuristic(path);

    if(total_cost == -1.0) {
        std::cout << "Our algorithm doesn't work with graphs not fully connected.\n";
        return;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std:: cout << "Path: ";
    for (auto v : path){
        std::cout << v->getId() << " -> ";
    }
    std::cout << "0" << std::endl;
    std::cout << "Cost: " << total_cost << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;
}