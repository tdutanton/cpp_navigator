SHELL = /bin/sh

#### COMPILATION FLAGS ####
CC = g++ -std=c++20
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -pthread -lgtest -lstdc++
GFLAGS = -fprofile-arcs -ftest-coverage
DEBUG_FLAG = -g

#### FILE NAMES ####
FILE_NAME_TEST_GRAPH = tests_graph
FILE_NAME_TEST_ALGORITHMS = tests_algorithms

LIB_GRAPH_SRC = $(wildcard lib/$(GRAPH_LIB_DIR)/*.cpp)
LIB_ALGORITHMS_SRC = $(wildcard lib/$(ALGORITHMS_LIB_DIR)/*.cpp)
TEST_GRAPH_SRC =  $(wildcard tests/$(GRAPH_TEST_DIR)/*.cpp)
TEST_ALGORITHMS_SRC = $(wildcard tests/$(ALGORITHMS_TEST_DIR)/*.cpp)

LIB_GRAPH_O = $(LIB_GRAPH_SRC:.cpp=.o)
LIB_ALGORITHMS_O = $(LIB_ALGORITHMS_SRC:.cpp=.o)
TEST_GRAPH_O = $(TEST_GRAPH_SRC:.cpp=.o)
TEST_ALGORITHMS_O = $(TEST_ALGORITHMS_SRC:.cpp=.o)

GCOV_NAME = gcov_tests.info

#### FOLDERS ####
DOCS_FOLDER = documentation
DIST_FOLDER = Graph
DIST_FILE = Graph_lib
REPORT_DIR = report
GRAPH_LIB_DIR = s21_graph
ALGORITHMS_LIB_DIR = s21_graph_algorithms
GRAPH_TEST_DIR = tests_s21_graph
ALGORITHMS_TEST_DIR = tests_s21_graph_algorithms
INSTALL_DIR = s21_bin

#### TARGET LLIBRARIES ####
LIB_NAME_GRAPH = s21_graph.a
LIB_NAME_ALGORITHMS = s21_graph_algorithms.a

#### UML NAMES ####
UML_LIB = hpp2plantuml
PLANTUML_LIB = plantuml
PYTHON_LIB = python3-pip

CHECK_UML_UTIL = $(shell which $(UML_LIB))
CHECK_PIP3_LIB = $(shell which pip3)
CHECK_PLANTUML_LIB = $(shell which $(PLANTUML_LIB))

INSTALL_UML_LIB = pip install $(UML_LIB)
INSTALL_PLANTUML_LIB = sudo apt install -y $(PLANTUML_LIB)
INSTALL_PYTHON_LIB = sudo apt install -y $(PYTHON_LIB)

UML_FILE_NAME = graph_uml.puml
UML_PNG_FILE_NAME = graph_uml.png

#### DVI NAMES ####
XETEX_LIB = texlive-xetex
CYRILLIC_LIB = texlive-lang-cyrillic
DOXYGEN_LIB = doxygen

CHECK_XETEX_LIB = $(shell dpkg -l | grep $(XETEX_LIB))
CHECK_CYRILLIC_LIB = $(shell dpkg -l | grep $(CYRILLIC_LIB))
CHECK_DOXYGEN_LIB = $(shell which $(DOXYGEN_LIB))

INSTALL_XETEX_LIB = sudo apt install -y $(XETEX_LIB)
INSTALL_CYRILLIC_LIB = sudo apt install -y $(CYRILLIC_LIB)
INSTALL_DOXYGEN_LIB = sudo apt install -y $(DOXYGEN_LIB)