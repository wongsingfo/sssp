/*
 * solver.h
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "node_arc.h"

class Solver {
public:
	Solver(long n, Node* nodes);
    virtual ~Solver() = default;
    virtual void Initialize() = 0;
    virtual void Solve(long source_id) = 0;
    long long Checksum();
    long long FarthestDistance();
    static constexpr long long MODUL = (long long) 1 << 62;
    static constexpr long long Infinity = 9223372036854775807LL; // LLONG_MAX
    long long improvements_;

protected:
    int n;
	Node* nodes;

private:
	long long checksum_;
};

#endif /* SOLVER_H_ */
