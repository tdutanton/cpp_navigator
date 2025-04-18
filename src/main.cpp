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
    ActionsMap result_actions = actions(view);
    if (result_actions.find(input) != result_actions.end()) {
      clear_console();
      result_actions[input]();
    }
  }
  return 0;
}