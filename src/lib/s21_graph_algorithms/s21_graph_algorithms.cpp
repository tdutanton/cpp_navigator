/**
 * @file s21_graph_algorithms.cpp
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

#include "s21_graph_algorithms.h"

Alias::NodesPath GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   const int start_vertex) {
  s21::stack<int> stack_nodes;
  return TraverseGraph(graph, start_vertex, stack_nodes);
}

Alias::NodesPath GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     const int start_vertex) {
  s21::queue<int> queue_nodes;
  return TraverseGraph(graph, start_vertex, queue_nodes);
}

ShortPath GraphAlgorithms::GetShortPath(const Graph& graph,
                                        const int start_index) {
  ShortPath result;
  const size_t size = graph.get_graph_size();
  if (size == 0 || start_index < 0 || static_cast<size_t>(start_index) >= size)
    return result;
  // Container of visit statuses for nodes
  std::vector<bool> visited(size, false);
  // Minimal distance to nodes. distance[i] - current minimal distance from
  // start to i
  std::vector<Alias::distance> distance_array(size, UINT_MAX);
  // Previous node in minimal path
  std::vector<int> prev_node(size, -1);

  // Min-heap - get node with minimal distance
  // pair<unsigned, unsigned> - distance, node_index
  std::priority_queue<
      std::pair<Alias::distance, Alias::node_index>,
      std::vector<std::pair<Alias::distance, Alias::node_index>>,
      std::greater<>>
      queue_nodes;

  // Distance for start_node = 0
  distance_array[start_index] = 0;
  // Push in queue just like in BreadthFirstSearch
  queue_nodes.push(std::make_pair(0, start_index));

  while (!queue_nodes.empty()) {
    // Take the nearest node always - priority_queue helps
    Alias::distance current_distance = queue_nodes.top().first;
    Alias::node_index current_node = queue_nodes.top().second;
    queue_nodes.pop();

    if (visited[current_node]) continue;
    visited[current_node] = true;

    // Look every neighboors (i_neigh) of current_node
    for (Alias::node_index i_neighbor = 0; i_neighbor < size; ++i_neighbor) {
      // Distance from current_node to i_neigh
      Alias::distance weight = graph[current_node][i_neighbor];
      if (weight > 0 && !visited[i_neighbor]) {
        // New distance to neighboor
        Alias::distance perspective_distance = current_distance + weight;
        /// If new distance is lower - refresh distance_array to this node
        // (i_neigh)
        if (perspective_distance < distance_array[i_neighbor]) {
          // Refresh new distance - it's shorter than previous value
          distance_array[i_neighbor] = perspective_distance;
          // Refresh the best prev_node of i_neigh for take a path
          prev_node[i_neighbor] = current_node;
          // Push neighboor to queue to take it in a future
          queue_nodes.push(std::make_pair(perspective_distance, i_neighbor));
        }
      }
    }
  }

  result.distances = distance_array;
  result.prev_nodes = prev_node;
  return result;
}

unsigned GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                         const int vertex1,
                                                         const int vertex2) {
  // minus 1 because of indexes values goes from 0
  const size_t size = graph.get_graph_size();
  if ((vertex1 <= 0 || static_cast<size_t>(vertex1) > size) ||
      (vertex2 <= 0 || static_cast<size_t>(vertex2) > size))
    throw std::invalid_argument("Invalid vertex value");
  int start = vertex1 - 1;
  int end = vertex2 - 1;
  auto [distance_array, prev_node] = GetShortPath(graph, start);
  return distance_array[end];
}

Alias::IntRow GraphAlgorithms::GetShortestVectorBetweenVertices(
    const Graph& graph, const int vertex1, const int vertex2) {
  int start = vertex1 - 1;
  int end = vertex2 - 1;

  auto [distance_array, prev_node] = GetShortPath(graph, start);
  Alias::IntRow short_path;

  if (distance_array[end] != UINT_MAX) {
    for (int at = end; at != -1; at = prev_node[at])
      short_path.push_back(at + 1);
    std::reverse(short_path.begin(), short_path.end());
  }
  return short_path;
}

Alias::IntGrid GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    const Graph& graph) {
  // Get the number of vertices in the graph
  const size_t size = graph.get_graph_size();

  // Check if graph is empty or invalid
  if (size == 0 || !graph.is_valid_graph())
    throw std::invalid_argument("Invalid graph");

  // Initialize result matrix with INT_MAX (representing infinity) for all
  // distances
  Alias::IntGrid result{size, std::vector<int>(size, INT_MAX)};

  // Copy the graph's adjacency matrix to the result matrix
  // Convert 0 values (no edge) to INT_MAX (infinity)
  for (size_t i = 0; i < result.size(); i++) {
    for (size_t j = 0; j < result.size(); j++) {
      if (graph[i][j] == 0)
        result[i][j] = INT_MAX;  // No direct edge between i and j
      else
        result[i][j] = graph[i][j];  // Direct edge with given weight
    }
  }
  // Set distance from each vertex to itself as 0
  for (size_t i = 0; i < result.size(); i++) {
    result[i][i] = 0;
  }
  // Floyd-Warshall algorithm core - dynamic programming approach
  // For each intermediate vertex k, update shortest paths between all pairs
  // (i,j)
  for (size_t k = 0; k < size; k++) {      // Intermediate vertex
    for (size_t i = 0; i < size; i++) {    // Source vertex
      for (size_t j = 0; j < size; j++) {  // Destination vertex
        // Check if path through k exists and can improve current shortest path
        if (result[i][k] != INT_MAX && result[k][j] != INT_MAX) {
          if (result[i][j] > result[i][k] + result[k][j])
            result[i][j] = result[i][k] + result[k][j];  // Update shortest path
        }
      }
    }
  }
  // Convert remaining INT_MAX values (unreachable vertices) back to 0
  // This might be application-specific - some implementations keep them as
  // infinity
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (result[i][j] == INT_MAX) result[i][j] = 0;
    }
  }
  return result;
}

SpanTree GraphAlgorithms::GetSpanTree(const Graph& graph) {
  // Get the number of vertices in the graph
  const size_t size = graph.get_graph_size();

  // Check if graph is empty or invalid
  if (size == 0 || !graph.is_valid_graph())
    throw std::invalid_argument("Invalid graph");

  // Data structures for Prim's algorithm:
  // Track visited vertices
  std::vector<bool> visited(size, false);
  // Minimum distances to each node
  std::vector<Alias::distance> distance_array(size, UINT_MAX);
  // Stores the MST structure (previous nodes)
  std::vector<int> prev_node(size, -1);

  // Priority queue to efficiently get the next minimum-weight edge.
  // The priority queue automatically sorts elements so that the pair with the
  // smallest distance always appears at the top. This is a key data structure
  // for Prim's algorithm to function efficiently, enabling quick access to the
  // next lightest edge to be added to the spanning tree.
  std::priority_queue<
      std::pair<Alias::distance, Alias::node_index>,
      std::vector<std::pair<Alias::distance, Alias::node_index>>,
      std::greater<>>
      queue_nodes;

  int mst_weight = 0;  // Total weight of the MST

  // Start with vertex 0 (distance 0)
  distance_array[0] = 0;
  queue_nodes.push(std::make_pair(0, 0));

  // Main algorithm loop
  while (!queue_nodes.empty()) {
    // Get the closest unvisited vertex
    Alias::node_index current_node = queue_nodes.top().second;
    Alias::distance current_dist = queue_nodes.top().first;
    queue_nodes.pop();

    // Skip if already visited
    if (visited[current_node]) continue;

    // Mark as visited and add to MST weight
    visited[current_node] = true;
    mst_weight += current_dist;

    // Explore all neighbors
    for (Alias::node_index i_neighbor = 0; i_neighbor < size; ++i_neighbor) {
      Alias::distance weight = graph[current_node][i_neighbor];

      // If there's a connection to an unvisited neighbor with better distance
      if (weight > 0 && !visited[i_neighbor] &&
          weight < distance_array[i_neighbor]) {
        // Update distance and previous node
        distance_array[i_neighbor] = weight;
        prev_node[i_neighbor] = current_node;
        // Add to priority queue
        queue_nodes.push(std::make_pair(weight, i_neighbor));
      }
    }
  }

  // Convert the MST structure (prev_node array) to adjacency matrix format
  Alias::IntGrid tree_matrix{size, std::vector<int>(size, 0)};
  for (size_t i = 0; i < size; i++) {
    int u = prev_node[i];
    int v = i;
    if (u != -1) {  // If there's a connection in the MST
      tree_matrix[u][v] = graph[u][v];
      tree_matrix[v][u] = graph[v][u];  // For undirected graph
    }
  }

  // Return both the MST matrix and its total weight
  return {tree_matrix, mst_weight};
}

Alias::IntGrid GraphAlgorithms::GetLeastSpanningTree(const Graph& graph) {
  auto [matrix, weight] = GetSpanTree(graph);
  return matrix;
}

int GraphAlgorithms::GetSpanTreeWeight(const Graph& graph) {
  auto [matrix, weight] = GetSpanTree(graph);
  return weight;
}

Ant::Ant(const Alias::node_index a_start_vertex = 0)
    : start_vertex_{a_start_vertex}, current_vertex_(a_start_vertex) {
  visited_vertices_ = {};
  ant_path_ = {};
}

bool Ant::is_vertex_visited(const Alias::node_index a_vertex) const {
  return visited_vertices_.find(a_vertex) != visited_vertices_.end();
}

bool Ant::is_vertex_unvisited(const Alias::node_index a_vertex) const {
  return visited_vertices_.count(a_vertex) == 0;
}

void Ant::visit_vertex(const Graph& a_graph, const Alias::node_index a_vertex) {
  if (!ant_path_.vertices.empty()) {
    // add distance from current vertex to new
    ant_path_.distance += a_graph[current_vertex_][a_vertex];
  }
  current_vertex_ = a_vertex;
  ant_path_.vertices.push_back(a_vertex);
  visited_vertices_.insert(a_vertex);
}

double AntHill::random_destination() const {
  std::random_device seed;
  std::mt19937 gen(seed());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double result = dist(gen);
  return result;
}

void AntHill::set_alpha_pheromone_weight(const double a_value) {
  alpha_pheromone_weight_ = a_value;
}

void AntHill::set_beta_distance_weight_(const double a_value) {
  beta_distance_weight_ = a_value;
}

void AntHill::set_q_regulation_parameter_(const double a_value) {
  q_regulation_parameter_ = a_value;
}

void AntHill::set_p_pheromone_evaporation_coef(const double a_value) {
  p_pheromone_evaporation_coef_ = a_value;
}

void AntHill::set_start_pheromone_(const double a_value) {
  start_pheromone_ = a_value;
}

bool GraphAlgorithms::is_graph_connected(const Graph& graph) {
  if (graph.get_graph_size() == 0) return false;

  std::vector<bool> visited(graph.get_graph_size(), false);
  std::queue<size_t> q;
  q.push(0);
  visited[0] = true;

  while (!q.empty()) {
    size_t current = q.front();
    q.pop();

    for (size_t neighbor = 0; neighbor < graph.get_graph_size(); ++neighbor) {
      if (graph[current][neighbor] > 0 && !visited[neighbor]) {
        visited[neighbor] = true;
        q.push(neighbor);
      }
    }
  }

  return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
};

AntHill::AntHill(const Graph& a_graph) : graph_{a_graph} {
  anthill_size_ = graph_.get_graph_size();
  pheromone_matrix_ = Alias::PheromoneGrid(
      anthill_size_, std::vector<double>(anthill_size_, start_pheromone_));
  for (size_t i = 0; i < anthill_size_; i++) {
    for (size_t j = 0; j < anthill_size_; j++) {
      if (i != j && graph_[i][j] > 0) {
        pheromone_matrix_[i][j] = start_pheromone_;
      }
    }
  }
}

void AntHill::prepare_ants() {
  ant_squad_.resize(anthill_size_);
  for (size_t i = 0; i < anthill_size_; i++) {
    ant_squad_[i] = Ant(i);
  }
}

std::vector<Alias::node_index> Ant::get_available_neighbors(
    const Graph& a_graph) const {
  const size_t size = a_graph.get_graph_size();
  std::vector<size_t> result;
  for (size_t i_neigh = 0; i_neigh < size; i_neigh++) {
    bool is_neighbor_exists =
        (a_graph[current_vertex_][i_neigh] != 0) ? true : false;
    bool is_neighbor_strange = is_vertex_unvisited(i_neigh);
    if (is_neighbor_exists && is_neighbor_strange) result.push_back(i_neigh);
  }
  return result;
}

double AntHill::greepy_part(const Ant& a_ant,
                            const Alias::node_index a_neighbor) const {
  double weight = graph_[a_ant.get_current_vertex()][a_neighbor];
  if (weight <= 0) return 0.0;
  return pow(1.0 / weight, beta_distance_weight_);
}

double AntHill::herd_part(const Ant& a_ant,
                          const Alias::node_index a_neighbor) const {
  return pow(pheromone_matrix_[a_ant.get_current_vertex()][a_neighbor],
             alpha_pheromone_weight_);
}

double AntHill::ant_desire_to_neighbor(
    const Ant& a_ant, const Alias::node_index a_neighbor) const {
  double greedy = greepy_part(a_ant, a_neighbor);
  double herd = herd_part(a_ant, a_neighbor);
  return greedy * herd;
}

double Ant::pheromone_to_add(const double a_parameter) const {
  return ant_path_.vertices.empty() ? 0.0 : a_parameter / ant_path_.distance;
}

void AntHill::update_pheromone(const Ant& a_ant) {
  for (size_t i = 0; i < anthill_size_; i++) {
    for (size_t j = 0; j < anthill_size_; j++) {
      pheromone_matrix_[i][j] *= (1 - p_pheromone_evaporation_coef_);
    }
  }
  const auto& ant_path_edges = a_ant.get_ant_path_result().vertices;
  const double delta_pheromone =
      a_ant.pheromone_to_add(q_regulation_parameter_);

  for (size_t i = 1; i < ant_path_edges.size(); i++) {
    size_t from = ant_path_edges[i - 1];
    size_t to = ant_path_edges[i];
    pheromone_matrix_[from][to] += delta_pheromone;
  }
}

double AntHill::ant_transition_probability(
    const Ant& a_ant, const Alias::node_index a_neighbor) const {
  std::vector<Alias::node_index> ant_good_neighbors =
      a_ant.get_available_neighbors(graph_);
  double ant_desire_to_j = ant_desire_to_neighbor(a_ant, a_neighbor);
  double ant_summary_desire{0};
  for (const auto& vertex : ant_good_neighbors) {
    ant_summary_desire += ant_desire_to_neighbor(a_ant, vertex);
  }
  return ant_desire_to_j / ant_summary_desire;
}

size_t AntHill::choose_next_vertex(const Ant& a_ant) const {
  std::vector<size_t> available_neighbors =
      a_ant.get_available_neighbors(graph_);
  if (available_neighbors.empty()) {
    return a_ant.get_current_vertex();
  }
  std::vector<double> probabilities;
  double sum_prob = 0.0;
  for (const auto& neighbor : available_neighbors) {
    double prob = ant_transition_probability(a_ant, neighbor);
    probabilities.push_back(prob);
    sum_prob += prob;
  }
  double random = random_destination();
  double summary_probability{0.0};
  for (size_t i = 0; i < available_neighbors.size(); i++) {
    summary_probability += probabilities[i];
    if (random <= summary_probability) return available_neighbors[i];
  }
  return available_neighbors.back();
}

void AntHill::run_ant_colony() {
  prepare_ants();
  for (size_t iteration = 0; iteration < anthill_size_; ++iteration) {
    // All ants build paths
    for (Ant& ant : ant_squad_) {
      while (true) {
        size_t next_vertex = choose_next_vertex(ant);
        if (next_vertex == ant.get_current_vertex() ||
            ant.is_vertex_visited(next_vertex)) {
          break;
        }
        ant.visit_vertex(graph_, next_vertex);
        // Close cycle if goes all vertices
        if (ant.get_ant_path_result().vertices.size() == anthill_size_) {
          size_t start = ant.get_ant_path_result().vertices.front();
          ant.visit_vertex(graph_, start);  // close cycle
        }
      }
    }
    // update pheromone on all routes
    for (Ant& ant : ant_squad_) {
      update_pheromone(ant);
    }
  }
}

TsmResult AntHill::solve_salesman_graph() {
  run_ant_colony();
  TsmResult best_result;
  bool found = false;

  for (const auto& ant : ant_squad_) {
    const auto& res = ant.get_ant_path_result();
    if (res.vertices.size() == anthill_size_ + 1) {
      if (!found || res.distance < best_result.distance) {
        best_result = res;
        found = true;
      }
    }
  }
  return best_result;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph& graph) {
  if (graph.get_graph_size() == 0 || !graph.is_valid_graph()) {
    throw std::invalid_argument("Invalid graph");
  }

  if (!is_graph_connected(graph)) {
    throw std::runtime_error("Graph is not connected - no solution exists");
  }

  AntHill anthill(graph);
  return anthill.solve_salesman_graph();
}