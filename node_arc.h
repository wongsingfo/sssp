/*
 * node_arc.h
 *
 *  Created on: Jun 25, 2019
 *      Author: wck
 */

#ifndef NODE_ARC_H_
#define NODE_ARC_H_

struct Node;

struct Arc {
	long long len;
	Node *head;
};

struct Node {
	long long dist;
	Arc* first;
	// int tStamp;
	bool in_queue;

  // used for linked list
  Node* next;
  Node* prev;
};



#endif /* NODE_ARC_H_ */
