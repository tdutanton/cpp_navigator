#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <iostream>
#include <string>
#include <vector>

#include "common.h"
#include "filereader.h"

class FileReader;

class Graph {
 public:
  explicit Graph(size_t a_size)
      : graph_size_{a_size},
        adjacency_matrix_{a_size, std::vector<int>(a_size, 0)} {}

  Graph() = delete;
  ~Graph() = default;

  static Graph LoadGraphFromFile(const std::string& a_filename);
  void ExportGraphToDot(const std::string& a_filename);

  Alias::IntGrid get_graph_matrix() const { return adjacency_matrix_; }
  size_t get_graph_size() const { return graph_size_; }

  Alias::IntRow& operator[](size_t row) { return adjacency_matrix_[row]; }
  const Alias::IntRow& operator[](size_t row) const {
    return adjacency_matrix_[row];
  }
  void export_config_txt(std::ofstream& a_file);
  void export_node_line_txt(std::ofstream& a_file, unsigned& a_i_node_number,
                            size_t a_row, size_t a_col);

  void print_matrix_graph();

#ifdef TEST
 public:
#else
 private:
#endif
  size_t graph_size_;
  Alias::IntGrid adjacency_matrix_;
};

#endif