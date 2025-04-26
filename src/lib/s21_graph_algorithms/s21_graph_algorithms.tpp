/**
 * @file s21_graph_algorithms.tpp
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * @brief Generic graph traversal function
 */

#ifndef S21_GRAPH_ALGORITHMS_TPP
#define S21_GRAPH_ALGORITHMS_TPP

#include "s21_graph_algorithms.h"

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
                               T& a_container) {
  Alias::NodesPath result;
  const size_t size = a_graph.get_graph_size();
  if (size == 0 || a_start_vertex <= 0 ||
      static_cast<size_t>(a_start_vertex) > size)
    throw std::invalid_argument("Invalid start vertex value");
  // vector of vertices' indexes - visited index or not
  std::vector<bool> visited(size, false);
  // minus 1 - because we get a_start_vertex from 1, and we have indexes from 0
  // push start vertex to container (stack for DBS or queue for BFS)
  a_container.push(a_start_vertex - 1);
  // we were in start vertex
  visited[a_start_vertex - 1] = true;
  // main algorithm loop and quit point from cycle
  while (!a_container.empty()) {
    // iteration object
    size_t current_node;
    // current vertex - top of container
    // stack - DFS
    if constexpr (std::is_same_v<T, s21::stack<int>>) {
      current_node = a_container.top();
    }
    // queue - BFS
    else {
      current_node = a_container.front();
    }
    // get current vertex from container
    a_container.pop();
    // push current vertex (+1) to container
    result.push_back(current_node + 1);
    // stack - DFS
    if constexpr (std::is_same_v<T, s21::stack<int>>) {
      // go from the last neighbor of current vertex
      for (int i_neigh = size - 1; i_neigh >= 0; i_neigh--) {
        if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh]) {
          // push new not visited neighbor to stack
          a_container.push(i_neigh);
          visited[i_neigh] = true;
        }
      }
    }
    // queue - BFS
    else {
      // go from the first neighbor of current vertex
      for (size_t i_neigh = 0; i_neigh < size; i_neigh++) {
        if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh]) {
          // push new not visited neighbor to queue
          a_container.push(i_neigh);
          visited[i_neigh] = true;
        }
      }
    }
  }
  // get final vector of vertices
  return result;
}

#endif