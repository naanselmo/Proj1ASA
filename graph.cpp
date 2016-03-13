#include <iostream>
#include "graph.hpp"

//
// Vertex (Template)
//

template<class T>
Vertex<T>::Vertex(T element)
{
    this->element = element;
    this->reset();
}

template<class T>
void Vertex<T>::addLink(Vertex* const vertex)
{
    this->neighbours.push_back(vertex);
}

template<class T>
std::list<Vertex<T> *> &Vertex<T>::getNeighbours()
{
    return this->neighbours;
}

template<class T>
void Vertex<T>::reset()
{
    this->visitedTime = INFINITE;
    this->lowTime = 0;
    this->childrenCount = 0;
    this->parent = NULL;
    this->fundamental = false;
}

template<class T>
Vertex<T>::~Vertex()
{
    delete this->element;
}

//
// Graph (Class)
//

Graph::Graph()
{
    this->vertexLength = 0;
}

void Graph::populate()
{
    unsigned int linksLength;
    std::cin >> this->vertexLength >> linksLength;
    this->vertex = new Vertex<Person *> *[vertexLength];
    for (unsigned int i = 0; i < this->vertexLength; i++) {
        Person *person = new Person(i + 1);
        this->vertex[i] = new Vertex<Person *>(person);
    }
    for (unsigned int i = 0; i < linksLength; i++) {
        unsigned int from, to;
        std::cin >> from >> to;
        //Ids start at 1
        this->vertex[--from]->addLink(this->vertex[--to]);
        this->vertex[to]->addLink(this->vertex[from]);
    }
}

void Graph::execute()
{
    std::vector<Vertex<Person *> *> fundamentals = findFundamentals();

    if (fundamentals.empty()) {
        std::cout << "0" << std::endl << "-1 -1" << std::endl;
        return;
    }

    unsigned int firstId = (*fundamentals.begin())->element->getId();
    unsigned int maxId = firstId, minId = firstId;
    for (std::vector<Vertex<Person *> *>::iterator it = fundamentals.begin() + 1; it != fundamentals.end(); it++) {
        Person *fundamental = (*it)->element;
        maxId = std::max(maxId, fundamental->getId());
        minId = std::min(minId, fundamental->getId());
    }
    std::cout << fundamentals.size() << std::endl;
    std::cout << minId << " " << maxId << std::endl;
}

void Graph::print()
{
    std::cout << "Persons: " << this->vertexLength << std::endl;
    for (unsigned int i = 0; i < this->vertexLength; i++) {
        Vertex<Person *> *vertex = this->vertex[i];
        std::cout << "Person " << vertex->element->getId() << "[" << vertex << "] is linked to: " << std::endl;
        std::list<Vertex<Person *> *> links = vertex->getNeighbours();
        for (std::list<Vertex<Person *> *>::iterator it = links.begin(); it != links.end(); it++) {
            Vertex<Person *> *neighbour = *it;
            std::cout << "\t-> Person " << neighbour->element->getId() << "[" << neighbour << "]" << std::endl;
        }
    }
}

Graph::~Graph()
{
    for (unsigned int i = 0; i < this->vertexLength; ++i) {
        delete this->vertex[i];
    }
    delete[] this->vertex;
}

std::vector<Vertex<Person *> *> Graph::findFundamentals()
{
    unsigned int time = 0;
    std::vector<Vertex<Person *> *> fundamentals;
    // Reset all information
    for (unsigned int i = 0; i < this->vertexLength; i++) {
        this->vertex[i]->reset();
    }
    // Visit all unvisited vertex and compute all visited and low times
    for (unsigned int i = 0; i < this->vertexLength; i++) {
        Vertex<Person *> *vertex = this->vertex[i];
        if (vertex->visitedTime == INFINITE) {
            this->visit(vertex, time, fundamentals);
        }
    }
    return fundamentals;
}

void Graph::visit(Vertex<Person *> *vertex, unsigned int &time, std::vector<Vertex<Person *> *> &fundamentals)
{
    // Based on:
    // http://www.eecs.wsu.edu/~holder/courses/CptS223/spr08/slides/graphapps.pdf#7
    // https://fenix.tecnico.ulisboa.pt/downloadFile/1970943312272240/aula5.pdf#19
    //

    // Pre-order traversal to compute visited time
    vertex->visitedTime = vertex->lowTime = time++;
    // Visit all unvisited children and compute low and visited times
    std::list<Vertex<Person *> *> neighbours = vertex->getNeighbours();
    for (std::list<Vertex<Person *> *>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
        Vertex<Person *> *neighbour = *it;
        // Tree edge so vertex.low = min(vertex.low, neighbour.low)
        if (neighbour->visitedTime == INFINITE) {
            vertex->childrenCount++;
            neighbour->parent = vertex;
            this->visit(neighbour, time, fundamentals);

            // If its not yet in the fundamental list, check if its fundamental
            if (!vertex->fundamental) {
                // If its a root and has more than one child, it is a fundamental person
                // or if its not root and its visited time is lesser or equal than any of its childs, it is a fundamental person
                if ((vertex->parent == NULL && vertex->childrenCount > 1)
                || (vertex->parent != NULL && vertex->visitedTime <= neighbour->lowTime)) {
                    fundamentals.push_back(vertex);
                    vertex->fundamental = true;
                }
            }

            // Post order traversal to compute low time
            vertex->lowTime = std::min(vertex->lowTime, neighbour->lowTime);
            // Back edge so vertex.low = min(vertex.low, neighbour.visited)
        } else if (vertex->parent != neighbour) {
            // Post order traversal to compute low time
            vertex->lowTime = std::min(vertex->lowTime, neighbour->visitedTime);
        }
    }
}
