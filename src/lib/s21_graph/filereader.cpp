#include "filereader.h"

bool FileReader::open_file() {
  file_.open(filename_);
  if (!file_) {
    valid_file_ = false;
    throw std::runtime_error("Cannot open file: " + filename_);
  }
  return true;
}

void FileReader::close_file() {
  if (file_.is_open()) {
    file_.close();
  }
}

size_t FileReader::process_graph_size(const std::string& line) {
  std::istringstream iss(line);
  size_t result;
  char next_symbol;
  if (!iss >> result) {
    valid_file_ = false;
    throw std::invalid_argument(
        "First line parsing error - it's not a number.");
  }
  if (iss.get(next_symbol)) {
    if (!iss.eof() && next_symbol != '\n') {
      valid_file_ = false;
      throw std::invalid_argument(
          "First line parsing error - there's something else after a number.");
    }
  }
  return result;
}

Alias::IntRow FileReader::process_graph_line(const std::string& line) {
  Alias::IntRow result;
  if (valid_file_) {
    std::istringstream iss(line);
    int weight;
    char next_symbol;
    while (iss >> weight && valid_file_) {
      result.push_back(weight);
      if (iss.get(next_symbol) && !std::isspace(next_symbol)) {
        valid_file_ = false;
        break;
      }
    }
  }
  return result;
}
