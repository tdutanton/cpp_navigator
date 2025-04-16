#ifndef S21_GRAPH_ALGORITHMS_TPP
#define S21_GRAPH_ALGORITHMS_TPP

#include "s21_graph_algorithms.h"

template <typename T>
Alias::NodesPath TraverseGraph(const Graph& a_graph, int a_start_vertex,
                               T& a_container) {
  Alias::NodesPath result;
  const size_t size = a_graph.get_graph_size();
  if (size == 0 || a_start_vertex < 0 ||
      static_cast<size_t>(a_start_vertex) >= size)
    return result;
  std::vector<bool> visited(size, false);

  a_container.push(a_start_vertex - 1);

  while (!a_container.empty()) {
    unsigned current_node;
    if constexpr (std::is_same_v<T, s21::stack<unsigned>>) {
      current_node = a_container.top();
    } else {
      current_node = a_container.front();
    }
    a_container.pop();
    if (!visited[current_node]) {
      visited[current_node] = true;
      result.push_back(current_node + 1);
      if constexpr (std::is_same_v<T, s21::stack<unsigned>>) {
        for (int i_neigh = size - 1; i_neigh >= 0; i_neigh--) {
          if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh])
            a_container.push(i_neigh);
        }
      } else {
        for (size_t i_neigh = 0; i_neigh < size; i_neigh++) {
          if (a_graph[current_node][i_neigh] != 0 && !visited[i_neigh])
            a_container.push(i_neigh);
        }
      }
    }
  }

  return result;
}

#endif