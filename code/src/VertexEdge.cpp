#include "../headers/VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id): id(id) {}
Vertex::~Vertex() {
    delete coords;
}

void Vertex::add(std::vector<Edge*> &vec, Edge* edge) {
    int vId = edge->getDest()->getId();
    if (vId >= vec.size()) vec.resize(vId + 1, nullptr);

    if (vec[vId] == nullptr) vec[vId] = edge;
}

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    add(adj, newEdge);
    return newEdge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}


bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

Coords* Vertex::getCoords() const {
    return coords;
}

std::vector<int>& Vertex::getDestVertexVector() {
    return dest_vertex;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::setCoords(double longitude, double latitude) {
    Coords* newCoords = new Coords{longitude, latitude};
    coords = newCoords;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double dist): orig(orig), dest(dest), dist(dist) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->dist;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}
