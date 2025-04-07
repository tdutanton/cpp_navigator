#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
 public:
  FileReader() = default;
  ~FileReader() = default;

  void set_file(std::string filename) { filename_ = filename; };
  bool open_file();
  void close_file();
  bool read_successfull();

#ifdef TEST
 public:
#else
 private:
#endif
  std::string filename_;      ///< The name of the file to read.
  std::ifstream file_;        ///< File stream for reading.
  bool correct_file_ = true;  ///< Flag indicating whether the file is valid.
};

#endif