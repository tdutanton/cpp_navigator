#ifndef S21_GRAPH_ALGORITHMS_TPP
#define S21_GRAPH_ALGORITHMS_TPP

#include "s21_graph_algorithms.h"

template <typename T>
Alias::NodesPath TraverseGraph(const Graph& a_graph, int a_start_vertex,
                               T& a_container) {
  Alias::NodesPath result;
  const size_t size = a_graph.get_graph_size();
  if (size == 0 || a_start_vertex <= 0 ||
      static_cast<size_t>(a_start_vertex) > size)
    throw std::invalid_argument("Invalid start vertex value");
  std::vector<bool> visited(size, false);
  a_container.push(a_start_vertex - 1);
  visited[a_start_vertex - 1] = true;
  while (!a_container.empty()) {
    size_t current_node;
    if constexpr (std::is_same_v<T, s21::stack<int>>) {
      current_node = a_container.top();
    } else {
      current_node = a_container.front();
    }
    a_container.pop();
    result.push_back(current_node + 1);
    if constexpr (std::is_same_v<T, s21::stack<int>>) {
      for (int i_neigh = size - 1; i_neigh >= 0; i_neigh--) {
        if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh]) {
          a_container.push(i_neigh);
          visited[i_neigh] = true;
        }
      }
    } else {
      for (size_t i_neigh = 0; i_neigh < size; i_neigh++) {
        if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh]) {
          a_container.push(i_neigh);
          visited[i_neigh] = true;
        }
      }
    }
  }

  return result;
}

#endif