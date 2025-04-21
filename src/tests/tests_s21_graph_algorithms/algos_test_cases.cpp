#include "../s21_graph_tests.h"

class GraphAlgorithmsTest : public ::testing::Test {
 protected:
  GraphAlgorithmsTest() : graph1_(3), graph2_(4), graph3_(3) {
    CreateTestGraphs();
  }
  void SetUp() override { CreateTestGraphs(); }

  void CreateTestGraphs() {
    graph1_ = Graph(3);
    graph1_[0][1] = 1;

    graph2_ = Graph(4);
    graph2_[0][1] = 1;
    graph2_[1][2] = 1;
    graph2_[2][3] = 1;
    graph2_[3][0] = 1;

    graph3_ = Graph(3);
    graph3_[0][1] = 1;
    graph3_[0][2] = 1;
    graph3_[1][0] = 1;
    graph3_[1][2] = 1;
    graph3_[2][0] = 1;
    graph3_[2][1] = 1;
  }

  Graph graph1_;
  Graph graph2_;
  Graph graph3_;
};

TEST_F(GraphAlgorithmsTest, DFS_InvalidStartVertex) {
  EXPECT_THROW(GraphAlgorithms::DepthFirstSearch(graph1_, 0),
               std::invalid_argument);
  EXPECT_THROW(GraphAlgorithms::DepthFirstSearch(graph1_, 4),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, DFS_EmptyGraph) {
  Graph empty_graph(0);
  EXPECT_THROW(GraphAlgorithms::DepthFirstSearch(empty_graph, 1),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, DFS_DisconnectedGraph) {
  auto path = GraphAlgorithms::DepthFirstSearch(graph1_, 1);
  ASSERT_EQ(path.size(), 2);
  EXPECT_EQ(path[0], 1);
  EXPECT_EQ(path[1], 2);
}

TEST_F(GraphAlgorithmsTest, DFS_ConnectedGraph) {
  auto path = GraphAlgorithms::DepthFirstSearch(graph2_, 1);
  ASSERT_EQ(path.size(), 4);
  EXPECT_EQ(path[0], 1);

  EXPECT_TRUE(std::find(path.begin(), path.end(), 2) != path.end());
  EXPECT_TRUE(std::find(path.begin(), path.end(), 3) != path.end());
  EXPECT_TRUE(std::find(path.begin(), path.end(), 4) != path.end());
}

TEST_F(GraphAlgorithmsTest, DFS_FullGraph) {
  auto path = GraphAlgorithms::DepthFirstSearch(graph3_, 1);
  ASSERT_EQ(path.size(), 3);
  EXPECT_EQ(path[0], 1);

  EXPECT_TRUE(std::find(path.begin(), path.end(), 2) != path.end());
  EXPECT_TRUE(std::find(path.begin(), path.end(), 3) != path.end());
}

TEST_F(GraphAlgorithmsTest, BFS_InvalidStartVertex) {
  EXPECT_THROW(GraphAlgorithms::BreadthFirstSearch(graph1_, 0),
               std::invalid_argument);
  EXPECT_THROW(GraphAlgorithms::BreadthFirstSearch(graph1_, 4),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, BFS_EmptyGraph) {
  Graph empty_graph(0);
  EXPECT_THROW(GraphAlgorithms::BreadthFirstSearch(empty_graph, 1),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, BFS_DisconnectedGraph) {
  auto path = GraphAlgorithms::BreadthFirstSearch(graph1_, 1);
  ASSERT_EQ(path.size(), 2);
  EXPECT_EQ(path[0], 1);
  EXPECT_EQ(path[1], 2);
}

TEST_F(GraphAlgorithmsTest, BFS_FullGraph) {
  auto path = GraphAlgorithms::BreadthFirstSearch(graph3_, 1);
  ASSERT_EQ(path.size(), 3);
  EXPECT_EQ(path[0], 1);

  EXPECT_TRUE((path[1] == 2 && path[2] == 3) || (path[1] == 3 && path[2] == 2));
}

TEST_F(GraphAlgorithmsTest, TraverseGraph_StackBehavior) {
  Graph small_graph(3);
  small_graph[0][1] = 1;
  small_graph[0][2] = 1;

  auto path = GraphAlgorithms::DepthFirstSearch(small_graph, 1);
  EXPECT_EQ(path[0], 1);
  EXPECT_TRUE((path[1] == 3 && path[2] == 2) || (path[1] == 2 && path[2] == 3));
}

TEST_F(GraphAlgorithmsTest, TraverseGraph_QueueBehavior) {
  Graph small_graph(3);
  small_graph[0][1] = 1;
  small_graph[0][2] = 1;

  auto path = GraphAlgorithms::BreadthFirstSearch(small_graph, 1);

  EXPECT_EQ(path[0], 1);
  EXPECT_TRUE((path[1] == 2 && path[2] == 3) || (path[1] == 3 && path[2] == 2));
}