#include "s21_graph.h"

Graph Graph::LoadGraphFromFile(const std::string& a_filename) {
  FileReader filereader;
  try {
    filereader.set_parsed_graph_size(a_filename);
    size_t size = filereader.get_parsed_size();
    Graph result(size);
    Alias::IntGrid matrix = filereader.process_graph_grid(a_filename);
    result.adjacency_matrix_ = matrix;
    return result;
  } catch (const std::exception& e) {
    std::cerr << "Error loading graph: " << e.what() << std::endl;
    throw;
  }
}

void Graph::print_matrix_graph() {
  for (size_t i = 0; i < graph_size_; i++) {
    for (size_t j = 0; j < graph_size_; j++) {
      std::cout << adjacency_matrix_[i][j];
    }
    std::cout << std::endl;
  }
}

void Graph::ExportGraphToDot(const std::string& a_filename) {
  std::ofstream file(a_filename);
  if (!file) {
    std::cerr << "Cannot write to file:" << a_filename << '\n';
    return;
  }
  export_config_txt(file);
  char node_name = Serialize::first_node_name;
  for (size_t i = 0; i < graph_size_; i++) {
    file << Serialize::tab_symb << static_cast<char>(node_name + i)
         << Serialize::semicolon << Serialize::new_line;
  }
  for (size_t i = 0; i < graph_size_; i++) {
    for (size_t j = i; j < graph_size_; j++) {
      if ((node_name + i > static_cast<int>('z')) ||
          (node_name + j > static_cast<int>('z')))
        node_name = Serialize::first_node_name_extra;
      if (adjacency_matrix_[i][j] == 0) continue;
      file << Serialize::tab_symb << static_cast<char>(node_name + i);
      if (adjacency_matrix_[0][j + 1] != 0) {
        export_node_line_txt(file, node_name, i, j);
      }
      file << Serialize::new_line;
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

void Graph::export_node_line_txt(std::ofstream& a_file, const char& a_node_name,
                                 size_t a_row, size_t a_col) {
  if (a_file) {
    a_file << Serialize::double_minus;
    a_file << static_cast<char>(a_node_name + a_col);
    a_file << Serialize::weight_line_part << adjacency_matrix_[a_row][a_col]
           << Serialize::label_line_part << adjacency_matrix_[a_row][a_col]
           << Serialize::end_line;
    a_file << Serialize::semicolon;
  }
}