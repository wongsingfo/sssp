/*
 * solver_spfa.h
 *
 *  Created on: Jun 26, 2019
 *      Author: wck
 */

#ifndef SOLVER_DELTA_H_
#define SOLVER_DELTA_H_

#include "solver.h"
#include "concurrentqueue.h"

using moodycamel::ConcurrentQueue;

class SolverDelta: public Solver {
 public:
  SolverDelta(long n, Node nodes[]);
  ~SolverDelta() override;
  void Initialize() override;
  void Solve(long source_id) override;

 private:
  long long max_arc_len_;
  static constexpr int num_threads = 1;
  static constexpr int delta_log = 8; // delta = 256
  
  class Bucket {
   public:
    Bucket();
    ~Bucket() = default;
    // void Initialize();
    void Clear();
    bool IsEmpty();
    Node* first_node();

    // before insertion, remove |node| from its orignal bucket
    void Insert(Node* node);
   private:
    Node head_;
  };
  Bucket** p_buckets_;

  using Request = std::pair<long long, Node*>;
  ConcurrentQueue<Request> *queues_;
};

#endif /* SOLVER_DELTA_H_ */
