#pragma once

#include "ring.h"

struct Point {
    double x, y;
};

namespace GEO {
    // compute signed area of triangle
    // +ve -> counterclockwise, -ve -> clockwise
    double triangle_area(Point a, Point b, Point c);

    // perpendicular distance from point p to line through a and b
    double dist_to_line(Point p, Point a, Point b);

    // Which side of directed line a->b is point p on
    // +ve -> left, -ve -> right
    double side(Point p, Point a, Point b);

    // intersection of line through p1,p2 and line through p3,p4
    Point line_intersect(Point p1, Point p2, Point p3, Point p4);

    // given 4 consecutive vertices A,B,C,D, returns the new Steiner point E
    Point compute_E(Point A, Point B, Point C, Point D);

    // compute areal displacement of replacing A->B->C->D with A->E->D
    double areal_displacement(Point A, Point B, Point C, Point D, Point E);
}