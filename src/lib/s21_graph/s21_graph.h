#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <string>

class Graph {
 public:
  Graph LoadGraphFromFile(std::string filename);
  // void File ExportGraphToDot(std::string filename);
};

#endif