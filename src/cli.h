#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <map>
#include <string>

#include "lib/s21_graph/s21_graph.h"
#include "lib/s21_graph_algorithms/s21_graph_algorithms.h"

using MenuPair = std::map<unsigned, std::pair<std::string, std::string>>;

namespace Menu {
static const std::string greeting = "====  Graph Algorithms ====";
static const std::string input_welcome = "==== Enter your choice ====";

static const std::string upload_graph_long =
    "Load graph from file with adjacency matrix (make shure You have a good "
    "file)";
static const std::string upload_graph_short = "Upload graph";

static const std::string breadth_search_long =
    "Breadth First Search (BFS) from any vertex - returns array of vertices. "
    "Input vertex";
static const std::string breadth_search_short = "BFS";

static const std::string depth_search_long =
    "Depth First Search (DFS) from any vertex - returns array of vertices. "
    "Input vertex";
static const std::string depth_search_short = "DFS";

static const std::string dijkstra_long =
    "Find shortest path between two vertices. Enter start and stop with space "
    "between. Returns the value of the shortest path";
static const std::string dijkstra_short = "Shortest path (enter \"start end\")";

static const std::string floyd_long =
    "Find shortest paths between all vertices. Returns the matrix of shortest "
    "paths";
static const std::string floyd_short = "Matrix of shortest paths";

static const std::string tree_long =
    "Find minimal spanning tree. Returns the adjacency matrix for minimal "
    "spanning tree";
static const std::string tree_short = "Minimal spanning tree";

static const std::string ants_long =
    "Solution of the traveling salesman problem. Returns the output of the "
    "resulting route and its length in the console";
static const std::string ants_shorts = "Traveling salesman problem";

static const std::string exit = "Exit";
static const std::string note = "**Numeration of vertices from 1**";
static const std::string filename_welcome =
    "Enter file path to file with adjacency matrix: ";
static const std::string start_vertex_welcome =
    "Enter number of vertex - from 1 to ";
static const std::string result_label = "Result: ";
static const std::string ui_line = "===========================\n";
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
  NONE
};

void print_string(const std::string& a_string);
void new_line();

MenuPair make_menu_points();

void print_menu(MenuPair& a_menu);
void print_short_menu(MenuPair& a_menu);

void set_graph_from_file(Graph& a_graph, int& a_size);
void set_bfs(const Graph& a_graph, const int a_size);
void set_dfs(const Graph& a_graph, const int a_size);
void set_dijkstra(const Graph& a_graph, const int a_size);
void set_floyd(const Graph& a_graph);
void set_tree(const Graph& a_graph);

#endif