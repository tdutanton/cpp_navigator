
#include "../s21_graph_tests.h"

TEST(GraphAlgorithmsTest_simple, ValidConnectedGraphTest) {
  Graph graph(4);
  graph.valid_graph_ = true;

  graph[0][1] = 1;
  graph[1][0] = 1;
  graph[1][2] = 2;
  graph[2][1] = 2;
  graph[2][3] = 1;
  graph[3][2] = 1;

  graph[0][2] = 3;
  graph[2][0] = 3;
  graph[1][3] = 4;
  graph[3][1] = 4;

  graph[0][0] = 1;

  ASSERT_TRUE(graph.get_graph_size() > 0);
  ASSERT_TRUE(graph.is_valid_graph());

  EXPECT_NO_THROW({
    auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);

    EXPECT_EQ(result[0][3], 4);
  });
}

TEST(GraphAlgorithmsTest_simple, DebugGraphValidity) {
  Graph graph(4);
  graph[0][1] = 1;
  graph[1][0] = 1;
  graph[1][2] = 2;
  graph[2][1] = 2;
  graph[2][3] = 1;
  graph[3][2] = 1;

  std::cout << "Graph validity check: " << graph.is_valid_graph() << std::endl;
  std::cout << "Graph connections:\n";
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      std::cout << graph[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

TEST(GetSpanTreeTest, Test1) {
  Graph graph(5);
  graph.valid_graph_ = true;
  graph[0][1] = 1;
  graph[0][2] = 2;
  graph[1][2] = 3;
  graph[1][3] = 4;
  graph[2][3] = 5;
  graph[2][4] = 6;
  graph[3][4] = 7;

  SpanTree result = GraphAlgorithms::GetSpanTree(graph);

  EXPECT_EQ(result.tree_weight, 13);
  EXPECT_EQ(result.Tree[0][1], 1);
  EXPECT_EQ(result.Tree[0][2], 2);
  EXPECT_EQ(result.Tree[1][3], 4);
  EXPECT_EQ(result.Tree[2][4], 6);
}

TEST(GetSpanTreeTest, Test2) {
  Graph graph(4);
  graph.valid_graph_ = true;
  graph[0][1] = 1;
  graph[0][2] = 2;
  graph[1][2] = 3;
  graph[1][3] = 4;
  graph[2][3] = 5;

  SpanTree result = GraphAlgorithms::GetSpanTree(graph);

  EXPECT_EQ(result.tree_weight, 7);
  EXPECT_EQ(result.Tree[0][1], 1);
  EXPECT_EQ(result.Tree[0][2], 2);
  EXPECT_EQ(result.Tree[1][3], 4);
}

TEST(GetSpanTreeTest, Test3) {
  Graph graph(3);
  graph.valid_graph_ = true;
  graph[0][1] = 1;
  graph[0][2] = 2;
  graph[1][2] = 3;

  SpanTree result = GraphAlgorithms::GetSpanTree(graph);

  EXPECT_EQ(result.tree_weight, 3);
  EXPECT_EQ(result.Tree[0][1], 1);
  EXPECT_EQ(result.Tree[0][2], 2);
}
