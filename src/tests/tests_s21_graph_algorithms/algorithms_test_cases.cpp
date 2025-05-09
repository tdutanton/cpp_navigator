#include "../s21_graph_tests.h"

class GraphAlgorithmsTest : public ::testing::Test {
 protected:
  GraphAlgorithmsTest()
      : graph1_(3),
        graph2_(4),
        graph3_(3),
        simple_graph(3),
        disconnected_graph(3),
        weighted_graph(4),
        valid_graph1(3),
        valid_graph2(4),
        graph_with_loop(2),
        empty_graph_(0),
        no_hamiltonian_graph_(3),
        valid_graph_(3) {
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

    simple_graph = Graph(3);
    simple_graph[0][1] = 1;
    simple_graph[1][0] = 2;
    simple_graph[1][2] = 3;
    simple_graph[2][1] = 4;

    disconnected_graph = Graph(3);
    disconnected_graph[0][1] = 1;

    weighted_graph = Graph(4);
    weighted_graph[0][1] = 5;
    weighted_graph[1][0] = 5;
    weighted_graph[0][2] = 10;
    weighted_graph[2][0] = 10;
    weighted_graph[1][2] = 3;
    weighted_graph[2][1] = 3;
    weighted_graph[1][3] = 20;
    weighted_graph[3][1] = 20;
    weighted_graph[2][3] = 2;
    weighted_graph[3][2] = 2;

    valid_graph1 = Graph(3);
    valid_graph1[0][1] = 1;
    valid_graph1[1][0] = 1;
    valid_graph1[1][2] = 2;
    valid_graph1[2][1] = 2;

    valid_graph2 = Graph(4);
    valid_graph2[0][1] = 5;
    valid_graph2[1][0] = 5;
    valid_graph2[0][2] = 10;
    valid_graph2[2][0] = 10;
    valid_graph2[1][2] = 3;
    valid_graph2[2][1] = 3;
    valid_graph2[1][3] = 20;
    valid_graph2[3][1] = 20;
    valid_graph2[2][3] = 2;
    valid_graph2[3][2] = 2;

    graph_with_loop = Graph(2);
    graph_with_loop[0][1] = 1;
    graph_with_loop[1][0] = 1;

    empty_graph_ = Graph(0);

    no_hamiltonian_graph_ = Graph(3);
    no_hamiltonian_graph_[0][1] = 1;
    no_hamiltonian_graph_[1][0] = 1;
    no_hamiltonian_graph_[1][2] = 1;
    no_hamiltonian_graph_[2][1] = 1;

    valid_graph_ = Graph(3);
    valid_graph_[0][1] = 1;
    valid_graph_[1][0] = 1;
    valid_graph_[0][2] = 1;
    valid_graph_[2][0] = 1;
    valid_graph_[1][2] = 1;
    valid_graph_[2][1] = 1;
  }

  Graph graph1_;
  Graph graph2_;
  Graph graph3_;
  Graph simple_graph;
  Graph disconnected_graph;
  Graph weighted_graph;
  Graph valid_graph1;
  Graph valid_graph2;
  Graph graph_with_loop;

  Graph empty_graph_;
  Graph no_hamiltonian_graph_;
  Graph valid_graph_;
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

TEST_F(GraphAlgorithmsTest, TraverseGraph_StackBehavior) {
  Graph small_graph(3);
  small_graph[0][1] = 1;
  small_graph[0][2] = 1;
  small_graph[1][0] = 1;
  small_graph[2][0] = 1;

  auto path = GraphAlgorithms::DepthFirstSearch(small_graph, 1);
  EXPECT_EQ(path[0], 1);
  EXPECT_TRUE((path[1] == 3 && path[2] == 2) || (path[1] == 2 && path[2] == 3));
}

TEST_F(GraphAlgorithmsTest, TraverseGraph_QueueBehavior) {
  Graph small_graph(3);
  small_graph[0][1] = 1;
  small_graph[0][2] = 1;
  small_graph[1][0] = 1;
  small_graph[1][2] = 1;
  small_graph[2][0] = 1;
  small_graph[2][1] = 1;

  auto path = GraphAlgorithms::BreadthFirstSearch(small_graph, 1);

  EXPECT_EQ(path[0], 1);
  EXPECT_TRUE((path[0] == 1 && path[1] == 2));
}

TEST_F(GraphAlgorithmsTest, GetShortPath_InvalidStartIndex) {
  auto result1 = GraphAlgorithms::GetShortPath(simple_graph, -1);
  EXPECT_TRUE(result1.distances.empty());
  EXPECT_TRUE(result1.prev_nodes.empty());

  auto result2 = GraphAlgorithms::GetShortPath(simple_graph, 10);
  EXPECT_TRUE(result2.distances.empty());
  EXPECT_TRUE(result2.prev_nodes.empty());
}

TEST_F(GraphAlgorithmsTest, GetShortPath_ValidGraph) {
  auto result = GraphAlgorithms::GetShortPath(simple_graph, 0);

  EXPECT_EQ(result.distances.size(), 3);
  EXPECT_EQ(result.prev_nodes.size(), 3);

  EXPECT_EQ(result.distances[0], 0);
  EXPECT_EQ(result.distances[1], 1);
  EXPECT_EQ(result.distances[2], 4);

  EXPECT_EQ(result.prev_nodes[0], -1);
  EXPECT_EQ(result.prev_nodes[1], 0);
  EXPECT_EQ(result.prev_nodes[2], 1);
}

TEST_F(GraphAlgorithmsTest, GetShortPath_DisconnectedGraph) {
  auto result = GraphAlgorithms::GetShortPath(disconnected_graph, 0);

  EXPECT_EQ(result.distances[0], 0);
  EXPECT_EQ(result.distances[1], 1);
  EXPECT_EQ(result.distances[2], UINT_MAX);

  EXPECT_EQ(result.prev_nodes[0], -1);
  EXPECT_EQ(result.prev_nodes[1], 0);
  EXPECT_EQ(result.prev_nodes[2], -1);
}

TEST_F(GraphAlgorithmsTest, GetShortestPathBetweenVertices_InvalidVertices) {
  EXPECT_THROW(
      GraphAlgorithms::GetShortestPathBetweenVertices(simple_graph, 0, 1),
      std::invalid_argument);
  EXPECT_THROW(
      GraphAlgorithms::GetShortestPathBetweenVertices(simple_graph, 1, 0),
      std::invalid_argument);
  EXPECT_THROW(
      GraphAlgorithms::GetShortestPathBetweenVertices(simple_graph, 1, 10),
      std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, GetShortestPathBetweenVertices_ValidPath) {
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(simple_graph, 1, 2),
            1);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(simple_graph, 1, 3),
            4);
  EXPECT_EQ(
      GraphAlgorithms::GetShortestPathBetweenVertices(weighted_graph, 1, 4),
      10);
}

TEST_F(GraphAlgorithmsTest, GetShortestPathBetweenVertices_NoPath) {
  EXPECT_EQ(
      GraphAlgorithms::GetShortestPathBetweenVertices(disconnected_graph, 1, 3),
      UINT_MAX);
}

TEST_F(GraphAlgorithmsTest, GetShortestVectorBetweenVertices_ValidPath) {
  auto path1 =
      GraphAlgorithms::GetShortestVectorBetweenVertices(simple_graph, 1, 3);
  ASSERT_EQ(path1.size(), 3);
  EXPECT_EQ(path1[0], 1);
  EXPECT_EQ(path1[1], 2);
  EXPECT_EQ(path1[2], 3);

  auto path2 =
      GraphAlgorithms::GetShortestVectorBetweenVertices(weighted_graph, 1, 4);
  ASSERT_EQ(path2.size(), 4);
  EXPECT_EQ(path2[0], 1);
  EXPECT_EQ(path2[1], 2);
  EXPECT_EQ(path2[2], 3);
  EXPECT_EQ(path2[3], 4);
}

TEST_F(GraphAlgorithmsTest, GetShortestVectorBetweenVertices_NoPath) {
  auto path = GraphAlgorithms::GetShortestVectorBetweenVertices(
      disconnected_graph, 1, 3);
  EXPECT_TRUE(path.empty());
}

TEST_F(GraphAlgorithmsTest, GetShortestVectorBetweenVertices_SameVertex) {
  auto path =
      GraphAlgorithms::GetShortestVectorBetweenVertices(simple_graph, 1, 1);
  ASSERT_EQ(path.size(), 1);
  EXPECT_EQ(path[0], 1);
}

TEST_F(GraphAlgorithmsTest, ShortestPathsAllVertices_DisconnectedGraph) {
  EXPECT_THROW(
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(disconnected_graph),
      std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, SpanTree_DisconnectedGraph) {
  EXPECT_THROW(GraphAlgorithms::GetSpanTree(disconnected_graph),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeThrowsOnInvalidGraph) {
  Graph empty_graph(0);
  EXPECT_THROW(GraphAlgorithms::GetSpanTree(empty_graph),
               std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeSimpleGraph) {
  simple_graph.valid_graph_ = true;
  auto [matrix, weight] = GraphAlgorithms::GetSpanTree(simple_graph);

  EXPECT_EQ(weight, 4);
  EXPECT_EQ(matrix[0][1], 1);
  EXPECT_EQ(matrix[1][0], 2);
  EXPECT_EQ(matrix[1][2], 3);
  EXPECT_EQ(matrix[2][1], 4);
  EXPECT_EQ(matrix[0][2], 0);
  EXPECT_EQ(matrix[2][0], 0);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeWeightedGraph) {
  weighted_graph.valid_graph_ = true;
  auto [matrix, weight] = GraphAlgorithms::GetSpanTree(weighted_graph);

  EXPECT_EQ(weight, 10);

  EXPECT_EQ(matrix[0][1], 5);
  EXPECT_EQ(matrix[1][0], 5);
  EXPECT_EQ(matrix[1][2], 3);
  EXPECT_EQ(matrix[2][1], 3);
  EXPECT_EQ(matrix[2][3], 2);
  EXPECT_EQ(matrix[3][2], 2);
  EXPECT_EQ(matrix[0][2], 0);
  EXPECT_EQ(matrix[2][0], 0);
  EXPECT_EQ(matrix[1][3], 0);
  EXPECT_EQ(matrix[3][1], 0);
}

TEST_F(GraphAlgorithmsTest, GetLeastSpanningTreeValidGraph1) {
  valid_graph1.valid_graph_ = true;
  Alias::IntGrid result = GraphAlgorithms::GetLeastSpanningTree(valid_graph1);

  EXPECT_EQ(result[0][1], 1);
  EXPECT_EQ(result[1][0], 1);
  EXPECT_EQ(result[1][2], 2);
  EXPECT_EQ(result[2][1], 2);
  EXPECT_EQ(result[0][2], 0);
  EXPECT_EQ(result[2][0], 0);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeWeightValidGraph2) {
  valid_graph2.valid_graph_ = true;
  int weight = GraphAlgorithms::GetSpanTreeWeight(valid_graph2);
  EXPECT_EQ(weight, 10);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeGraphWithLoop) {
  graph_with_loop.valid_graph_ = true;
  auto [matrix, weight] = GraphAlgorithms::GetSpanTree(graph_with_loop);

  EXPECT_EQ(weight, 1);
  EXPECT_EQ(matrix[0][1], 1);
  EXPECT_EQ(matrix[1][0], 1);
}

TEST_F(GraphAlgorithmsTest, GetSpanTreeGraph3) {
  graph3_.valid_graph_ = true;
  auto [matrix, weight] = GraphAlgorithms::GetSpanTree(graph3_);

  EXPECT_EQ(weight, 2);
  int edge_count = 0;
  for (const auto& row : matrix) {
    for (int val : row) {
      if (val > 0) edge_count++;
    }
  }
  EXPECT_EQ(edge_count, 4);
}

TEST_F(GraphAlgorithmsTest, ThrowsOnEmptyGraph) {
  EXPECT_THROW(
      { GraphAlgorithms::SolveTravelingSalesmanProblem(empty_graph_); },
      std::invalid_argument);
}

TEST_F(GraphAlgorithmsTest, ThrowsOnDisconnectedGraph) {
  disconnected_graph.valid_graph_ = true;
  EXPECT_THROW(
      { GraphAlgorithms::SolveTravelingSalesmanProblem(disconnected_graph); },
      std::runtime_error);
}

TEST_F(GraphAlgorithmsTest, DoesNotThrowOnValidGraph) {
  valid_graph_.valid_graph_ = true;
  EXPECT_NO_THROW(
      { GraphAlgorithms::SolveTravelingSalesmanProblem(valid_graph_); });
}

TEST_F(GraphAlgorithmsTest, ReturnsValidResultOnValidGraph) {
  valid_graph_.valid_graph_ = true;
  TsmResult result =
      GraphAlgorithms::SolveTravelingSalesmanProblem(valid_graph_);

  EXPECT_EQ(result.vertices.size(), valid_graph_.get_graph_size() + 1);

  std::unordered_set<size_t> unique_vertices(result.vertices.begin(),
                                             result.vertices.end() - 1);
  EXPECT_EQ(unique_vertices.size(), valid_graph_.get_graph_size());

  EXPECT_GT(result.distance, 0);
}