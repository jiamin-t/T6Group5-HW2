// HWProject2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "csv_parser.h"
#include "ring.h"
#include "simplifier.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.csv> <target_vertices>\n";
        return 1;
    }

    std::string filename = argv[1];
    int target = std::stoi(argv[2]);

    // Parse + build rings
    auto parsed = CSV::parse_csv(filename);
    std::vector<Ring*> rings;
    for (auto& [rid, verts] : parsed)
        rings.push_back(new Ring(rid, verts));

    // Record input area before any changes
    double input_area = 0.0;
    for (Ring* r : rings) input_area += r->signed_area();

    int total_in = 0;
    for (Ring* r : rings) total_in += r->size;
    //std::cerr << "Input vertices: " << total_in << "  Target: " << target << "\n";

	//run simplification
    double areal_disp = simplify(rings, target);

    int total_out = 0;
    for (Ring* r : rings) total_out += r->size;
    //std::cerr << "Output vertices: " << total_out << "\n";

	//print output CSV
    std::cout << "ring_id,vertex_id,x,y\n";
    for (Ring* ring : rings) {
        Node* start = ring->active_head();
        if (!start) continue;
        Node* cur = start;
        int vid = 0;
        do {
            std::cout << ring->ringID << "," << vid++ << ","
                << cur->x << "," << cur->y << "\n";
            cur = cur->next;
        } while (cur != start);
    }

	//print area stats
    double output_area = 0.0;
    for (Ring* r : rings) output_area += r->signed_area();

    std::cout << std::scientific << std::setprecision(6);
    std::cout << "Total signed area in input: " << input_area << "\n";
    std::cout << "Total signed area in output: " << output_area << "\n";
    std::cout << "Total areal displacement: " << areal_disp << "\n";

    for (Ring* r : rings) delete r;
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
