/**
 * @file fileReader.h
 * @author montoyay (https://t.me/tdutanton)
 * @author buggkell (https://t.me/a_a_sorokina)
 * @brief Handles file operations for graph data reading and parsing.
 */
#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "common.h"

/**
 * @class FileReader
 * @brief Provides functionality to read and parse graph data from files.
 *
 * This class handles file operations including opening/closing files,
 * validating file contents, and parsing graph data into appropriate structures.
 */
class FileReader {
 public:
  FileReader() = default;   /// Default constructor
  ~FileReader() = default;  /// Default destructor

  /**
   * @brief Sets the filename to be processed.
   * @param[in] a_filename The name of the file containing graph data.
   */
  void set_file(const std::string& a_filename) { filename_ = a_filename; };

  /**
   * @brief Opens the specified file for reading.
   * @return True if the file was successfully opened, false otherwise.
   */
  bool open_file();

  /**
   * @brief Checks if the current file is valid.
   * @return True if the file is valid and ready for reading, false otherwise.
   */
  bool is_valid_file() const { return valid_file_; }

  /**
   * @brief Closes the currently opened file.
   */
  void close_file();

  /**
   * @brief Parses the graph size from a line of text.
   * @param[in] a_line The input line containing the graph size.
   * @return The parsed graph size (number of vertices).
   */
  size_t process_graph_size(const std::string& a_line);

  /**
   * @brief Parses a single line of graph adjacency data.
   * @param[in] a_line The input line containing adjacency row data.
   * @return A row of integers representing the adjacency matrix row.
   */
  Alias::IntRow process_graph_line(const std::string& a_line);

  /**
   * @brief Parses the complete graph adjacency matrix from the file.
   * @return A 2D grid of integers representing the complete adjacency matrix.
   */
  Alias::IntGrid process_graph_grid();

  /**
   * @brief Parses and sets the graph size from a file.
   * @param[in] a_filename The name of the file to read.
   * @return True if the size was successfully parsed, false otherwise.
   */
  bool set_parsed_graph_size(const std::string& a_filename);

  /**
   * @brief Gets the parsed graph size.
   * @return The number of vertices in the graph as parsed from the file.
   */
  size_t get_parsed_size() const { return size_parsed_; }

#ifdef TEST
 public:
#else
 private:
#endif  // TEST
  /// The name of the file to read.
  std::string filename_;
  /// File stream for reading operations.
  std::ifstream file_;
  /// Graph size (number of vertices) parsed from file.
  size_t size_parsed_;
  /// Flag indicating file validity and readiness for operations.
  bool valid_file_ = true;
};

#endif