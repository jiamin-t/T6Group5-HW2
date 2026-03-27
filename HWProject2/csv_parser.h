#pragma once

#include <string>
#include <map>
#include <vector>

struct Vertex{
    int ringID, vertexID;
    double x, y;
};

namespace CSV {
    std::map<int, std::vector<Vertex>> parse_csv(const std::string& filename);
}