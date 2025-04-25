/**
 * @file fileReader.cpp
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * @brief Handles file operations for graph data reading and parsing.
 */

#include "filereader.h"

bool FileReader::open_file() {
  file_.open(filename_);
  if (!file_) {
    valid_file_ = false;
    return false;
  }
  return true;
}

void FileReader::close_file() {
  if (file_.is_open()) {
    file_.close();
  }
}

size_t FileReader::process_graph_size(const std::string& a_line) {
  std::istringstream iss(a_line);
  size_t result{0};
  if (valid_file_) {
    if (!(iss >> result)) valid_file_ = false;
    std::string remaining;
    std::getline(iss, remaining);
    if (!remaining.empty() && remaining.back() == '\r') remaining.pop_back();
    if (!remaining.empty() &&
        remaining.find_first_not_of(" \t") != std::string::npos)
      valid_file_ = false;
    if (result <= 1) valid_file_ = false;
  }
  return result;
}

Alias::IntRow FileReader::process_graph_line(const std::string& a_line) {
  Alias::IntRow result;
  if (valid_file_) {
    std::istringstream iss(a_line);
    int weight;
    char next_symbol;
    size_t n_count{0};
    while (iss >> weight && valid_file_) {
      result.push_back(weight);
      n_count++;
      if (iss.get(next_symbol)) {
        if (!std::isspace(static_cast<unsigned char>(next_symbol)))
          valid_file_ = false;
      }
    }
    if (n_count != size_parsed_) valid_file_ = false;
  }
  return result;
}

Alias::IntGrid FileReader::process_graph_grid() {
  Alias::IntGrid result;
  if (valid_file_) {
    open_file();
    std::string i_current_line;
    getline(file_, i_current_line);
    size_t n_count{0};
    while (std::getline(file_, i_current_line) && valid_file_) {
      Alias::IntRow i_one_graph_line = process_graph_line(i_current_line);
      result.push_back(i_one_graph_line);
      n_count++;
    }
    if (n_count != size_parsed_) valid_file_ = false;
    close_file();
  }
  return result;
}

bool FileReader::set_parsed_graph_size(const std::string& a_filename) {
  set_file(a_filename);
  if (valid_file_ && open_file()) {
    std::string first_line;
    if (std::getline(file_, first_line) && valid_file_)
      size_parsed_ = process_graph_size(first_line);
    close_file();
    return (size_parsed_ > 1 ? true : false);
  }
  return false;
}
