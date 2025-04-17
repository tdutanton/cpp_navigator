#include "cli.h"

/* int main() {
  Graph g = Graph::LoadGraphFromFile("gr.txt");
  AntHill hill = AntHill(g);

  TsmResult res = hill.solve_salesman_graph();

  std::cout << res.distance << std::endl;
  for (const auto& i : res.vertices) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::sort(res.vertices.begin(), res.vertices.end());

  for (const auto& i : res.vertices) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
} */

int main() {
  clear_console();
  MenuPair menu_labels = make_menu_points();
  Graph graph(0);
  int size{0};
  std::string filename;
  int choice = -1;
  while (choice != static_cast<int>(USER_INPUT::EXIT)) {
    print_menu(menu_labels);
    choice = get_choice(static_cast<int>(USER_INPUT::ANTS));
    USER_INPUT input = static_cast<USER_INPUT>(choice);
    switch (input) {
      case USER_INPUT::LOAD: {
        clear_console();
        set_graph_from_file(graph, size, filename);
        clear_console();
        print_current_graph_info(filename, graph);
        break;
      }
      case USER_INPUT::BFS: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_bfs(graph, size);
        break;
      }
      case USER_INPUT::DFS: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_dfs(graph, size);
        break;
      }
      case USER_INPUT::DIJKSTRA: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_dijkstra(graph, size);
        break;
      }
      case USER_INPUT::FLOYD: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_floyd(graph);
        break;
      }
      case USER_INPUT::TREE: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_tree(graph);
        break;
      }
      case USER_INPUT::ANTS: {
        clear_console();
        print_current_graph_info(filename, graph);
        set_ants(graph);
        break;
      }
      default:
        break;
    }
  }
  return 0;
}

/* int main() {
  Graph res = Graph::LoadGraphFromFile("gr.txt");
  std::cout << "Graph" << std::endl;
  std::cout << res;
  std::cout << std::endl;

  res.ExportGraphToDot("asd.dot");
  std::vector<unsigned> result = GraphAlgorithms::DepthFirstSearch(res, 0);
  std::vector<unsigned> result_w = GraphAlgorithms::BreadthFirstSearch(res, 0);

  std::cout << "DepthFirstSearch - нерекурентный поиск в глубину" << std::endl;
  for (const auto& i : result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "BreadthFirstSearch - поиск в ширину" << std::endl;
  for (const auto& i : result_w) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  unsigned path = GraphAlgorithms::GetShortestPathBetweenVertices(res, 1, 5);
  std::cout << "GetShortestPathBetweenVertices - поиск кратчайшего пути "
               "алгоритм Дейкстры"
            << std::endl;
  std::cout << path << '\n';
  std::cout << std::endl;
  for (const auto& i :
       GraphAlgorithms::GetShortestVectorBetweenVertices(res, 1, 5)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  Alias::IntGrid m_p = GraphAlgorithms::GetShortestPathsBetweenAllVertices(res);
  std::cout << "GetShortestPathsBetweenAllVertices - поиск кратчайших путей "
               "между всеми парами"
            << std::endl;
  for (size_t i = 0; i < m_p.size(); i++) {
    for (size_t j = 0; j < m_p.size(); j++) {
      std::cout << m_p[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  Alias::IntGrid m_g = GraphAlgorithms::GetLeastSpanningTree(res);
  std::cout << "GetLeastSpanningTree - поиск наименьшего остовного дерева"
            << std::endl;
  for (size_t i = 0; i < m_g.size(); i++) {
    for (size_t j = 0; j < m_g.size(); j++) {
      std::cout << m_g[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Вес остовного дерева" << std::endl;
  std::cout << GraphAlgorithms::GetSpanTreeWeight(res) << std::endl;

  return 0;
} */
