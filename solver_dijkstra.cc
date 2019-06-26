#include "solver_dijkstra.h"

#include <queue>

SolverDijkstra::SolverDijkstra(long n, Node nodes[])
	: Solver(n, nodes),
    buckets_(nullptr) {
}

// 2 ^ log_ceiling(num) >= num
int log_ceiling(long long num) {
  int res = 1;
  while (((long long) 1 << res) < num) {
    res += 1;
  }
  return res;
}


SolverDijkstra::~SolverDijkstra() {
  if (buckets_) {
    delete[] buckets_;
  }
}

void SolverDijkstra::Initialize() {
	Arc* last_arc = (nodes + n)->first;
	long long max_arc_len = 0;
	for (Arc* arc = nodes->first; arc < last_arc; arc++) {
		if (arc->len > max_arc_len) {
			max_arc_len = arc->len;
		}
	}
	max_arc_len_ = max_arc_len;

  int buffer_log = log_ceiling(max_arc_len_) - delta_log;
  if (!buckets_) buckets_ = new Bucket[1 << buffer_log];
}


void SolverDijkstra::Solve(long source_id) {
  Node* source = nodes + source_id;
  for (Node* node = nodes; node < nodes + n; node++) {
    node->dist = Infinity;
    node->in_queue = false;
  }
  source->dist = 0;

  int buffer_log = log_ceiling(max_arc_len_) - delta_log;
  int buffer_mask = (1 << buffer_log) - 1;

/* distance: 
  | --------- | ----------- | --------- |
  |   ***     | buffer_log  | delta_log |
  |           | buffer_mask |           |
 */
  
  Bucket* buckets = buckets_;
  Bucket* last_bucket = buckets + (1 << buffer_log);
  Bucket* current_bucket = buckets;

  for (Bucket* b = buckets; b < last_bucket; b++) {
    while (! b->empty()) b->pop();
  }

  current_bucket->push(std::make_pair(0, source));
  long final_n = 0;
  long long improvements = improvements_;
  while (final_n < n) {
    while (current_bucket->empty()) {
      current_bucket++;
      if (current_bucket == last_bucket) current_bucket = buckets;
    }

    Node* current = current_bucket->top().second;
    current_bucket->pop();

    if (! current->in_queue) {
      current->in_queue = true;
      final_n += 1;

      Arc* last_arc = (current+1)->first;
      for (Arc* arc = current->first; arc < last_arc; arc++) {
        Node* next = arc->head;
        long long t_dis = current->dist + arc->len;
        if (t_dis < next->dist) {
          improvements += 1;
          next->dist = t_dis;

          Bucket* next_bucket = buckets + ((t_dis >> delta_log) & buffer_mask);
          next_bucket->push(std::make_pair(t_dis, next));
        }
      }
    }
  }

  improvements_ = improvements;
}