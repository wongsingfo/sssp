/*
 * solver_spfa.h
 *
 *  Created on: Jun 26, 2019
 *      Author: wck
 */

#ifndef SOLVER_DIJKSTRA_H_
#define SOLVER_DIJKSTRA_H_

#include <queue>

#include "solver.h"

class SolverDijkstra: public Solver {
public:
	SolverDijkstra(long n, Node nodes[]);
	~SolverDijkstra() override;
	void Initialize() override;
	void Solve(long source_id) override;

private:
	long long max_arc_len_;

  using BucketElement = std::pair<long long, Node*>;
  using Bucket = std::priority_queue<BucketElement,
                                     std::vector<BucketElement>,
                                     std::greater<BucketElement>>;
  Bucket* buckets_;

  static constexpr int delta_log = 4; // delta = 16
};

#endif /* SOLVER_DIJKSTRA_H_ */
