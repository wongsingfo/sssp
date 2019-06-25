#include "solver.h"

Solver::Solver(long n, Node* nodes)
	: n(n), nodes(nodes), checksum_(0LL) {
}

long long Solver::Checksum() {
	long long dist = 0;
	for (Node* node = nodes; node < nodes + n; node++) {
		dist = (dist + (node->dist % MODUL)) % MODUL;
	}
	checksum_ = dist;
	return checksum_;
}

long long Solver::FarthestDistance() {
	long long dist = 0;
	for (Node* node = nodes; node < nodes + n; node++) {
		if (node->dist > dist) {
			dist = node->dist;
		}
	}
	return dist;
}