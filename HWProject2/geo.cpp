#include "geo.h"
#include <cmath>
#include <stdexcept>

namespace GEO {
    double triangle_area(Point a, Point b, Point c) {
        // shoelace formula, clockwise +ve
        return 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
    }

    double dist_to_line(Point p, Point a, Point b) {
        // Perpendicular distance from p to line through a and b
        double dx = b.x - a.x;
        double dy = b.y - a.y;
        double len = std::sqrt(dx * dx + dy * dy);
        if (len == 0) return 0;
        return std::abs((p.x - a.x) * dy - (p.y - a.y) * dx) / len;
    }

    double side(Point p, Point a, Point b) {
        // Cross product
        // Positive = left, negative = right
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    }

    Point line_intersect(Point p1, Point p2, Point p3, Point p4) {
        // Intersection of line p1->p2 and line p3->p4
        double a1 = p2.y - p1.y;
        double b1 = p1.x - p2.x;
        double c1 = a1 * p1.x + b1 * p1.y;

        double a2 = p4.y - p3.y;
        double b2 = p3.x - p4.x;
        double c2 = a2 * p3.x + b2 * p3.y;

        double det = a1 * b2 - a2 * b1;
        if (std::abs(det) < 1e-12)
            // Lines are parallel, return midpoint as fallback
            return { (p1.x + p2.x) * 0.5, (p1.y + p2.y) * 0.5 };

        return {
            (c1 * b2 - c2 * b1) / det,
            (a1 * c2 - a2 * c1) / det
        };
    }

    Point compute_E(Point A, Point B, Point C, Point D) {
        // Step 1 — compute E-line (ax + by + c = 0, parallel to AD)
        // From equation (1b) in the paper:
        // a = yD - yA
        // b = xA - xD
        // c = -yB*xA + (yA-yC)*xB + (yB-yD)*xC + yC*xD
        // (we don't need a,b,c explicitly — just need two points on E-line)

        // Two points on E-line: shift AD perpendicular by the required height
        // Easier: just find a point on E-line using the formula directly
        // The E-line passes through a point we can compute from the area condition

        double a = D.y - A.y;
        double b = A.x - D.x;
        double c = -B.y * A.x + (A.y - C.y) * B.x + (B.y - D.y) * C.x + C.y * D.x;

        // Get two points on the E-line (ax + by + c = 0)
        Point E1, E2;
        if (std::abs(b) > 1e-12) {
            E1 = { 0.0,          -c / b };
            E2 = { 1.0,          (-c - a) / b };
        }
        else {
            E1 = { -c / a,       0.0 };
            E2 = { (-c - b) / a, 1.0 };
        }

        // Step 2 — find which side B and C are on relative to AD
        double sideB = side(B, A, D);
        double sideC = side(C, A, D);
        double sideE_line = side(E1, A, D);

        // Step 3 — placement rules from the paper (Figure 4)
        // Config (a): B and C on opposite sides of AD
        // Config (b,c): B and C on same side of AD
        if ((sideB > 0) != (sideC > 0)) {
            // Opposite sides — config (a)
            // E is at intersection of E-line and AB if E-line is on same side as B
            if ((sideB > 0) == (sideE_line > 0))
                return line_intersect(E1, E2, A, B);
            else
                return line_intersect(E1, E2, C, D);
        }
        else {
            // Same side — config (b) or (c)
            // E is at intersection of E-line and AB if B is further from AD than C
            double dB = dist_to_line(B, A, D);
            double dC = dist_to_line(C, A, D);
            if (dB > dC)
                return line_intersect(E1, E2, A, B);
            else
                return line_intersect(E1, E2, C, D);
        }
    }

    double areal_displacement(Point A, Point B, Point C, Point D, Point E) {
        // Total area between A->B->C->D and A->E->D
        // = area of triangle ABE + area of triangle BCE + area of triangle CDE
        // (unsigned, so take abs of each)
        double t1 = std::abs(triangle_area(A, B, E));
        double t2 = std::abs(triangle_area(B, C, E));
        double t3 = std::abs(triangle_area(C, D, E));
        return t1 + t2 + t3;
    }

    bool segments_intersect(Point p1, Point p2, Point p3, Point p4) {
        // Strict interior crossing — shared endpoints don't count
        double d1 = side(p3, p1, p2), d2 = side(p4, p1, p2);
        double d3 = side(p1, p3, p4), d4 = side(p2, p3, p4);
        return ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
            ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0));
    }
} // namespace GEO