/**
 * @file cli.h
 * @brief Command Line Interface for Graph Algorithms
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * Provides a user interface to interact with graph algorithms including:
 * - Graph loading and visualization
 * - BFS/DFS traversals
 * - Shortest path algorithms (Dijkstra, Floyd-Warshall)
 * - Minimum Spanning Tree
 * - Traveling Salesman Problem solution
 */

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

/**
 * @namespace Color
 * @brief ANSI color codes for terminal output
 */
namespace Color {
static const std::string red = "\033[31m";    ///< Red color code
static const std::string green = "\033[32m";  ///< Green color code
static const std::string blue = "\033[34m";   ///< Blue color code
static const std::string orange =
    "\033[38;2;255;165;0m";                      ///< Orange color code
static const std::string color_end = "\033[0m";  ///< Reset color code
};                                               // namespace Color

/**
 * @namespace Style
 * @brief ANSI text style codes
 */
namespace Style {
static const std::string dim = "\033[2m";      ///< Dim text style
static const std::string italics = "\033[3m";  ///< Italic text style
};                                             // namespace Style

/**
 * @namespace Menu
 * @brief Contains all menu strings and UI utilities
 */
namespace Menu {
static const std::string greeting =
    "====  Graph Algorithms ====";  ///< Welcome message
static const std::string input_welcome =
    "==== Enter your choice ====";  ///< Prompt message

// Menu item descriptions
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

static const std::string exit = "Exit";  ///< Exit option text
static const std::string note =
    "Numeration of vertices from 1";  ///< Vertex numbering note
static const std::string filename_welcome =
    "Enter filename (with path if it's in other folder) to file with adjacency "
    "matrix: ";  ///< File prompt
static const std::string start_vertex_welcome =
    "Enter number of vertex - from 1 to ";           ///< Vertex prompt
static const std::string result_label = "Result: ";  ///< Result prefix
static const std::string ui_line =
    "===========================\n";  ///< UI separator

/**
 * @brief Prints error when no graph is loaded
 */
inline static void print_error_bad_graph() {
  std::cerr << Color::red << "ERROR! Please upload a graph first"
            << Color::color_end << std::endl;
}

/**
 * @brief Prints vertex-related error
 * @param e Exception containing error details
 */
inline static void print_error_invalid_vertex(std::invalid_argument& e) {
  std::cerr << Color::red << "Unexpected error\n" << e.what() << std::endl;
  std::cerr << "Please write correct vertex value" << Color::color_end
            << std::endl;
}

/**
 * @brief Prints graph-related error
 * @param e Exception containing error details
 */
inline static void print_error_invalid_graph(std::invalid_argument& e) {
  std::cerr << Color::red << "Unexpected error\n" << e.what() << std::endl;
  std::cerr << "Graph error" << Color::color_end << std::endl;
}

};  // namespace Menu

/**
 * @enum USER_INPUT
 * @brief Represents possible user menu selections
 */
enum class USER_INPUT {
  EXIT,      ///< Exit the application
  LOAD,      ///< Load a graph
  BFS,       ///< Breadth-first search
  DFS,       ///< Depth-first search
  DIJKSTRA,  ///< Dijkstra's algorithm
  FLOYD,     ///< Floyd-Warshall algorithm
  TREE,      ///< Minimum spanning tree
  ANTS,      ///< Traveling salesman problem
  DOT,       ///< Export to DOT format
  NONE       ///< No valid selection
};

using MenuPair = std::map<unsigned, std::string>;  ///< Menu option mapping
using ActionsMap =
    std::map<USER_INPUT, std::function<void()>>;  ///< Action mapping

/**
 * @class View
 * @brief Handles all user interface operations
 */
class View {
 public:
  /**
   * @brief Default constructor
   */
  View() : graph_{0}, filename_{} {}

  /**
   * @brief Constructor with graph and filename
   * @param a_graph Graph object
   * @param a_filename Name of graph file
   */
  View(Graph& a_graph, std::string& a_filename)
      : graph_{a_graph}, filename_{a_filename} {}

  ~View() = default;

  /**
   * @brief Prints current graph information
   */
  void print_current_graph_info();

  /**
   * @brief Loads graph from file
   */
  void set_graph_from_file();

  /**
   * @brief Runs Dijkstra's algorithm
   */
  void set_dijkstra();

  /**
   * @brief Solves TSP using Ant Colony Optimization
   */
  void set_ants();

  /**
   * @brief Runs BFS or DFS algorithm
   * @param a_func Traversal function to use
   */
  void set_dbfs(
      std::function<Alias::NodesPath(const Graph&, const int)> a_func);

  /**
   * @brief Runs Floyd-Warshall or MST algorithm
   * @param a_func Algorithm function to use
   */
  void set_floyd_or_tree(std::function<Alias::IntGrid(const Graph&)> a_func);

  /**
   * @brief Exports graph to DOT format
   */
  void set_upload_dot_file();

  /**
   * @brief Checks if graph is loaded
   * @return true if graph is valid, false otherwise
   */
  bool is_graph_loaded() const { return graph_.is_valid_graph(); }

#ifdef TEST
 public:
#else
 private:
#endif                    // TEST
  Graph graph_;           ///< Current graph instance
  std::string filename_;  ///< Current graph filename
};

/**
 * @brief Creates menu options mapping
 * @return MenuPair with numbered options
 */
MenuPair make_menu_points();

/**
 * @brief Creates action mappings for menu options
 * @param a_view View instance to bind actions to
 * @return ActionsMap with function bindings
 */
ActionsMap actions(View& a_view);

/**
 * @brief Gets user menu selection
 * @param a_max Maximum valid choice
 * @return Selected menu option
 */
int get_choice(int a_max);

/**
 * @brief Prints a string to console
 * @param a_string String to print
 */
void print_string(const std::string& a_string);

/**
 * @brief Prints a newline
 */
void new_line();

/**
 * @brief Prints full menu
 * @param a_menu Menu options to display
 */
void print_menu(MenuPair& a_menu);

/**
 * @brief Prints menu without graph-dependent options
 * @param a_menu Menu options to display
 */
void print_empty_graph_menu(MenuPair& a_menu);

/**
 * @brief Clears console screen
 */
inline void clear_console() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif  // _WIN32
}

#endif  // CLI_H