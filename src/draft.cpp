#include <iostream>
#include <random>

#include "lib/s21_graph/common.h"
#include "lib/s21_graph/filereader.h"
#include "lib/s21_graph/s21_graph.h"
#include "lib/s21_graph_algorithms/s21_graph_algorithms.h"

int main() {
  std::string a_filename = "gr_old.txt";
  Graph res = Graph::LoadGraphFromFile(a_filename);
  Alias::NodesPath result = GraphAlgorithms::BreadthFirstSearch(res, 2);

  for (size_t i : result) {
    std::cout << i << " ";
  }

  return 0;
}