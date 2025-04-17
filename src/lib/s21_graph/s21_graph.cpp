#include "s21_graph.h"

Graph Graph::LoadGraphFromFile(const std::string& a_filename) {
  FileReader filereader;
  if (!filereader.set_parsed_graph_size(a_filename)) {
    throw std::invalid_argument("Cannot load graph from file: " + a_filename);
  }
  const size_t size = filereader.get_parsed_size();
  Graph result(size);
  result.valid_graph_ = true;
  Alias::IntGrid matrix = filereader.process_graph_grid();
  result.adjacency_matrix_ = matrix;
  return result;
}

void Graph::ExportGraphToDot(const std::string& a_filename) {
  std::ofstream file(a_filename);
  if (!file) {
    throw std::invalid_argument("Cannot write to file: " + a_filename);
  }
  export_config_txt(file);
  unsigned i_node_number = 1;
  for (size_t i = 0; i < graph_size_; i++) {
    file << Serialize::tab_symb << (i_node_number + i) << Serialize::semicolon
         << Serialize::new_line;
  }
  for (size_t i = 0; i < graph_size_; i++) {
    for (size_t j = i; j < graph_size_; j++) {
      if (adjacency_matrix_[i][j] != 0) {
        file << Serialize::tab_symb << (i_node_number + i);
        file << Serialize::double_minus << (i_node_number + j);
        file << Serialize::weight_line_part << adjacency_matrix_[i][j];
        file << Serialize::label_line_part << adjacency_matrix_[i][j];
        file << Serialize::end_line << Serialize::semicolon;
        file << Serialize::new_line;
      }
    }
  }
  file << Serialize::closed_bracket;
  file.close();
}

void Graph::export_config_txt(std::ofstream& a_file) {
  if (a_file) {
    a_file << Serialize::start_dot_file;
    a_file << Serialize::txt_shape;
    a_file << Serialize::txt_edge_color;
  }
}

void Graph::export_node_line_txt(std::ofstream& a_file,
                                 unsigned& a_i_node_number, size_t a_row,
                                 size_t a_col) {
  if (a_file) {
    a_file << Serialize::double_minus;
    a_file << a_i_node_number + a_col;
    a_file << Serialize::weight_line_part << adjacency_matrix_[a_row][a_col]
           << Serialize::label_line_part << adjacency_matrix_[a_row][a_col]
           << Serialize::end_line;
    a_file << Serialize::semicolon;
  }
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
  for (size_t i = 0; i < graph.get_graph_size(); i++) {
    for (size_t j = 0; j < graph.get_graph_size(); j++) {
      os << graph[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}