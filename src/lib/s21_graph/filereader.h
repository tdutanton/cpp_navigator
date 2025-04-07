#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <sstream>
#include <string>

#include "common.h"

class FileReader {
 public:
  FileReader() = default;
  ~FileReader() = default;

  void set_file(std::string filename) { filename_ = filename; };
  bool open_file();
  bool is_valid_file() const { return valid_file_; }
  void close_file();
  size_t process_graph_size(const std::string& line);
  Alias::IntRow process_graph_line(const std::string& line);

#ifdef TEST
 public:
#else
 private:
#endif
  std::string filename_;    ///< The name of the file to read.
  std::ifstream file_;      ///< File stream for reading.
  bool valid_file_ = true;  ///< Flag indicating whether the file is valid.
};

#endif