/**
 * @file s21_graph.h
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * @brief A class representing a graph using an adjacency matrix
 */
#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <iostream>
#include <string>
#include <vector>

#include "common.h"
#include "filereader.h"

class FileReader;

/**
 * @class Graph
 * @brief A class representing a graph using an adjacency matrix.
 *
 * This class provides functionality to load a graph from a file, export it to
 * DOT format, and access/modify the adjacency matrix. The graph can be
 * validated for correctness.
 */
class Graph {
 public:
  /**
   * @brief Constructs a Graph with a specified size.
   * @param[in] a_size The number of vertices in the graph (default is 0).
   */
  explicit Graph(size_t a_size = 0)
      : graph_size_{a_size},
        adjacency_matrix_{a_size, std::vector<int>(a_size, 0)},
        valid_graph_{false} {}

  Graph() = delete;    ///< Default constructor is deleted.
  ~Graph() = default;  ///< Default destructor.

  /**
   * @brief Loads a graph from a file.
   * @param[in] a_filename The name of the file to load the graph from.
   * @return A Graph object constructed from the file.
   */
  static Graph LoadGraphFromFile(const std::string& a_filename);

  /**
   * @brief Exports the graph to a DOT format file.
   * @param[in] a_filename The name of the file to export the graph to.
   */
  void ExportGraphToDot(const std::string& a_filename);

  /**
   * @brief Gets the adjacency matrix of the graph.
   * @return The adjacency matrix as a 2D vector of integers.
   */
  Alias::IntGrid get_graph_matrix() const { return adjacency_matrix_; }

  /**
   * @brief Gets the number of vertices in the graph.
   * @return The size of the graph.
   */
  size_t get_graph_size() const { return graph_size_; }

  /**
   * @brief Checks if the graph is valid.
   * @return True if the graph is valid, false otherwise.
   */
  bool is_valid_graph() const { return valid_graph_; }

  /**
   * @brief Accesses a row of the adjacency matrix for modification.
   * @param row The index of the row to access.
   * @return A reference to the specified row in the adjacency matrix.
   */
  Alias::IntRow& operator[](size_t row) { return adjacency_matrix_[row]; }

  /**
   * @brief Accesses a row of the adjacency matrix (const version).
   * @param row The index of the row to access.
   * @return A const reference to the specified row in the adjacency matrix.
   */
  const Alias::IntRow& operator[](size_t row) const {
    return adjacency_matrix_[row];
  }

#ifdef TEST
 public:
#else
 private:
#endif  // TEST
  /// The number of vertices in the graph.
  size_t graph_size_;
  /// The adjacency matrix representing the graph.
  Alias::IntGrid adjacency_matrix_;
  /// Flag indicating if the graph is valid.
  bool valid_graph_;

  /**
   * @brief Exports configuration text to a file.
   * @param[in] a_file The output file stream to write to.
   */
  void export_config_txt(std::ofstream& a_file);

  /**
   * @brief Exports a node line to a file.
   * @param[in] a_file The output file stream to write to.
   * @param[in] a_i_node_number Reference to the node number.
   * @param[in] a_row The row index in the adjacency matrix.
   * @param[in] a_col The column index in the adjacency matrix.
   */
  void export_node_line_txt(std::ofstream& a_file, unsigned& a_i_node_number,
                            size_t a_row, size_t a_col);
};

/**
 * @brief Overloads the << operator to print the graph.
 * @param[in] os The output stream.
 * @param[in] graph The graph to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif