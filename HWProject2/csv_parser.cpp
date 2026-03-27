#include "csv_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace CSV {
    std::map<int, std::vector<Vertex>> parse_csv(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + filename);

        std::map<int, std::vector<Vertex>> rings;
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;
            Vertex v;
            
            std::getline(ss, token, ','); v.ringID = std::stoi(token);
            std::getline(ss, token, ','); v.vertexID = std::stoi(token);
            std::getline(ss, token, ','); v.x = std::stod(token);
            std::getline(ss, token, ','); v.y = std::stod(token);

            rings[v.ringID].push_back(v);
        }

        return rings;
    }
}