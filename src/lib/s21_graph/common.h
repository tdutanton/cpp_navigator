/**
 * @file common.h
 * @brief Common aliases and serialization constants for graph operations.
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * This header defines type aliases used throughout the graph library and
 * constants for graph serialization/deserialization.
 */
#ifndef COMMON_H
#define COMMON_H

#include <climits>
#include <string>
#include <vector>

/**
 * @namespace Alias
 * @brief Contains type aliases used in the graph library.
 */
namespace Alias {
/// Type for representing distances between nodes
using distance = unsigned;
/// Type for node indices
using node_index = size_t;
/// Type for representing paths through nodes
using NodesPath = std::vector<node_index>;
/// Type for a row of integer values
using IntRow = std::vector<int>;
/// Type for a 2D grid of integer values
using IntGrid = std::vector<IntRow>;
/// Type for a row of pheromone values
using PheromoneRow = std::vector<double>;
/// Type for a 2D grid of pheromone values
using PheromoneGrid = std::vector<PheromoneRow>;
};  // namespace Alias

/**
 * @namespace Serialize
 * @brief Contains constants for graph serialization formats.
 *
 * These constants are used when reading/writing graphs to files,
 * particularly for DOT format serialization.
 */
namespace Serialize {
/// Open bracket character for serialization
static const char open_bracket = '{';
/// Closed bracket character for serialization
static const char closed_bracket = '}';
/// Tab character for formatting
static const char tab_symb = '\t';
/// Newline character for formatting
static const char new_line = '\n';
/// Semicolon character for formatting
static const char semicolon = ';';
/// Edge connector in DOT format
static const std::string double_minus = " -- ";
/// DOT file header
static const std::string start_dot_file = "graph G {\n";
/// Node shape in DOT format
static const std::string txt_shape = "\tnode[shape = circle];\n";
/// Default edge color in DOT format
static const std::string txt_edge_color = "\tedge[color = gray];\n";
/// Weight prefix in DOT format
static const std::string weight_line_part = " [weight=";
/// Label prefix in DOT format
static const std::string label_line_part = ", label=\"";
/// Line ending in DOT format
static const std::string end_line = "\"]";
};  // namespace Serialize

#endif