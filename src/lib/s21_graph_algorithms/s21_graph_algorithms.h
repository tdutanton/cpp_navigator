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
      : start_vertex_{a_start_vertex}, current_vertex_(a_start_vertex) {}
  ~Ant() = default;

  std::vector<size_t> get_available_neighbors(const Graph& a_graph)
      const;  ///< Get vector of available vertices for ant journey (if
  ///< path == 0 and if neighbor was visited)

  double pheromone_to_add(
      const double a_parameter) const;  ///< Сколько феромона оставляем на пути

  TsmResult get_ant_path_result() const { return ant_path_; }

  bool is_vertex_visited(const size_t a_vertex) const {
    return visited_vertices_.find(a_vertex) != visited_vertices_.end();
  }

  void visit_vertex(const Graph& a_graph, const size_t vertex) {
    if (!ant_path_.vertices.empty()) {
      // Добавляем расстояние от предыдущей вершины к новой
      ant_path_.distance += a_graph[current_vertex_][vertex];
    }
    current_vertex_ = vertex;
    ant_path_.vertices.push_back(vertex);
    visited_vertices_.insert(vertex);
  }

  bool is_vertex_unvisited(const size_t vertex) const {
    return visited_vertices_.count(vertex) == 0;
  }

  size_t get_current_vertex() const { return current_vertex_; }
  size_t get_start_vertex() const { return start_vertex_; }

 private:
  size_t start_vertex_;
  size_t current_vertex_;
  bool is_available_next_step_ = true;
  std::unordered_set<size_t>
      visited_vertices_;  ///< For quick search in is_vertex_unvisited
  Alias::NodesPath journey_history_;
  TsmResult ant_path_ = {};  //   Alias::IntRow vertices; double distance;
};

class AntHill {
 public:
  AntHill(const Graph& a_graph);
  ~AntHill() = default;

  double greepy_part(const Ant& a_ant,
                     const size_t a_neighbor) const;  ///< Жадность

  double herd_part(const Ant& a_ant,
                   const size_t a_neighbor) const;  ///< Стадность

  double ant_desire_to_neighbor(
      const Ant& a_ant,
      const size_t a_neighbor) const;  ///< Желание муравья идти в соседний узел

  double ant_transition_probability(
      const Ant& a_ant,
      const size_t a_neighbor);  ///< Вероятность перемещения к соседу

  double random_destination();  ///< Сгенерированная случайная величина для
                                ///< выбора соседа

  void update_pheromone(const Ant& a_ant);

  size_t choose_next_vertex(const Ant& a_ant);

  void run_ant_colony();

  TsmResult solve_salesman_graph();

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
    p_pheromone_evaporation_coef_ = a_value;
  }
  void set_start_pheromone_(const double a_value) {
    start_pheromone_ = a_value;
  }

  double get_alpha_pheromone_weight() const { return alpha_pheromone_weight_; }
  double get_beta_distance_weight() const { return beta_distance_weight_; }
  double get_q_regulation_parameter() const { return q_regulation_parameter_; }
  double get_p_pheromone_evaporation_coef() const {
    return p_pheromone_evaporation_coef_;
  }
  double get_start_pheromone() const { return start_pheromone_; }
  size_t get_anthill_size() const { return anthill_size_; }

 private:
  Graph graph_;
  Alias::PheromoneGrid pheromone_matrix_;
  std::vector<Ant> ant_squad_;
  size_t anthill_size_;
  double alpha_pheromone_weight_ = 10.0;  ///< from 0 to 1. 0 - greedy algo
  double beta_distance_weight_ = 0.01;    ///< from ?? to ??
  double q_regulation_parameter_ =
      100.0;  ///< parameter for get good speed of algorithm. 1 - for small
  ///< graphs, 100 - default value for most of graphs, Lko - length
  ///< of greedy algo - for big and scary graphs
  double p_pheromone_evaporation_coef_ =
      0.3;  ///< small value - the same paths, big value - fast and boring paths
  double start_pheromone_ = 100.0;

  void prepare_ants();
};

#include "s21_graph_algorithms.tpp"

#endif