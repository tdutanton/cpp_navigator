/**
 * @file s21_graph_algorithms.h
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * @brief Graph algorithms implementation including traversal, shortest path,
 * and TSP solutions
 *
 * Contains implementations of various graph algorithms including:
 * - Depth-first and breadth-first search
 * - Shortest path algorithms (Dijkstra, Floyd-Warshall)
 * - Minimum spanning tree algorithms
 * - Ant Colony Optimization for Traveling Salesman Problem
 */

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

/**
 * @brief Generic graph traversal function
 * @tparam T Container type (stack for DFS, queue for BFS)
 * @param[in] a_graph Graph to traverse
 * @param[in] a_start_vertex Starting vertex index
 * @param[in] a_container Data structure to use for traversal
 * @return Sequence of visited nodes
 */
template <typename T>
Alias::NodesPath TraverseGraph(const Graph& a_graph, int a_start_vertex,
                               T& a_container);

/**
 * @brief Structure representing shortest path information
 */
struct ShortPath {
  std::vector<Alias::distance>
      distances;                ///< Distance from source to each vertex
  std::vector<int> prev_nodes;  ///< Previous node in shortest path
};

/**
 * @brief Structure representing spanning tree information
 */
struct SpanTree {
  Alias::IntGrid Tree;  ///< Adjacency matrix of spanning tree
  int tree_weight;      ///< Total weight of spanning tree
};

/**
 * @brief Structure representing TSP solution
 */
struct TsmResult {
  Alias::IntRow vertices;    ///< Sequence of visited vertices
  Alias::distance distance;  ///< Total path distance
};

/**
 * @class GraphAlgorithms
 * @brief Collection of graph algorithms
 */
class GraphAlgorithms {
 public:
  /**
   * @brief Depth-first search traversal
   * @param[in] graph Input graph
   * @param[in] start_vertex Starting vertex index
   * @return Sequence of visited nodes
   */
  static Alias::NodesPath DepthFirstSearch(const Graph& graph,
                                           const int start_vertex);

  /**
   * @brief Breadth-first search traversal
   * @param[in] graph Input graph
   * @param[in] start_vertex Starting vertex index
   * @return Sequence of visited nodes
   */
  static Alias::NodesPath BreadthFirstSearch(const Graph& graph,
                                             const int start_vertex);

  /**
   * @brief Gets shortest paths from source vertex (Dijkstra's algorithm)
   * @param[in] graph Input graph
   * @param[in] start_index Source vertex index
   * @return ShortPath structure with distances and previous nodes
   */
  static ShortPath GetShortPath(const Graph& graph, const int start_index);

  /**
   * @brief Gets shortest path distance between two vertices
   * @param[in] graph Input graph
   * @param[in] vertex1 Source vertex
   * @param[in] vertex2 Target vertex
   * @return Shortest path distance
   */
  static unsigned GetShortestPathBetweenVertices(const Graph& graph,
                                                 const int vertex1,
                                                 const int vertex2);

  /**
   * @brief Gets shortest path sequence between two vertices
   * @param[in] graph Input graph
   * @param[in] vertex1 Source vertex
   * @param[in] vertex2 Target vertex
   * @return Sequence of vertices in shortest path
   */
  static Alias::IntRow GetShortestVectorBetweenVertices(const Graph& graph,
                                                        const int vertex1,
                                                        const int vertex2);

  /**
   * @brief Gets all pairs shortest paths (Floyd-Warshall algorithm)
   * @param[in] graph Input graph
   * @return Distance matrix between all pairs of vertices
   */
  static Alias::IntGrid GetShortestPathsBetweenAllVertices(const Graph& graph);

  /**
   * @brief Gets spanning tree information
   * @param[in] graph Input graph
   * @return SpanTree structure with tree and weight
   */
  static SpanTree GetSpanTree(const Graph& graph);

  /**
   * @brief Gets minimum spanning tree (Prim's or Kruskal's algorithm)
   * @param[in] graph Input graph
   * @return Adjacency matrix of minimum spanning tree
   */
  static Alias::IntGrid GetLeastSpanningTree(const Graph& graph);

  /**
   * @brief Gets weight of minimum spanning tree
   * @param[in] graph Input graph
   * @return Total weight of minimum spanning tree
   */
  static int GetSpanTreeWeight(const Graph& graph);

  /**
   * @brief Solves Traveling Salesman Problem using Ant Colony Optimization
   * @param[in] graph Input graph
   * @return TsmResult with optimal path and distance
   * @throws std::invalid_argument if graph is invalid
   * @throws std::runtime_error if no solution exists
   */
  static TsmResult SolveTravelingSalesmanProblem(const Graph& graph);

  /**
   * @brief Checks if graph is connected
   * @param[in] graph Input graph
   * @return true if graph is connected, false otherwise
   */
  static bool is_graph_connected(const Graph& graph);
};

/**
 * @class Ant
 * @brief Represents an ant in Ant Colony Optimization algorithm
 */
class Ant {
  friend class AntHill;

 public:
  /**
   * @brief Constructs an Ant at starting vertex
   * @param[in] a_start_vertex Starting vertex index
   */
  explicit Ant(const Alias::node_index a_start_vertex);
  ~Ant() = default;

#ifdef TEST
 public:
#else
 private:
#endif                                // TEST
  Alias::node_index start_vertex_;    ///< Starting vertex index
  Alias::node_index current_vertex_;  ///< Current vertex index
  std::unordered_set<Alias::node_index>
      visited_vertices_;  ///< Visited vertices
  TsmResult ant_path_;    ///< Current path and distance

  /**
   * @brief Gets available neighboring vertices
   * @param[in] a_graph Input graph
   * @return Vector of available neighbor indices
   */
  std::vector<Alias::node_index> get_available_neighbors(
      const Graph& a_graph) const;

  /**
   * @brief Calculates pheromone to deposit on path
   * @param[in] a_parameter Regulation parameter Q
   * @return Pheromone amount to deposit
   */
  double pheromone_to_add(const double a_parameter) const;

  /**
   * @brief Moves ant to specified vertex
   * @param[in] a_graph Input graph
   * @param[in] a_vertex Target vertex index
   */
  void visit_vertex(const Graph& a_graph, const Alias::node_index a_vertex);

  /**
   * @brief Checks if vertex was visited
   * @param[in] a_vertex Vertex index to check
   * @return true if visited, false otherwise
   */
  bool is_vertex_visited(const Alias::node_index a_vertex) const;

  /**
   * @brief Checks if vertex wasn't visited
   * @param[in] a_vertex Vertex index to check
   * @return true if not visited, false otherwise
   */
  bool is_vertex_unvisited(const Alias::node_index a_vertex) const;

  /**
   * @brief Gets current path result
   * @return TsmResult with current path and distance
   */
  TsmResult get_ant_path_result() const { return ant_path_; }

  /**
   * @brief Gets current vertex
   * @return Current vertex index
   */
  Alias::node_index get_current_vertex() const { return current_vertex_; }

  /**
   * @brief Gets starting vertex
   * @return Starting vertex index
   */
  Alias::node_index get_start_vertex() const { return start_vertex_; }
};

/**
 * @class AntHill
 * @brief Implements Ant Colony Optimization for TSP
 */
class AntHill {
 public:
  /**
   * @brief Constructs AntHill with given graph
   * @param[in] a_graph Input graph
   */
  explicit AntHill(const Graph& a_graph);

  ~AntHill() = default;  ///< Default destructor

  /**
   * @brief Solves TSP using Ant Colony Optimization
   * @return TsmResult with optimal path and distance
   */
  TsmResult solve_salesman_graph();

  // Parameter setters and getters
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
  Graph graph_;                            ///< Input graph
  Alias::PheromoneGrid pheromone_matrix_;  ///< Pheromone trail matrix
  std::vector<Ant> ant_squad_;             ///< Colony of ants
  size_t anthill_size_;                    ///< Number of vertices in graph

  // Algorithm parameters - set for better result. You can change it
  double alpha_pheromone_weight_ = 1.0;        ///< Pheromone influence weight
  double beta_distance_weight_ = 2.0;          ///< Distance influence weight
  double q_regulation_parameter_ = 100.0;      ///< Pheromone deposit constant
  double p_pheromone_evaporation_coef_ = 0.5;  ///< Evaporation rate
  double start_pheromone_ = 1.0;               ///< Initial pheromone level

  /**
   * @brief Initializes ant colony
   */
  void prepare_ants();

  /**
   * @brief Calculates greedy component of transition probability
   * @param[in] a_ant Current ant
   * @param[in] a_neighbor Neighbor vertex index
   * @return Greedy component value
   */
  double greepy_part(const Ant& a_ant,
                     const Alias::node_index a_neighbor) const;

  /**
   * @brief Calculates pheromone component of transition probability
   * @param[in] a_ant Current ant
   * @param[in] a_neighbor Neighbor vertex index
   * @return Pheromone component value
   */
  double herd_part(const Ant& a_ant, const Alias::node_index a_neighbor) const;

  /**
   * @brief Calculates total desire to move to neighbor
   * @param[in] a_ant Current ant
   * @param[in] a_neighbor Neighbor vertex index
   * @return Combined desire value
   */
  double ant_desire_to_neighbor(const Ant& a_ant,
                                const Alias::node_index a_neighbor) const;

  /**
   * @brief Calculates transition probability to neighbor
   * @param[in] a_ant Current ant
   * @param[in] a_neighbor Neighbor vertex index
   * @return Probability value (0-1)
   */
  double ant_transition_probability(const Ant& a_ant,
                                    const Alias::node_index a_neighbor) const;

  /**
   * @brief Generates random number for probabilistic selection
   * @return Random value between 0 and 1
   */
  double random_destination() const;

  /**
   * @brief Updates pheromone trails based on ant's path
   * @param[in] a_ant Ant whose path to use for update
   */
  void update_pheromone(const Ant& a_ant);

  /**
   * @brief Selects next vertex for ant to visit
   * @param[in] a_ant Current ant
   * @return Selected vertex index
   */
  Alias::node_index choose_next_vertex(const Ant& a_ant) const;

  /**
   * @brief Runs complete ant colony optimization cycle
   */
  void run_ant_colony();
};

#include "s21_graph_algorithms.tpp"

#endif