#include "filereader.h"

bool FileReader::open_file() {
  file_.open(filename_);
  if (!file_) {
    correct_file_ = false;
    throw std::runtime_error("Cannot open file: " + filename_);
  }
  return true;
}

void FileReader::close_file() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool FileReader::read_successfull() { return correct_file_; }