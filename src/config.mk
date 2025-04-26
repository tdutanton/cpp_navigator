SHELL := /bin/sh

#### COMPILATION FLAGS ####
CC := g++ -std=c++20
CFLAGS := -Wall -Werror -Wextra
LFLAGS := -pthread -lgtest -lgtest_main -lstdc++
GFLAGS := -O0 --coverage -fprofile-arcs -ftest-coverage
DEBUG_FLAG := -g

#### FILE NAMES ####
FILE_NAME_TEST_GRAPH := tests_graph
FILE_NAME_TEST_ALGORITHMS := tests_algorithms

LIB_GRAPH_SRC = $(wildcard $(DIR_LIBS)/$(DIR_GRAPH_LIB)/*.cpp)
LIB_ALGORITHMS_SRC = $(wildcard $(DIR_LIBS)/$(DIR_ALGORITHMS_LIB)/*.cpp)
LINKED_LIST_SRC = $(wildcard $(DIR_LIBS)/$(DIR_LINKED_LIST)/*.cpp)
LIB_STACK_SRC = $(wildcard $(DIR_LIBS)/$(DIR_STACK_LIB)/*.cpp)
LIB_QUEUE_SRC = $(wildcard $(DIR_LIBS)/$(DIR_QUEUE_LIB)/*.cpp)

TEST_GRAPH_SRC =  $(wildcard $(DIR_TESTS)/$(DIR_GRAPH_TEST)/*.cpp)
TEST_ALGORITHMS_SRC = $(wildcard $(DIR_TESTS)/$(DIR_ALGORITHMS_TEST)/*.cpp)

LIB_GRAPH_H = $(wildcard $(DIR_LIBS)/$(DIR_GRAPH_LIB)/*.h)
LIB_ALGORITHMS_H = $(wildcard $(DIR_LIBS)/$(DIR_ALGORITHMS_LIB)/*.h)
LINKED_LIST_H = $(wildcard $(DIR_LIBS)/$(DIR_LINKED_LIST)/*.h)
LIB_STACK_H = $(wildcard $(DIR_LIBS)/$(DIR_STACK_LIB)/*.h)
LIB_QUEUE_H = $(wildcard $(DIR_LIBS)/$(DIR_QUEUE_LIB)/*.h)

ALL_HEADERS = $(LIB_GRAPH_H) $(LIB_ALGORITHMS_H) $(LINKED_LIST_H) $(LIB_STACK_H) $(LIB_QUEUE_H)

UML_INPUT_FILES = $(foreach file,$(ALL_HEADERS),-i $(file))

LIB_GRAPH_O = $(LIB_GRAPH_SRC:.cpp=.o)
LIB_ALGORITHMS_O = $(LIB_ALGORITHMS_SRC:.cpp=.o)
LINKED_LIST_O = $(LINKED_LIST_SRC:.cpp=.o)
LIB_STACK_O = $(LIB_STACK_SRC:.cpp=.o)
LIB_QUEUE_O = $(LIB_QUEUE_SRC:.cpp=.o)

TEST_GRAPH_O = $(TEST_GRAPH_SRC:.cpp=.o)
TEST_ALGORITHMS_O = $(TEST_ALGORITHMS_SRC:.cpp=.o)

GCOV_NAME := gcov_tests.info

DIST_NAME = graphlib-$(shell date +%Y%m%d)

MAIN_CPP := main.cpp

EXE := graph_cli

#### FOLDERS ####
DIR_LIBS := lib
DIR_TESTS := tests

DIR_GRAPH_LIB := s21_graph
DIR_ALGORITHMS_LIB := s21_graph_algorithms
DIR_LINKED_LIST := s21_linked_list
DIR_STACK_LIB := s21_stack
DIR_QUEUE_LIB := s21_queue

DIR_GRAPH_TEST := tests_s21_graph
DIR_ALGORITHMS_TEST := tests_s21_graph_algorithms

DIR_DOCS := documentation
DIR_DIST = dist/$(DIST_NAME)
DIR_REPORT := report

EXE_DIR := ./

#### TARGET LLIBRARIES ####
LIB_NAME_GRAPH := s21_graph.a
LIB_NAME_ALGORITHMS := s21_graph_algorithms.a
LIB_NAME_STACK := s21_stack.a
LIB_NAME_QUEUE := s21_queue.a

#### UML NAMES ####
UML_LIB := hpp2plantuml
PLANTUML_LIB := plantuml
PYTHON_LIB := python3-pip

CHECK_UML_UTIL = $(shell which $(UML_LIB))
CHECK_PIP3_LIB = $(shell which pip3)
CHECK_PLANTUML_LIB = $(shell which $(PLANTUML_LIB))

INSTALL_UML_LIB = pip install $(UML_LIB)
INSTALL_PLANTUML_LIB = sudo apt install -y $(PLANTUML_LIB)
INSTALL_PYTHON_LIB = sudo apt install -y $(PYTHON_LIB)

UML_FILE_NAME := graph_uml.puml
UML_PNG_FILE_NAME := graph_uml.png

#### DVI NAMES ####
XETEX_LIB := texlive-xetex
CYRILLIC_LIB := texlive-lang-cyrillic
DOXYGEN_LIB := doxygen

CHECK_XETEX_LIB = $(shell dpkg -l | grep $(XETEX_LIB))
CHECK_CYRILLIC_LIB = $(shell dpkg -l | grep $(CYRILLIC_LIB))
CHECK_DOXYGEN_LIB = $(shell which $(DOXYGEN_LIB))

INSTALL_XETEX_LIB = sudo apt install -y $(XETEX_LIB)
INSTALL_CYRILLIC_LIB = sudo apt install -y $(CYRILLIC_LIB)
INSTALL_DOXYGEN_LIB = sudo apt install -y $(DOXYGEN_LIB)

#### DIST ####
INCLUDE_DIR := include
PREFIX ?= /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include/graph

#### COLORS ####
RED := \033[31m
GREEN := \033[32m
BLUE := \033[34m
RESET := \033[0m
BOLD := \033[1m
UNDERLINE := \033[4m