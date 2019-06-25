/*
 * data_reader.h
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#ifndef DATA_READER_H_
#define DATA_READER_H_

#include "node_arc.h"

#include <string>
#include <cstdio>

class DataReader {

public:
	inline static int parse_gr(long *n_ad, long *m_ad,
				Node **nodes_ad, Arc **arcs_ad, char *gName) {
		long _;
		return parse_gr(n_ad, m_ad, nodes_ad, arcs_ad, &_, gName);
	}

	static int parse_ss(long *sN_ad, long **source_array, char *aName);

private:
	static int parse_gr(long *n_ad, long *m_ad,
				Node **nodes_ad, Arc **arcs_ad,
				long *node_min_ad, char *gName);
};

#endif /* DATA_READER_H_ */
