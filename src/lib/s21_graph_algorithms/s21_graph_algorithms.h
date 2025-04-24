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

class Ant {
  friend class AntHill;

 public:
  explicit Ant(const Alias::node_index a_start_vertex);
  ~Ant() = default;

#ifdef TEST
 public:
#else
 private:
#endif  // TEST
  /// @brief Index of start ant's point
  Alias::node_index start_vertex_;
  /// @brief Index of point - where's ant's now
  Alias::node_index current_vertex_;
  /// @brief unordered_set for quick search in is_vertex_unvisited
  std::unordered_set<Alias::node_index> visited_vertices_;
  /// @brief Alias::IntRow vertices; double distance;
  TsmResult ant_path_;

  /** @brief Get vector of available vertices for ant journey (if path == 0 and
   * if neighbor was visited)
   * @param a_graph Graph
   * @return vector of available vertices for ant journey (vector<size_t>)
   */
  std::vector<Alias::node_index> get_available_neighbors(
      const Graph& a_graph) const;
  /**
   * @brief Count of pheromone added on ant's way after journey
   *
   * @param a_parameter parameter Q - q_regulation_parameter_ from AntHill
   * @return double - pheromone
   */
  double pheromone_to_add(const double a_parameter) const;
  void visit_vertex(const Graph& a_graph, const Alias::node_index a_vertex);

  bool is_vertex_visited(const Alias::node_index a_vertex) const;
  bool is_vertex_unvisited(const Alias::node_index a_vertex) const;

  TsmResult get_ant_path_result() const { return ant_path_; }
  Alias::node_index get_current_vertex() const { return current_vertex_; }
  Alias::node_index get_start_vertex() const { return start_vertex_; }
};

class AntHill {
 public:
  explicit AntHill(const Graph& a_graph);
  ~AntHill() = default;

  TsmResult solve_salesman_graph();

  void set_alpha_pheromone_weight(const double a_value);
  double get_alpha_pheromone_weight() const { return alpha_pheromone_weight_; }

  void set_beta_distance_weight_(const double a_value);
  double get_beta_distance_weight() const { return beta_distance_weight_; }

  void set_q_regulation_parameter_(const double a_value);
  double get_q_regulation_parameter() const { return q_regulation_parameter_; }

  void set_p_pheromone_evaporation_coef(const double a_value);
  double get_p_pheromone_evaporation_coef() const {
    return p_pheromone_evaporation_coef_;
  }

  void set_start_pheromone_(const double a_value);
  double get_start_pheromone() const { return start_pheromone_; }

  size_t get_anthill_size() const { return anthill_size_; }

#ifdef TEST
 public:
#else
 private:
#endif
  Graph graph_;
  Alias::PheromoneGrid pheromone_matrix_;
  std::vector<Ant> ant_squad_;
  size_t anthill_size_;
  /// @brief From 0 to 1. 0 - greedy algo
  double alpha_pheromone_weight_ = 1.0;
  //! TODO comments
  ///  @brief from ?? to ??
  double beta_distance_weight_ = 2.0;
  /**
   * @brief Parameter Q for get good speed of algorithm. 1 - for small graphs,
   * 100 - default value for most of graphs, Lko - length of greedy algo - for
   * big and scary graphs
   */
  double q_regulation_parameter_ = 100.0;
  /// @brief Small value - the same paths, big value - fast and boring paths
  double p_pheromone_evaporation_coef_ = 0.5;
  /// @brief Start value of pheromone on every non-zero edge
  double start_pheromone_ = 1.0;

  void prepare_ants();
  /// @brief Жадность
  double greepy_part(const Ant& a_ant,
                     const Alias::node_index a_neighbor) const;
  /// @brief Стадность
  double herd_part(const Ant& a_ant, const Alias::node_index a_neighbor) const;
  /// @brief Желание муравья идти в соседний узел
  double ant_desire_to_neighbor(const Ant& a_ant,
                                const Alias::node_index a_neighbor) const;
  /// @brief Вероятность перемещения к соседу
  double ant_transition_probability(const Ant& a_ant,
                                    const Alias::node_index a_neighbor) const;
  /// @brief Сгенерированная случайная величина для выбора соседа
  double random_destination() const;
  void update_pheromone(const Ant& a_ant);
  Alias::node_index choose_next_vertex(const Ant& a_ant) const;
  void run_ant_colony();
};

#include "s21_graph_algorithms.tpp"

#endif