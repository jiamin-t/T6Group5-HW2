#pragma once

#include <vector>
#include "csv_parser.h"

struct Node {
    double x, y;
    Node* prev;
    Node* next;
    bool active; // false means removed
};

// circular double linked list
struct Ring {
    int ringID;
    std::vector<Node*> nodes;
    int size; // tracks active node count

    // build ring from parsed vertices
    Ring(int id, const std::vector<Vertex>& verts);

    // dtor
    ~Ring();

    // remove node from linked list (does NOT free memory, just unlinks)
    void remove_node(Node* node);

    // insert new_node
    void insert_node(Node* new_node, Node* prev_node, Node* next_node);
};