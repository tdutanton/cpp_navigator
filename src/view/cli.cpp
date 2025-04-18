#include "cli.h"

void print_string(const std::string& a_string) { std::cout << a_string; }
void new_line() { std::cout << std::endl; }

MenuPair make_menu_points() {
  MenuPair menu_pair;
  menu_pair[1] =
      std::make_pair(Menu::upload_graph_long, Menu::upload_graph_short);
  menu_pair[2] =
      std::make_pair(Menu::breadth_search_long, Menu::breadth_search_short);
  menu_pair[3] =
      std::make_pair(Menu::depth_search_long, Menu::depth_search_short);
  menu_pair[4] = std::make_pair(Menu::dijkstra_long, Menu::dijkstra_short);
  menu_pair[5] = std::make_pair(Menu::floyd_long, Menu::floyd_short);
  menu_pair[6] = std::make_pair(Menu::tree_long, Menu::tree_short);
  menu_pair[7] = std::make_pair(Menu::ants_long, Menu::ants_shorts);
  menu_pair[0] = std::make_pair(Menu::exit, Menu::exit);
  return menu_pair;
}

int get_choice(int a_max) {
  int choice;
  while (true) {
    std::cin >> choice;
    if (std::cin.fail() || choice < 0 || choice > a_max) {
      std::cin.clear();
      std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
      std::cout << "Invalid input. Please try again: ";
    } else {
      break;
    }
  }
  return choice;
}

void print_menu(MenuPair& a_menu) {
  print_string(Menu::greeting);
  new_line();
  print_string(Menu::input_welcome);
  new_line();
  for (unsigned long long i = 1; i < a_menu.size(); i++) {
    std::cout << i << " - ";
    print_string(a_menu[i].first);
    new_line();
  }
  std::cout << 0 << " - ";
  print_string(a_menu[0].first);
  new_line();
  print_string(Menu::note);
  new_line();
}

void print_short_menu(MenuPair& a_menu) {
  for (unsigned long long i = 1; i < a_menu.size(); i++) {
    std::cout << i << " - ";
    print_string(a_menu[i].second);
    new_line();
  }
  std::cout << 0 << " - ";
  print_string(a_menu[0].second);
  new_line();
  print_string(Menu::note);
  new_line();
}

void View::set_graph_from_file() {
  print_string(Menu::filename_welcome);
  std::string filename;
  std::cin >> filename;
  try {
    graph_ = Graph::LoadGraphFromFile(filename);
    filename_ = filename;
  } catch (std::invalid_argument& e) {
    std::cerr << "Unexpected error\n" << e.what() << std::endl;
    std::cerr << "Please write correct filename" << std::endl;
  }
}

void View::set_bfs() {
  if (graph_.is_valid_graph()) {
    print_string(Menu::start_vertex_welcome);
    std::cout << graph_.get_graph_size();
    new_line();
    int vertex{0};
    std::cin >> vertex;
    auto result = GraphAlgorithms::BreadthFirstSearch(graph_, vertex);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    for (const auto& i : result) {
      std::cout << i << " ";
    }
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::set_dfs() {
  if (graph_.is_valid_graph()) {
    print_string(Menu::start_vertex_welcome);
    std::cout << graph_.get_graph_size();
    new_line();
    int vertex{0};
    std::cin >> vertex;
    auto result = GraphAlgorithms::DepthFirstSearch(graph_, vertex);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    for (const auto& i : result) {
      std::cout << i << " ";
    }
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::set_dijkstra() {
  if (graph_.is_valid_graph()) {
    print_string(Menu::start_vertex_welcome);
    std::cout << graph_.get_graph_size() - 1;
    new_line();
    int vertex_1{0};
    std::cin >> vertex_1;
    print_string(Menu::start_vertex_welcome);
    std::cout << graph_.get_graph_size() - 1;
    new_line();
    int vertex_2{0};
    std::cin >> vertex_2;
    unsigned path = GraphAlgorithms::GetShortestPathBetweenVertices(
        graph_, vertex_1, vertex_2);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    std::cout << path;
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::set_floyd() {
  if (graph_.is_valid_graph()) {
    Alias::IntGrid res =
        GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    for (size_t i = 0; i < res.size(); i++) {
      for (size_t j = 0; j < res.size(); j++) {
        std::cout << res[i][j] << " ";
      }
      new_line();
    }
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::set_tree() {
  if (graph_.is_valid_graph()) {
    Alias::IntGrid res = GraphAlgorithms::GetLeastSpanningTree(graph_);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    for (size_t i = 0; i < res.size(); i++) {
      for (size_t j = 0; j < res.size(); j++) {
        std::cout << res[i][j] << " ";
      }
      new_line();
    }
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::set_ants() {
  if (graph_.is_valid_graph()) {
    TsmResult res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
    print_string(Menu::ui_line);
    print_string(Menu::result_label);
    new_line();
    std::cout << "Shortest distance: " << res.distance;
    new_line();
    std::cout << "Shortest path: ";
    for (const auto& i : res.vertices) {
      std::cout << i << " ";
    }
    new_line();
    print_string(Menu::ui_line);
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}

void View::print_current_graph_info() {
  if (graph_.is_valid_graph()) {
    std::cout << "Current graph loaded from file: " << filename_;
    new_line();
    std::cout << "Current graph size " << graph_.get_graph_size();
    new_line();
  } else
    std::cerr << "ERROR! Please upload a graph first" << std::endl;
}