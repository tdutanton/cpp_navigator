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
