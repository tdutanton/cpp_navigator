#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <queue>

#include "../s21_graph/s21_graph.h"
#include "../s21_linked_list/s21_linked_list.h"
#include "../s21_queue/s21_queue.h"
#include "../s21_stack/s21_stack.h"

class Graph;
template <typename T>
Alias::NodesPath TraverseGraph(const Graph& a_graph, int a_start_vertex,
                               T& a_container);

struct ShortPath {
  std::vector<Alias::distance> distances;
  std::vector<int> prev_nodes;
};

struct SpanTree {
  Alias::IntGrid Tree;
  int tree_weight;
};

struct TsmResult {
  Alias::IntRow vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  static Alias::NodesPath DepthFirstSearch(const Graph& graph,
                                           const int start_vertex);
  static Alias::NodesPath BreadthFirstSearch(const Graph& graph,
                                             const int start_vertex);

  static ShortPath GetShortPath(const Graph& graph, const int start_index);
  static unsigned GetShortestPathBetweenVertices(const Graph& graph,
                                                 const int vertex1,
                                                 const int vertex2);
  static Alias::IntRow GetShortestVectorBetweenVertices(const Graph& graph,
                                                        const int vertex1,
                                                        const int vertex2);

  static Alias::IntGrid GetShortestPathsBetweenAllVertices(const Graph& graph);

  static SpanTree GetSpanTree(const Graph& graph);
  static Alias::IntGrid GetLeastSpanningTree(const Graph& graph);
  static int GetSpanTreeWeight(const Graph& graph);

  static TsmResult SolveTravelingSalesmanProblem(const Graph& graph);
};

// ANTZZZ

class Ant {
 public:
  Ant() : start_vertex_{0} {}
  explicit Ant(unsigned a_start_vertex) : start_vertex_{a_start_vertex} {}
  ~Ant() = default;

  double mark_pheromone();
  double transition_probability(unsigned a_current_vertex, unsigned a_neighbor);
  double random_destination();

 private:
  TsmResult ant_path_;  //   Alias::IntRow vertices; double distance;
  unsigned start_vertex_;
  unsigned current_vertex_;
  bool is_available_next_step_;
};

class AntHill {
 public:
  AntHill(const Graph& a_graph);
  ~AntHill() = default;

 private:
  std::vector<Ant> ant_squad_;
  double alpha_pheromone_weight_ = 1.0;  ///< from 0 to 1. 0 - greedy algo
  double beta_distance_weight_ = 2.0;    ///< from ?? to ??
  double q_regulation_parameter_ =
      100.0;  ///< parameter for get good speed of algorithm. 1 - for small
  ///< graphs, 100 - default value for most of graphs, Lko - length
  ///< of greedy algo - for big and scary graphs
  double p_pheromone_evaporation_coef =
      0.1;  ///< small value - the same paths, big value - fast and boring paths
};

#include "s21_graph_algorithms.tpp"

#endif