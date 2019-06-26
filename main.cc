/*
 * main.cc
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */



#include <cstdlib>
#include <cstdio>

#include "data_reader.h"
#include "solver.h"
#include "solver_spfa.h"
#include "solver_delta.h"
#include "solver_dijkstra.h"
#include "timer.h"

int main(int argc, char **argv) {
	if (argc != 4) {
		fprintf(stderr,
			"Usage: \"%s <graph file> <aux file> <out file> [0]\"\n"
			"    or \"%s <graph file> <aux file> <out file> [<levels>] \"\n"
			"    or \"%s <graph file> <aux file> <out file> [-<log delta>] \"\n",
			argv[0], argv[0], argv[0]);
		exit(0);
	}

	char* gName = argv[1];
	char* aName = argv[2];
	char* oName = argv[3];
	FILE* oFile = fopen(oName, "a");
	fprintf(oFile, "f %s %s\n", gName, aName);

	long n, m, nQ;
	Arc *arcs;
	Node *nodes;
	long *source_array = nullptr;
	DataReader::parse_gr(&n, &m, &nodes, &arcs, gName);
	DataReader::parse_ss(&nQ, &source_array, aName);

	Solver* solver = new SolverDelta(n, nodes);
	solver->Initialize();

	Timer timer;
	for (int i = 0; i < nQ; i++) {
		long source_id = source_array[i] - 1; // 0-index
		solver->Solve(source_id);
		long long chk = solver->Checksum();
		fprintf(oFile,"d %lld\n", chk);
	}
	fprintf(stderr, "c Time (ave, ms): %18.2f\n",
			timer.GetTimeMilliSeconds(nQ));


	return 0;
}
