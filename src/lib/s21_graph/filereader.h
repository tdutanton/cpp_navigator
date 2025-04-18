#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "common.h"

class FileReader {
 public:
  FileReader() = default;
  ~FileReader() = default;

  void set_file(const std::string& a_filename) { filename_ = a_filename; };
  bool open_file();
  bool is_valid_file() const { return valid_file_; }
  void close_file();
  size_t process_graph_size(const std::string& a_line);
  Alias::IntRow process_graph_line(const std::string& a_line);
  Alias::IntGrid process_graph_grid();

  bool set_parsed_graph_size(const std::string& a_filename);

  size_t get_parsed_size() const { return size_parsed_; }

#ifdef TEST
 public:
#else
 private:
#endif                    // TEST
  std::string filename_;  ///< The name of the file to read.
  std::ifstream file_;    ///< File stream for reading.
  size_t size_parsed_;  ///< Graph size (number parsed from file's first line).
  bool valid_file_ = true;  ///< Flag indicating whether the file is valid.
};

#endif