#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <queue>
#include <random>
#include <unordered_set>

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
  Alias::distance distance;
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
  explicit Ant(const size_t a_start_vertex = 0)
      : start_vertex_{a_start_vertex} {}
  ~Ant() = default;

  Alias::NodesPath get_available_neighbors(
      const Graph&
          a_graph);  ///< Get vector of available vertices for ant journey (if
                     ///< path == 0 and if neighbor was visited)

  double mark_pheromone();  ///< Пометить путь феромоном

  double random_destination();  ///< Сгенерированная случайная величина для
                                ///< выбора соседа
  TsmResult get_ant_path_result() const { return ant_path_; }

  bool is_vertex_visited(const size_t a_vertex) const {
    return visited_vertices_.find(a_vertex) != visited_vertices_.end();
  }

  void visit_vertex(const size_t a_vertex) {
    journey_history_.push_back(a_vertex);
    visited_vertices_.insert(a_vertex);
  }

  bool is_vertex_unvisited(const size_t vertex) const {
    return visited_vertices_.count(vertex) == 0;
  }

 private:
  size_t start_vertex_;
  size_t current_vertex_;
  bool is_available_next_step_;
  std::unordered_set<size_t>
      visited_vertices_;  ///< For quick search in is_vertex_unvisited
  Alias::NodesPath journey_history_;
  TsmResult ant_path_;  //   Alias::IntRow vertices; double distance;
};

class AntHill {
 public:
  AntHill(const Graph& a_graph);
  ~AntHill() = default;

  double ant_transition_probability(
      const size_t a_current_vertex, const size_t a_neighbor,
      const double a_pheromone_value);  ///< Вероятность перемещения к соседу

  void set_alpha_pheromone_weight(const double a_value) {
    alpha_pheromone_weight_ = a_value;
  }
  void set_beta_distance_weight_(const double a_value) {
    beta_distance_weight_ = a_value;
  }
  void set_q_regulation_parameter_(const double a_value) {
    q_regulation_parameter_ = a_value;
  }
  void set_p_pheromone_evaporation_coef(const double a_value) {
    p_pheromone_evaporation_coef = a_value;
  }
  void set_start_pheromone_(const double a_value) {
    start_pheromone_ = a_value;
  }

 private:
  Graph graph_;
  Alias::PheromoneGrid pheromone_matrix_;
  std::vector<Ant> ant_squad_;
  size_t anthill_size_;
  double alpha_pheromone_weight_ = 1.0;  ///< from 0 to 1. 0 - greedy algo
  double beta_distance_weight_ = 2.0;    ///< from ?? to ??
  double q_regulation_parameter_ =
      100.0;  ///< parameter for get good speed of algorithm. 1 - for small
  ///< graphs, 100 - default value for most of graphs, Lko - length
  ///< of greedy algo - for big and scary graphs
  double p_pheromone_evaporation_coef =
      0.1;  ///< small value - the same paths, big value - fast and boring paths
  double start_pheromone_ = 1.0;

  void prepare_ants();
};

#include "s21_graph_algorithms.tpp"

#endif