#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <string>
#include <vector>

#include "common.h"

class Graph {
 public:
  explicit Graph(size_t a_size)
      : graph_size_{a_size},
        adjacency_matrix_{a_size, std::vector<int>(a_size, 0)} {}

  Graph() = delete;

  ~Graph() = default;

  Graph LoadGraphFromFile(std::string filename);
  // void File ExportGraphToDot(std::string filename);

  Alias::IntGrid get_graph_matrix() const { return adjacency_matrix_; }
  size_t get_graph_size() const { return graph_size_; }

#ifdef TEST
 public:
#else
 private:
#endif
  Alias::IntGrid adjacency_matrix_;
  size_t graph_size_;

  void set_graph_size(size_t a_size);
};

#endif