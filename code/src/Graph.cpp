#include <iostream>
#include "../headers/Graph.h"
#include <algorithm>
#include <valarray>

Vertex* Graph::findVertex(const int &id) {
    if(id < vertexSet.size()) return vertexSet[id];
    else return nullptr;
}

Vertex* Graph::addVertex(const int &id) {
    if (id >= vertexSet.size()) vertexSet.resize(id + 1, nullptr);

    if (vertexSet[id] == nullptr) vertexSet[id] = new Vertex(id);
    return vertexSet[id];
}

bool Graph::addBidirectionalEdge(Vertex* v1, Vertex* v2, double w) {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    v2->addEdge(v1, w);
    return true;
}

double Graph::dist(Vertex *source, Vertex *dest) {
    //auto adj = source->getAdj();
    if(dest->getId() >= source->adj.size()) return -1.0;
    Edge* edge = source->adj[dest->getId()];
    if (edge == nullptr) return -1.0;
    double dist = edge->getDistance();
    return dist;
}

double Graph::Haversine(Vertex* v1, Vertex* v2) {
    double v1_lat_rad = (v1->getCoords()->latitude * M_PI) / 180.0;
    double v2_lat_rad = (v2->getCoords()->latitude * M_PI) / 180.0;
    double v1_lon_rad = (v1->getCoords()->longitude * M_PI) / 180.0;
    double v2_lon_rad = (v2->getCoords()->longitude * M_PI) / 180.0;

    double delta_lat = v2_lat_rad  - v1_lat_rad;
    double delta_lon = v2_lon_rad - v1_lon_rad;
    double aux = std::sin(delta_lat / 2.0) * std::sin(delta_lat / 2.0) + std::cos(v1_lat_rad) * std::cos(v2_lat_rad) * std::sin(delta_lon / 2.0) * std::sin(delta_lon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(aux), std::sqrt(1.0 - aux));
    double earthradius = 6371000.0;
    return earthradius * c;
}

double Graph::calculateDistance(Vertex *v1,Vertex *v2){
    double distance = Graph::dist(v1,v2);
    if (distance == -1.0){
        distance = Graph::Haversine(v1,v2);
    }
    return distance;
}

void Graph::addVectorPath() {
    for (auto v : vertexSet) {
        if (v->getPath() != nullptr) {
            auto initial_vertex = v->getPath()->getOrig();
            std::vector<int>& initVertexVector = initial_vertex->getDestVertexVector();
            initVertexVector.push_back(v->getPath()->getDest()->getId());
        }
    }
}

void Graph::dfs(Vertex* v, std::vector<Vertex*>& visited) {
    visited.push_back(v);
    v->setVisited(true);

    for (auto w : v->getDestVertexVector()) {
        auto u = vertexSet[w];
        if(!u->isVisited()) {
            dfs(u, visited);
        }
    }
}

std::vector<Vertex *> Graph::mstPrim() {
    MutablePriorityQueue<Vertex> q;
    std::vector<Vertex *> res;
    for (auto v: vertexSet) {
        v->setVisited(false);
        if (v == *vertexSet.begin()) {
            v->setDist(0);
            v->setPath(nullptr);
        } else {
            v->setDist(INT_MAX);
        }
        q.insert(v);
    }
    while (!q.empty()) {
        auto u = q.extractMin();
        res.push_back(u);
        u->setVisited(true);
        for (auto w: u->adj) {
            if (w == nullptr) continue;
            auto v = w->getDest();
            if (!v->isVisited() && w->getDistance() < v->getDist()) {
                v->setPath(w);
                v->setDist(w->getDistance());
                q.decreaseKey(v);
            }
        }
    }
    return res;
}

void Graph::backtracking(std::vector<Vertex*> &path, std::vector<Vertex*> currPath, double currCost, double &bestCost, int index) {
    if (index == vertexSet.size()) {
        double dist = Graph::dist(currPath[index-1], vertexSet[0]);
        if (dist != -1) {
            currCost += dist;
            if (currCost < bestCost) {
                bestCost = currCost;
                path = currPath;
            }
        }

        return;
    }

    for (int i = 1; i < vertexSet.size(); i++) {
        double dist = Graph::dist(currPath[index - 1], vertexSet[i]);
        Vertex* vertex = vertexSet[i];
        if (dist != -1 && currCost + dist < bestCost && std::find(currPath.begin(), currPath.end(), vertex) == currPath
        .end()) {
            currPath[index] = vertex;
            backtracking(path, currPath, currCost + dist, bestCost, index+1);
        }
    }
}


double Graph::tspBT(std::vector<Vertex*> &path) {
    std::vector<Vertex*> currPath(vertexSet.size(), nullptr);
    double bestCost = LONG_MAX;
    currPath[0] = vertexSet[0];
    backtracking(path, currPath, 0, bestCost, 1);

    return bestCost;
}

double Graph::calculateShipping(std::vector<Vertex*> &path){
    double cost = 0.0;
    Vertex* vertex_0 = vertexSet[0];
    int last_index = path.size();
    double sum = 0.0;

    for(auto v : path){
        sum += v->getDist();
    }
    sum = sum / path.size(); // Average of the all edges (distance)


    for(int i = 0; i < path.size() -1; i++){
        double dist = Graph::dist(path[i],path[i+1]);
        if(dist == -1){
            dist = sum;
        }
        cost += dist;
    }

    if(Graph::dist(path[last_index-1],vertex_0) == -1){
        cost += sum;
    }
    else cost += Graph::dist(path[last_index-1],vertex_0);

    return cost;
}

double Graph::tspTriangular(std::vector<Vertex*> &path) {
    double cost = 0.0;
    Vertex* vertex_0 = vertexSet[0];
    int last_index = path.size();
    for(int i = 0; i < path.size()-1;i++){
        cost += Graph::calculateDistance(path[i],path[i+1]);
    }
    cost += Graph::calculateDistance(path[last_index-1],vertex_0);
    return cost;
}

double Graph::nearestNeighbour(std::vector<Vertex*> &path) {
    double cost = 0;
    for(Vertex* v: vertexSet) {
        v->setVisited(false);
    }

    Vertex* currentVertex = vertexSet[0];
    path.clear();
    path.push_back(currentVertex);
    currentVertex->setVisited(true);

    while (path.size() < getNumVertex()) {
        double minDistance = LONG_MAX;
        Vertex* nextVertex = nullptr;

        for (Edge* edge : currentVertex->adj) {
            if (edge == nullptr) continue;
            Vertex* neighbor = edge->getDest();
            if (!neighbor->isVisited() && edge->getDistance() < minDistance) {
                minDistance = edge->getDistance();
                nextVertex = neighbor;
            }
        }

        if (nextVertex != nullptr) {
            cost += minDistance;
            nextVertex->setVisited(true);
            path.push_back(nextVertex);
            currentVertex = nextVertex;
        } else {
            return -1.0;
        }
    }

    cost += calculateDistance(path[path.size() - 1], path[0]);

    return cost;
}


double Graph::tspHeuristic(std::vector<Vertex*> &path) {
    double cost = nearestNeighbour(path);

    if(cost == -1.0) return -1.0;

    bool improved = true;
    while (improved) {
        improved = false;

        for (int i = 0; i < path.size() - 2; i++) {
            for (int j = i + 2; j < path.size() - 1; j++) {
                double oldCost = calculateDistance(path[i], path[i + 1]) + calculateDistance(path[j], path[j + 1]);
                double newCost = calculateDistance(path[i], path[j]) + calculateDistance(path[i + 1], path[j + 1]);

                if (newCost < oldCost) {
                    std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                    cost -= oldCost - newCost;
                    improved = true;
                }
            }
        }
    }

    return cost;
}


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}
