#include "view/cli.h"

int main() {
  clear_console();
  MenuPair menu_labels = make_menu_points();
  int choice = -1;
  View view;
  while (choice != static_cast<int>(USER_INPUT::EXIT)) {
    print_menu(menu_labels);
    choice = get_choice(static_cast<int>(USER_INPUT::ANTS));
    USER_INPUT input = static_cast<USER_INPUT>(choice);
    switch (input) {
      case USER_INPUT::LOAD: {
        clear_console();
        view.set_graph_from_file();
        break;
      }
      case USER_INPUT::BFS: {
        clear_console();
        view.print_current_graph_info();
        view.set_bfs();
        break;
      }
      case USER_INPUT::DFS: {
        clear_console();
        view.print_current_graph_info();
        view.set_dfs();
        break;
      }
      case USER_INPUT::DIJKSTRA: {
        clear_console();
        view.print_current_graph_info();
        view.set_dijkstra();
        break;
      }
      case USER_INPUT::FLOYD: {
        clear_console();
        view.print_current_graph_info();
        view.set_floyd();
        break;
      }
      case USER_INPUT::TREE: {
        clear_console();
        view.print_current_graph_info();
        view.set_tree();
        break;
      }
      case USER_INPUT::ANTS: {
        clear_console();
        view.print_current_graph_info();
        view.set_ants();
        break;
      }
      default:
        break;
    }
  }
  return 0;
}
