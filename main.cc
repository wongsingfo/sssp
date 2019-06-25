/*
 * main.cc
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */


#include <cstdlib>
#include <cstdio>


int main(int argc, char **argv) {
	if (argc != 4) {
		fprintf(stderr,
			"Usage: \"%s <graph file> <aux file> <out file> [0]\"\n"
			"    or \"%s <graph file> <aux file> <out file> [<levels>] \"\n"
			"    or \"%s <graph file> <aux file> <out file> [-<log delta>] \"\n",
			argv[0], argv[0], argv[0]);
		exit(0);
	}


	return 0;
}
