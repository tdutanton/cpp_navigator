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

class GraphAlgorithms {
 public:
  static Alias::NodesPath DepthFirstSearch(const Graph& graph,
                                           const int start_vertex);
  static Alias::NodesPath BreadthFirstSearch(const Graph& graph,
                                             const int start_vertex);

  static ShortPath GetShortPath(const Graph& graph, int start_index);
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
};

#include "s21_graph_algorithms.tpp"

#endif