#pragma once
#include <vector>
#include "ring.h"

// Simplifies the ring to target_vertices using the Ramer-Douglas-Peucker algorithm.
double simplify(std::vector<Ring*>& rings, int target_vertices);