#include <queue>
#include "geo.h"
#include "simplifier.h"

// One entry in the priority queue: collapsing A->B->C->D into A->E->D.
// B and C get removed; E is inserted between A and D.
struct Collapse {
    double displacement;  // areal displacement — used to rank candidates
    Point  E;             // precomputed replacement point
    Node* A;
    Node* B;             // will be removed
    Node* C;             // will be removed
    Node* D;
    Ring* ring;
};

// Min-heap: smallest displacement = best candidate
struct CollapseCmp {
    bool operator()(const Collapse& a, const Collapse& b) const {
        return a.displacement > b.displacement;
    }
};

using PQ = std::priority_queue<Collapse, std::vector<Collapse>, CollapseCmp>;

// Helper to convert Node to Point for geo calculations
static inline Point to_point(const Node* n) { return { n->x, n->y }; }

static int total_vertices(const std::vector<Ring*>& rings) {
    int sum = 0;
    for (const Ring* r : rings) sum += r->size;
    return sum;
}

// Returns false and leaves `out` untouched if any node is inactive.
static bool make_candidate(Node* A, Node* B, Node* C, Node* D,
    Ring* ring, Collapse& out) {
    if (!A->active || !B->active || !C->active || !D->active)
        return false;

    Point pA = to_point(A), pB = to_point(B),
        pC = to_point(C), pD = to_point(D);
    Point E = GEO::compute_E(pA, pB, pC, pD);

    out = { GEO::areal_displacement(pA, pB, pC, pD, E), E, A, B, C, D, ring };
    return true;
}

//seed, push all valid windows from the ring into the priority queue
static void seed_ring(PQ& pq, Ring* ring) {
    if (ring->size < 4) return;

    Node* A = ring->active_head();
    Node* B = A->next, * C = B->next, * D = C->next;
    Node* start = A;
    do {
        Collapse cand;
        if (make_candidate(A, B, C, D, ring, cand))
            pq.push(cand);
        A = B; B = C; C = D; D = D->next;
    } while (A != start);
}

//topo check: ensure new edges A-E and E-D don't intersect existing edges (except those incident to A, B, C, D).
// The two new segments A-E and E-D must not cross any existing ring edge.
// We skip edges incident to A, B, C, D (they share endpoints and will be gone).
static bool topology_ok(const std::vector<Ring*>& rings,
    Node* A, Node* B, Node* C, Node* D, Point E) {
    Point pA = to_point(A), pD = to_point(D);

    for (const Ring* ring : rings) {
        Node* u = ring->active_head();
        if (!u) continue;
        do {
            Node* v = u->next;
            // Skip edges that touch A, B, C, or D
            if (u == A || u == B || u == C || u == D || v == A || v == B || v == C || v == D) {
                u = u->next; continue;
            }
            Point pu = to_point(u), pv = to_point(v);
            if (GEO::segments_intersect(pA, E, pu, pv)) return false;
            if (GEO::segments_intersect(E, pD, pu, pv)) return false;
            u = u->next;
        } while (u != ring->active_head());
    }
    return true;
}

// Remove B and C, insert new node E between A and D.
static Node* apply_collapse(Ring* ring, const Collapse& cand) {
    ring->remove_node(cand.B);
    ring->remove_node(cand.C);
    Node* E_node = new Node{ cand.E.x, cand.E.y, nullptr, nullptr, false };
    ring->insert_node(E_node, cand.A, cand.D);
    return E_node;
}

// E can appear as A, B, C, or D in up to 4 windows.
// Walk back 3 steps from E to find the earliest affected window start.
static void push_around(PQ& pq, Node* E, Ring* ring) {
    if (ring->size < 4) return;
    Node* starts[4] = {
        E->prev->prev->prev,
        E->prev->prev,
        E->prev,
        E
    };
    for (Node* A : starts) {
        Node* B = A->next, * C = B->next, * D = C->next;
        Collapse cand;
        if (make_candidate(A, B, C, D, ring, cand))
            pq.push(cand);
    }
}

//main loop
double simplify(std::vector<Ring*>& rings, int target_vertices) {
    if (total_vertices(rings) <= target_vertices) return 0.0;

    PQ pq;
    for (Ring* r : rings) seed_ring(pq, r);

    double total_disp = 0.0;

    while (!pq.empty() && total_vertices(rings) > target_vertices) {
        Collapse cand = pq.top();
        pq.pop();

        // Staleness check: if B or C were already removed, skip
        if (!cand.A->active || !cand.B->active ||
            !cand.C->active || !cand.D->active) continue;

        // Each ring must keep at least 3 vertices
        if (cand.ring->size <= 3) continue;

        // Topology guard
        if (!topology_ok(rings, cand.A, cand.B, cand.C, cand.D, cand.E))
            continue;

        // Apply collapse and re-seed affected windows
        Node* E_node = apply_collapse(cand.ring, cand);
        total_disp += cand.displacement;
        push_around(pq, E_node, cand.ring);
    }

    return total_disp;
}
