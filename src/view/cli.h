#ifndef CLI_H
#define CLI_H

#include <functional>
#include <iostream>
#include <map>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../lib/s21_graph/s21_graph.h"
#include "../lib/s21_graph_algorithms/s21_graph_algorithms.h"

namespace Color {
static const std::string red = "\033[31m";
static const std::string green = "\033[32m";
static const std::string blue = "\033[34m";
static const std::string orange = "\033[38;2;255;165;0m";
static const std::string color_end = "\033[0m";
};  // namespace Color

namespace Style {
static const std::string dim = "\033[2m";
static const std::string italics = "\033[3m";
};  // namespace Style

namespace Menu {
static const std::string greeting = "====  Graph Algorithms ====";
static const std::string input_welcome = "==== Enter your choice ====";

static const std::string upload_graph_long =
    "Load graph from file with adjacency matrix (make shure You have a good "
    "file)";
static const std::string breadth_search_long =
    "Breadth First Search (BFS) from any vertex - returns array of vertices. "
    "Input - vertex";
static const std::string depth_search_long =
    "Depth First Search (DFS) from any vertex - returns array of vertices. "
    "Input - vertex";
static const std::string dijkstra_long =
    "Find shortest path between two vertices. Input - start and stop vertices. "
    "Returns the shortest path";
static const std::string floyd_long =
    "Find shortest paths between all vertices. Returns the matrix of shortest "
    "paths";
static const std::string tree_long =
    "Find minimal spanning tree. Returns the adjacency matrix for minimal "
    "spanning tree";
static const std::string ants_long =
    "Solution of the traveling salesman problem. Returns the "
    "resulting route and its length";
static const std::string dot_long = "Export graph to .dot file";

static const std::string exit = "Exit";
static const std::string note = "Numeration of vertices from 1";
static const std::string filename_welcome =
    "Enter filename (with path if it's in other folder) to file with adjacency "
    "matrix: ";
static const std::string start_vertex_welcome =
    "Enter number of vertex - from 1 to ";
static const std::string result_label = "Result: ";
static const std::string ui_line = "===========================\n";

inline static void print_error_bad_graph() {
  std::cerr << Color::red << "ERROR! Please upload a graph first"
            << Color::color_end << std::endl;
}
inline static void print_error_invalid_vertex(std::invalid_argument& e) {
  std::cerr << Color::red << "Unexpected error\n" << e.what() << std::endl;
  std::cerr << "Please write correct vertex value" << Color::color_end
            << std::endl;
}
inline static void print_error_invalid_graph(std::invalid_argument& e) {
  std::cerr << Color::red << "Unexpected error\n" << e.what() << std::endl;
  std::cerr << "Graph error" << Color::color_end << std::endl;
}

};  // namespace Menu

enum class USER_INPUT {
  EXIT,
  LOAD,
  BFS,
  DFS,
  DIJKSTRA,
  FLOYD,
  TREE,
  ANTS,
  DOT,
  NONE
};

using MenuPair = std::map<unsigned, std::string>;
using ActionsMap = std::map<USER_INPUT, std::function<void()>>;

class View {
 public:
  View() : graph_{0}, filename_{} {}
  View(Graph& a_graph, std::string& a_filename)
      : graph_{a_graph}, filename_{a_filename} {}
  ~View() = default;

  void print_current_graph_info();
  void set_graph_from_file();
  void set_dijkstra();
  void set_ants();
  void set_dbfs(
      std::function<Alias::NodesPath(const Graph&, const int)> a_func);
  void set_floyd_or_tree(std::function<Alias::IntGrid(const Graph&)> a_func);
  void set_upload_dot_file();

  bool is_graph_loaded() const { return graph_.is_valid_graph(); }

#ifdef TEST
 public:
#else
 private:
#endif  // TEST
  Graph graph_;
  std::string filename_;
};

MenuPair make_menu_points();
ActionsMap actions(View& a_view);

int get_choice(int a_max);

void print_string(const std::string& a_string);
void new_line();
void print_menu(MenuPair& a_menu);
void print_empty_graph_menu(MenuPair& a_menu);

inline void clear_console() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif  // _WIN32
}

#endif  // CLI_H