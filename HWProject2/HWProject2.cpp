// HWProject2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "csv_parser.h"
#include "ring.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.csv> <target_vertices>\n";
        return 1;
    }

    std::string filename = argv[1];
    int target = std::stoi(argv[2]);

    auto parsed = CSV::parse_csv(filename);

    // build ring
    std::vector<Ring*> rings;
    for (auto& [rid, verts] : parsed) {
        rings.push_back(new Ring(rid, verts));
    }

    // for testing
    std::cout << "ring_id,vertex_id,x,y\n";
    for (auto* ring : rings) {
        Node* start = ring->nodes[0];
        Node* cur = start;
        int vid = 0;
        do {
            std::cout << ring->ringID << "," << vid++ << ","
                      << cur->x << "," << cur->y << "\n";
            cur = cur->next;
        } while (cur != start);
    }

    // cleanup
    for (auto* r : rings) delete r;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
