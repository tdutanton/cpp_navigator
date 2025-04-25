#include "../s21_graph_tests.h"

class AntsGraphAlgorithmsTest : public ::testing::Test {
 protected:
  AntsGraphAlgorithmsTest() : graph3_(3), graph4_(4), full_graph5_(5) {
    graph3_[0][1] = 1;
    graph3_[1][0] = 1;
    graph3_[0][2] = 2;
    graph3_[2][0] = 2;
    graph3_[1][2] = 3;
    graph3_[2][1] = 3;

    graph4_[0][1] = 10;
    graph4_[1][0] = 10;
    graph4_[0][2] = 15;
    graph4_[2][0] = 15;
    graph4_[0][3] = 20;
    graph4_[3][0] = 20;
    graph4_[1][2] = 35;
    graph4_[2][1] = 35;
    graph4_[1][3] = 25;
    graph4_[3][1] = 25;
    graph4_[2][3] = 30;
    graph4_[3][2] = 30;

    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (i != j) full_graph5_[i][j] = 1;
      }
    }
  }

  Graph graph3_;
  Graph graph4_;
  Graph full_graph5_;
};

TEST_F(AntsGraphAlgorithmsTest, MST_3Nodes) {
  graph3_.valid_graph_ = true;
  auto matrix = GraphAlgorithms::GetLeastSpanningTree(graph3_);
  int weight = GraphAlgorithms::GetSpanTreeWeight(graph3_);

  EXPECT_EQ(weight, 3);
  EXPECT_GT(matrix[0][1], 0);
  EXPECT_GT(matrix[0][2], 0);
  EXPECT_EQ(matrix[1][2], 0);
}

TEST_F(AntsGraphAlgorithmsTest, MST_4Nodes) {
  graph4_.valid_graph_ = true;
  int weight = GraphAlgorithms::GetSpanTreeWeight(graph4_);
  EXPECT_EQ(weight, 45);
}

TEST_F(AntsGraphAlgorithmsTest, AntBasicFunctionality) {
  Ant ant(0);
  EXPECT_EQ(ant.get_current_vertex(), 0);
  EXPECT_TRUE(ant.is_vertex_unvisited(1));

  ant.visit_vertex(graph3_, 1);
  EXPECT_EQ(ant.get_current_vertex(), 1);
  EXPECT_FALSE(ant.is_vertex_unvisited(1));
}

TEST_F(AntsGraphAlgorithmsTest, AntHillInitialization) {
  AntHill anthill(graph3_);
  anthill.set_start_pheromone_(0.1);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i != j && graph3_[i][j] > 0) {
        EXPECT_GT(anthill.pheromone_matrix_[i][j], 0);
      }
    }
  }
}

TEST_F(AntsGraphAlgorithmsTest, AntTransitionProbability) {
  AntHill anthill(graph3_);
  anthill.set_alpha_pheromone_weight(1.0);
  anthill.set_beta_distance_weight_(2.0);

  Ant ant(0);
  ant.visit_vertex(graph3_, 1);

  double prob = anthill.ant_transition_probability(ant, 2);
  EXPECT_GT(prob, 0);
  EXPECT_LT(prob, 1);
}

TEST_F(AntsGraphAlgorithmsTest, TSP_SmallGraph) {
  AntHill anthill(graph3_);
  anthill.set_alpha_pheromone_weight(1.0);
  anthill.set_beta_distance_weight_(5.0);
  anthill.set_q_regulation_parameter_(100.0);
  anthill.set_p_pheromone_evaporation_coef(0.1);
  anthill.set_start_pheromone_(1.0);

  TsmResult result = anthill.solve_salesman_graph();

  EXPECT_EQ(result.vertices.size(), 4);
  EXPECT_EQ(result.vertices.front(), result.vertices.back());
  EXPECT_GT(result.distance, 0);
}

TEST_F(AntsGraphAlgorithmsTest, TSP_InvalidGraph) {
  Graph empty_graph(0);
  EXPECT_THROW(GraphAlgorithms::SolveTravelingSalesmanProblem(empty_graph),
               std::invalid_argument);
}

TEST_F(AntsGraphAlgorithmsTest, PheromoneUpdate) {
  AntHill anthill(graph3_);
  anthill.set_p_pheromone_evaporation_coef(0.5);

  Ant ant(0);
  ant.visit_vertex(graph3_, 1);
  ant.visit_vertex(graph3_, 2);
  ant.visit_vertex(graph3_, 0);

  double initial_pheromone = anthill.pheromone_matrix_[0][1];
  anthill.update_pheromone(ant);
  double updated_pheromone = anthill.pheromone_matrix_[0][1];

  EXPECT_NE(initial_pheromone, updated_pheromone);
}

TEST_F(AntsGraphAlgorithmsTest, ChooseNextVertex) {
  AntHill anthill(graph3_);
  Ant ant(0);

  size_t next = anthill.choose_next_vertex(ant);
  EXPECT_TRUE(next == 1 || next == 2);
}

TEST_F(AntsGraphAlgorithmsTest, TSP_FullGraph) {
  AntHill anthill(full_graph5_);
  TsmResult result = anthill.solve_salesman_graph();

  EXPECT_EQ(result.vertices.size(), 6);
  EXPECT_EQ(result.distance, 5);
}

TEST(FullAntsGraphAlgorithmsTest, SolveTravelingSalesmanProblem_SimpleCase) {
  Graph graph(3);
  graph[0][1] = 1;
  graph[1][0] = 1;
  graph[0][2] = 1;
  graph[2][0] = 1;
  graph[1][2] = 1;
  graph[2][1] = 1;
  graph.valid_graph_ = true;

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.vertices.size(), 4);
  EXPECT_EQ(result.vertices.front(), result.vertices.back());
  std::set<size_t> unique_vertices(result.vertices.begin(),
                                   result.vertices.end());
  EXPECT_EQ(unique_vertices.size(), 3);
  EXPECT_GT(result.distance, 0);
}

TEST(FullAntsGraphAlgorithmsTest, SolveTravelingSalesmanProblem_InvalidGraph) {
  Graph empty_graph(0);
  EXPECT_THROW(GraphAlgorithms::SolveTravelingSalesmanProblem(empty_graph),
               std::invalid_argument);
}