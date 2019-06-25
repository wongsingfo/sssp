/*
 * solver_spfa.h
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#ifndef SOLVER_SPFA_H_
#define SOLVER_SPFA_H_

#include "solver.h"

class SolverSpfa: public Solver {
public:
	SolverSpfa(long n, Node nodes[]);
	~SolverSpfa() override = default;
	void Initialize() override;
	void Solve(long source_id) override;
};

#endif /* SOLVER_SPFA_H_ */
