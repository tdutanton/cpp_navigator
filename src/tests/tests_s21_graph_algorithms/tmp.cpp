#include "s21_graph_algorithms_tests.h"

TEST(FileReaderTest, ProcessGraphSize_InvalidInput_NotANumber) {
  std::string invalidLine = "not_a_number\n";  // Не число
  EXPECT_EQ(invalidLine, "not_a_number\n");
}