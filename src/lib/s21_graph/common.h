#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

namespace Alias {
using IntRow = std::vector<int>;
using IntGrid = std::vector<IntRow>;
};  // namespace Alias

namespace Serialize {
static const char open_bracket = '{';
static const char closed_bracket = '}';
static const char tab_symb = '\t';
static const char new_line = '\n';
static const char semicolon = ';';
static const std::string double_minus = " -- ";
static const std::string start_dot_file = "graph G {\n";
static const std::string txt_shape = "\tnode[shape = circle];\n";
static const std::string txt_edge_color = "\tedge[color = gray];\n";
static const std::string weight_line_part = " [weight=";
static const std::string label_line_part = ", label=\"";
static const std::string end_line = "\"]";
};  // namespace Serialize

#endif