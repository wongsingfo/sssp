/*
 * solver_spfa.cc
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#include "solver_spfa.h"
#include <queue>

SolverSpfa::SolverSpfa(long n, Node nodes[])
	: Solver(n, nodes) {
}

void SolverSpfa::Initialize() {
	for (Node* node = nodes; node < nodes + n; node++) {
		node->in_queue = false;
	}
}

void SolverSpfa::Solve(long source_id) {
	std::deque<Node*> que;
	Node* source = nodes + source_id;

	for (Node* node = nodes; node < nodes + n; node++) {
		node->dist = Infinity;
	}
	source->dist = 0;
	que.push_back(source);
	while (! que.empty()) {
		Node* current;
		if (que.back()->dist < que.front()->dist) {
			current = que.back();
			que.pop_back();
		} else {
			current = que.front();
			que.pop_front();
		}
		current->in_queue = false;

		Arc* last_arc = (current+1)->first;
		for (Arc* arc = current->first; arc < last_arc; arc++) {
			Node* next = arc->head;
			long long t_dis = current->dist + arc->len;
			if (t_dis < next->dist) {
				next->dist = t_dis;
				if (! next->in_queue) {
					next->in_queue = true;
					que.push_back(next);
				}
			}
		}
	}
}
