#include "../s21_graph_tests.h"

class GraphTest : public ::testing::Test {
 protected:
  void SetUp() override { createTestFiles(); }

  void TearDown() override { removeTestFiles(); }

  void createTestFiles() {
    std::ofstream goodFile("good_graph.txt");
    goodFile << "3\n";
    goodFile << "0 1 2\n";
    goodFile << "1 0 3\n";
    goodFile << "2 3 0\n";
    goodFile.close();

    std::ofstream badFile("bad_graph.txt");
    badFile << "0\n";
    badFile << "0\n";
    badFile.close();

    std::ofstream invalidFile("invalid_graph.txt");
    invalidFile << "2\n";
    invalidFile << "0 a\n";
    invalidFile << "1 0\n";
    invalidFile.close();

    std::filesystem::remove("nonexistent_file.txt");
  }

  void removeTestFiles() {
    std::vector<std::string> files = {"good_graph.txt", "bad_graph.txt",
                                      "invalid_graph.txt", "test_output.dot",
                                      "nonexistent_file.txt"};

    for (const auto& file : files) {
      if (std::filesystem::exists(file)) {
        std::filesystem::remove(file);
      }
    }
  }
};

TEST_F(GraphTest, LoadGraphFromFileSuccess) {
  Graph graph = Graph::LoadGraphFromFile("good_graph.txt");

  EXPECT_EQ(graph.get_graph_size(), 3);
  EXPECT_TRUE(graph.is_valid_graph());

  const auto& matrix = graph.get_graph_matrix();
  EXPECT_EQ(matrix[0], std::vector<int>({0, 1, 2}));
  EXPECT_EQ(matrix[1], std::vector<int>({1, 0, 3}));
  EXPECT_EQ(matrix[2], std::vector<int>({2, 3, 0}));
}

TEST_F(GraphTest, LoadGraphFromFileFailureInvalidFile) {
  EXPECT_THROW(Graph::LoadGraphFromFile("nonexistent_file.txt"),
               std::invalid_argument);
}

TEST_F(GraphTest, LoadGraphFromFileFailureBadSize) {
  EXPECT_THROW(Graph::LoadGraphFromFile("bad_graph.txt"),
               std::invalid_argument);
}

TEST_F(GraphTest, LoadGraphFromFileFailureInvalidData) {
  EXPECT_THROW(Graph::LoadGraphFromFile("invalid_graph.txt"),
               std::invalid_argument);
}

TEST_F(GraphTest, ExportGraphToDotSuccess) {
  Graph graph = Graph::LoadGraphFromFile("good_graph.txt");
  graph.ExportGraphToDot("test_output.dot");

  std::ifstream dotFile("test_output.dot");
  ASSERT_TRUE(dotFile.is_open());

  std::stringstream buffer;
  buffer << dotFile.rdbuf();
  std::string content = buffer.str();
  dotFile.close();
  std::cout << "Generated DOT file content:\n" << content << std::endl;

  EXPECT_TRUE(content.find("graph") != std::string::npos);
  EXPECT_TRUE(content.find("node") != std::string::npos);
  EXPECT_TRUE(content.find("edge") != std::string::npos);
  EXPECT_TRUE(content.find("1;") != std::string::npos);
  EXPECT_TRUE(content.find("2;") != std::string::npos);
  EXPECT_TRUE(content.find("3;") != std::string::npos);
  EXPECT_TRUE(content.find("1 --") != std::string::npos);
  EXPECT_TRUE(content.find("2 --") != std::string::npos);
  EXPECT_TRUE(content.find("}") != std::string::npos);
}

TEST_F(GraphTest, ExportGraphToDotFailure) {
  Graph graph(2);
  EXPECT_THROW(graph.ExportGraphToDot("/invalid/path/test_output.dot"),
               std::invalid_argument);
}

TEST_F(GraphTest, OperatorBrackets) {
  Graph graph = Graph::LoadGraphFromFile("good_graph.txt");

  graph[0][1] = 5;
  EXPECT_EQ(graph[0][1], 5);

  const Graph& constGraph = graph;
  EXPECT_EQ(constGraph[1][2], 3);
}

TEST_F(GraphTest, OperatorOutputStream) {
  Graph graph = Graph::LoadGraphFromFile("good_graph.txt");

  std::stringstream ss;
  ss << graph;

  std::string expected = "0 1 2 \n1 0 3 \n2 3 0 \n";
  EXPECT_EQ(ss.str(), expected);
}

TEST_F(GraphTest, ExportConfigTxt) {
  Graph graph(2);
  std::ofstream out("test_config.txt");
  ASSERT_TRUE(out.is_open());

  graph.export_config_txt(out);
  out.close();

  std::ifstream in("test_config.txt");
  std::stringstream ss;
  ss << in.rdbuf();

  std::string expected =
      "graph G {\n\tnode[shape = circle];\n\tedge[color = gray];\n";
  EXPECT_EQ(ss.str(), expected);
  std::filesystem::remove("test_config.txt");
}

TEST_F(GraphTest, ExportNodeLineTxt) {
  Graph graph(2);
  graph[0][1] = 5;
  std::ofstream out("test_node_line.txt");
  ASSERT_TRUE(out.is_open());
  unsigned nodeNumber = 1;

  graph.export_node_line_txt(out, nodeNumber, 0, 1);
  out.close();

  std::ifstream in("test_node_line.txt");
  std::stringstream ss;
  ss << in.rdbuf();

  std::string expected = " -- 2 [weight=5, label=\"5\"];";
  EXPECT_EQ(ss.str(), expected);
  std::filesystem::remove("test_node_line.txt");
}

TEST_F(GraphTest, DefaultConstructorAndGetters) {
  Graph graph(4);

  EXPECT_EQ(graph.get_graph_size(), 4);
  EXPECT_FALSE(graph.is_valid_graph());

  const auto& matrix = graph.get_graph_matrix();
  EXPECT_EQ(matrix.size(), 4);
  EXPECT_EQ(matrix[0].size(), 4);
  EXPECT_EQ(matrix[0][0], 0);
}

TEST(GraphConstructorTest, DefaultSizeZero) {
  Graph graph(0);

  EXPECT_EQ(graph.get_graph_size(), 0);
  EXPECT_FALSE(graph.is_valid_graph());
}

TEST(GraphConstructorTest, PositiveSize) {
  const size_t size = 5;
  Graph graph(size);

  EXPECT_EQ(graph.get_graph_size(), size);
  EXPECT_FALSE(graph.is_valid_graph());
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      EXPECT_EQ(graph[i][j], 0);
    }
  }
}

TEST(GraphConstructorTest, LargeSize) {
  const size_t large_size = 1000;
  Graph graph(large_size);

  EXPECT_EQ(graph.get_graph_size(), large_size);
  EXPECT_FALSE(graph.is_valid_graph());
}

TEST(GraphAccessorTest, ConstOperatorBracket) {
  const size_t size = 3;
  Graph graph(size);

  graph[0][0] = 1;
  graph[0][1] = 2;
  graph[0][2] = 3;
  graph[1][0] = 4;
  graph[1][1] = 5;
  graph[1][2] = 6;
  graph[2][0] = 7;
  graph[2][1] = 8;
  graph[2][2] = 9;

  EXPECT_EQ(graph[0][0], 1);
  EXPECT_EQ(graph[0][1], 2);
  EXPECT_EQ(graph[0][2], 3);
  EXPECT_EQ(graph[1][0], 4);
  EXPECT_EQ(graph[1][1], 5);
  EXPECT_EQ(graph[1][2], 6);
  EXPECT_EQ(graph[2][0], 7);
  EXPECT_EQ(graph[2][1], 8);
  EXPECT_EQ(graph[2][2], 9);
}

TEST(GraphAccessorTest, GetGraphSize) {
  const size_t size = 10;
  Graph graph(size);

  EXPECT_EQ(graph.get_graph_size(), size);
}

TEST(GraphEdgeCaseTest, OutOfBoundsAccess) {
  const size_t size = 2;
  Graph graph(size);

  EXPECT_NO_THROW(graph[0][0]);
  EXPECT_NO_THROW(graph[1][1]);
}

TEST(GraphCoverageTest, DestructorCoverage) {
  auto* g = new Graph(2);
  delete g;
}