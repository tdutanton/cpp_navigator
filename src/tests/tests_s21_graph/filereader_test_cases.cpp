#include "s21_graph_tests.h"

/* TEST(FileReaderTest, ProcessGraphSize_ValidInput) {
  FileReader reader;
  std::string validLine = "42\n";  // Корректный ввод
  EXPECT_NO_THROW(reader.process_graph_size(validLine));
  EXPECT_EQ(reader.process_graph_size(validLine), 42);
} */

TEST(FileReaderTest, ProcessGraphSize_InvalidInput_NotANumber) {
  FileReader reader;
  std::string invalidLine = "not_a_number\n";  // Не число
  EXPECT_THROW(reader.process_graph_size(invalidLine), std::invalid_argument);
}
/*
TEST(FileReaderTest, ProcessGraphSize_InvalidInput_ExtraCharacters) {
  FileReader reader;
  std::string invalidLine = "42 abc\n";  // Число + мусор
  EXPECT_THROW(reader.process_graph_size(invalidLine), std::invalid_argument);
}

TEST(FileReaderTest, ProcessGraphSize_InvalidInput_WhitespaceOnly) {
  FileReader reader;
  std::string invalidLine = "42   \n";  // Число + пробелы (допустимо?)
  // Если пробелы допускаются, тест должен проходить
  // Если нет — должен кидать исключение
  // В данном случае функция кидает исключение, так что:
  EXPECT_THROW(reader.process_graph_size(invalidLine), std::invalid_argument);
}

TEST(FileReaderTest, ProcessGraphSize_EmptyInput) {
  FileReader reader;
  std::string emptyLine = "";
  EXPECT_THROW(reader.process_graph_size(emptyLine), std::invalid_argument);
} */