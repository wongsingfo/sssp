#include "solver_delta.h"

#include <algorithm>
#include <omp.h>

SolverDelta::SolverDelta(long n, Node nodes[])
  : Solver(n, nodes) {
  omp_set_num_threads(num_threads);
}

// 2 ^ log_ceiling(num) >= num
static int log_ceiling(long long num) {
  int res = 1;
  while (((long long) 1 << res) < num) {
    res += 1;
  }
  return res;
}

SolverDelta::~SolverDelta() {
}

void SolverDelta::Initialize() {
  Arc* last_arc = (nodes + n)->first;
  long long max_arc_len = 0;
  for (Arc* arc = nodes->first; arc < last_arc; arc++) {
    if (arc->len > max_arc_len) {
      max_arc_len = arc->len;
    }
  }
  max_arc_len_ = max_arc_len;

  int buffer_log = log_ceiling(max_arc_len_) - delta_log;
  int buffer_size = 1 << buffer_log;
  Bucket** p_buckets = new Bucket*[num_threads];

  for (int p = 0; p < num_threads; p++) {
    p_buckets[p] = new Bucket[buffer_size];
    /*
    Bucket* last_bucket = p_buckets[p] + buffer_size;
    for (Bucket* bucket = p_buckets[p]; bucket < last_bucket; bucket++) {
      bucket->Initialize();
    }
    */
  }

  p_buckets_ = p_buckets;


  queues_ = new ConcurrentQueue<Request>[num_threads];
}

void SolverDelta::Solve(long source_id) {
  int buffer_log = log_ceiling(max_arc_len_) - delta_log;
  int buffer_size = 1 << buffer_log;
  int buffer_mask = (1 << buffer_log) - 1;
  constexpr int max_int = ~(1<<31);
  int min_bucket_id = max_int;
  int global_bucket_id = 0;

  #pragma omp parallel shared(min_bucket_id, global_bucket_id)
  {
    assert(omp_get_num_threads() == num_threads);
    int id = omp_get_thread_num();
    Bucket* buckets = p_buckets_[id];
    Bucket* bucket = buckets;
    Bucket* last_bucket = buckets + (1 << buffer_log);
    int bucket_id = 0;

    int block_size = n / num_threads;
    Node* node_lo = nodes + block_size * id;
    Node* node_hi = nodes + std::min(n, block_size * (id+1));

    for (Node* node = node_lo; node != node_hi; node++) {
      node->dist = Infinity;
      node->prev = nullptr;
      node->next = nullptr;
    }
    Node* source = nodes+source_id;

    for (Bucket* b = buckets; b != last_bucket; b++) b->Clear();

    if (source >= node_lo && source < node_hi) {
      source->dist = 0;
      bucket->Insert(source);
    }

    #pragma omp barrier

    while (1) {
      int last_bucket_id = global_bucket_id + buffer_size;
      bucket = buckets + (global_bucket_id & buffer_mask);
      while (bucket->IsEmpty() && bucket_id < last_bucket_id) {
        bucket++;
        bucket_id += 1;
        if (bucket == last_bucket) {
          bucket = buckets;
        }
      }

      if (bucket_id < min_bucket_id) {
        #pragma omp critical
        {
          if (bucket_id < min_bucket_id) {
            min_bucket_id = bucket_id;
            #pragma omp flush(min_bucket_id)
          }
        }
      }

      #pragma omp barrier
      if (min_bucket_id >= last_bucket_id) break;
      global_bucket_id = min_bucket_id;

      if (bucket_id == min_bucket_id) {
        Node* current = bucket->first_node();
        bucket->Clear();
        while (current != nullptr) {
          Arc* last_arc = (current+1)->first;
          for (Arc* arc = current->first; arc < last_arc; arc++) {
            Node* next = arc->head;
            int next_id = (next-nodes) / block_size;
            long long t_dis = current->dist + arc->len;
            Request req(t_dis, next);

            // TODO(): local node
            queues_[next_id].enqueue(req);
          }
          current = current->next;
        }
      }

      #pragma omp barrier
      
      auto &queue = queues_[id];
      Request req;
      while (queue.try_dequeue(req)) {
        if (req.first < req.second->dist) {
          req.second->dist = req.first;

          int traget_id = (req.first >> delta_log) & buffer_mask;
          buckets[traget_id].Insert(req.second);
        }
      }


      min_bucket_id = max_int;
      #pragma omp barrier
    } // while (1)
  } // omp parallel
}

SolverDelta::Bucket::Bucket() {
  head_.next = nullptr;
}

void SolverDelta::Bucket::Clear() {
  if (! IsEmpty()) {
    first_node()->prev = nullptr;
    head_.next = nullptr;
  }
}

bool SolverDelta::Bucket::IsEmpty() {
  return head_.next == nullptr;
}

Node* SolverDelta::Bucket::first_node() {
  return head_.next;
}

void SolverDelta::Bucket::Insert(Node* node) {
  if (node->prev == nullptr) {
    if (node->next) {
      node->next->prev = nullptr;
    }
  } else {
    if (node->next == nullptr) {
      node->prev->next = nullptr;
    } else {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
  }

  if (! IsEmpty()) {
    first_node()->prev = node;
    node->next = first_node();
  } else {
    node->next = nullptr;
  }

  node->prev = &head_;
  head_.next = node;
}

