#include "ring.h"

Ring::Ring(int id, const std::vector<Vertex>& verts) : ringID(id), size(verts.size()) {
    // create nodes
    for (const Vertex& v : verts){
        Node* n = new Node{v.x, v.y, nullptr, nullptr, true};
        nodes.push_back(n);
    }

    // make it circular
    int n = nodes.size();
    for (int i = 0; i < n; ++i) {
        nodes[i]->prev = nodes[(i - 1 + n) % n];
        nodes[i]->next = nodes[(i + 1) % n];
    }
}

Ring::~Ring() {
    for (Node* n : nodes)
        delete n;
}

void Ring::remove_node(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->active = false;
    
    --size;
}

void Ring::insert_node(Node* new_node, Node* prev_node, Node* next_node) {
    new_node->prev = prev_node;
    new_node->next = next_node;
    prev_node->next = new_node;
    next_node->prev = new_node;
    new_node->active = true;

    nodes.push_back(new_node);
    size++;
}