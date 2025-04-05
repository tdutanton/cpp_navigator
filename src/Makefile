SHELL = /bin/sh

#### COMPILATION FLAGS ####
CC = gcc -std=c++20
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

########################################################
#						TARGETS						   #
#						   \/						   #
########################################################

.PHONY: all
all: clean build

#### <<BUILD>> ####
.PHONY: build
build: s21_graph s21_graph_algorithms

.PHONY: s21_graph
s21_graph: $(LIB_GRAPH_O)
	@ar rcs $(LIB_NAME_GRAPH) $(LIB_GRAPH_O)
	@ranlib $(LIB_NAME_GRAPH)
	@rm -f $(LIB_GRAPH_O)

.PHONY: s21_graph_algorithms
s21_graph_algorithms: $(LIB_ALGORITHMS_O)
	@ar rcs $(LIB_NAME_ALGORITHMS) $(LIB_ALGORITHMS_O)
	@ranlib $(LIB_NAME_ALGORITHMS)
	@rm -f $(LIB_ALGORITHMS_O)
#### >>BUILD<< ####

#### <<TESTING>> ####
.PHONY: test
test: test_graph test_algorithms

.PHONY: test_graph
test_graph: $(TEST_GRAPH_O) $(LIB_NAME_GRAPH)
	@echo "Start testing graph"
	@rm -f $(FILE_NAME_TEST_GRAPH)
	@$(CC) $(CFLAGS) $(TEST_GRAPH_O) -DTEST -o $(FILE_NAME_TEST_GRAPH) -L. -l:$(LIB_NAME_GRAPH) $(LFLAGS) $(DEBUG_FLAG)
	@./$(FILE_NAME_TEST_GRAPH) || exit 1

.PHONY: test_algorithms
test_algorithms: $(TEST_ALGORITHMS_O) $(LIB_NAME_ALGORITHMS)
	@echo "Start testing graph algorithms"
	@rm -f $(FILE_NAME_TEST_ALGORITHMS)
	@$(CC) $(CFLAGS) $(TEST_ALGORITHMS_O) -DTEST -o $(FILE_NAME_TEST_ALGORITHMS) -L. -l:$(LIB_NAME_ALGORITHMS) $(LFLAGS) $(DEBUG_FLAG)
	@./$(FILE_NAME_TEST_ALGORITHMS) || exit 1
#### >>TESTING<< ####

.PHONY: style_check
style_check:
	@cp ../materials/linters/.clang-format .clang-format
	@find . -name '*.cpp' -o -name '*.h' | xargs clang-format -Werror -n
	@rm -rf .clang-format

.PHONY: style_fix
style_fix:
	@cp ../materials/linters/.clang-format .clang-format
	find . -name '*.c' -exec clang-format -i {} \;
	find . -name '*.cpp' -exec clang-format -i {} \;
	find . -name '*.h' -exec clang-format -i {} \;
	@rm -rf .clang-format

%.o: %.cpp
	@$(CC) $(CFLAGS) $(DEBUG_FLAG) -c $< -o $@

.PHONY: clean
clean:
	@rm -rf $(FILE_NAME_TEST_GRAPH) $(FILE_NAME_TEST_ALGORITHMS) *.o .clang-format
	@rm -rf $(LIB_GRAPH_O) $(LIB_ALGORITHMS_O) ./tests/*.o *.gcno *.gcda ./report
	@rm -rf $(GCOV_NAME)
	@rm -rf $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS)
	@rm -rf *.out
	@rm -rf $(UML_FILE_NAME)
	@rm -rf out.png
	@rm -rf $(UML_PNG_FILE_NAME)
	@rm -rf $(DOCS_FOLDER)
	@rm -rf build
	@rm -rf $(REPORT_DIR)

.PHONY: install
install:
	@echo "INSTALLATION IN PROGRESS"
	@(make -s $(LIB_NAME_GRAPH))
	@(make -s $(LIB_NAME_ALGORITHMS))
	@mkdir -p $(INSTALL_DIR)/
	@mv $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS) $(INSTALL_DIR)/
	@(make -s clean)
	@echo "INSTALLATION COMPLETED - LIBS IN $(INSTALL_DIR) FOLDER"

.PHONY: uml_diagram
uml_diagram: pip3_check_lib uml_check_lib plantuml_check_lib
	@$(UML_LIB) -i "model/**/*.h" -i "gui/*.h" -o $(UML_FILE_NAME) -d
	@plantuml $(UML_FILE_NAME)
	@echo "UML diagram saved to $(UML_PNG_FILE_NAME), puml file saved to $(UML_FILE_NAME)"

.PHONY: dvi
dvi: clean doxygen_check_lib xetex_check_lib cyrillic_check_lib
	@mkdir -p $(DOCS_FOLDER)
	@doxygen Doxyfile > /dev/null 2>&1
	@cd $(DOCS_FOLDER)/latex && xelatex -interaction=batchmode refman.tex > /dev/null 2>&1
	@if [ $$? -eq 0 ]; then echo "DVI make success. See $(DOCS_FOLDER)/latex/refman.pdf for \
	pdf and $(DOCS_FOLDER)/html/index.html for html"; else echo "DVI ERROR"; fi

.PHONY: dist
dist: uninstall install
	@mkdir -p $(DIST_FOLDER)/
	@cp build/3D_Viewer $(DIST_FOLDER)/3D_Viewer
	tar cvzf 3DViewer.tgz $(DIST_FOLDER)/
	@rm -rf $(DIST_FOLDER)/

########################################################
# 		CHECK IF NEEDED LIBRARIES ARE INSTALLED 	   #
#						  \/						   #						
########################################################

.PHONY: uml_check_lib
uml_check_lib:
	@if [ -z "$(CHECK_UML_UTIL)" ]; then \
		echo "Installing $(UML_LIB)"; \
		$(INSTALL_UML_LIB); \
	fi

.PHONY: pip3_check_lib
pip3_check_lib:
	@if [ -z "$(CHECK_PIP3_LIB)" ]; then \
		echo "Installing $(PYTHON_LIB)"; \
		$(INSTALL_PYTHON_LIB); \
	fi

.PHONY: plantuml_check_lib
plantuml_check_lib:
	@if [ -z "$(CHECK_PLANTUML_LIB)" ]; then \
		echo "Installing $(PLANTUML_LIB)"; \
		$(INSTALL_PLANTUML_LIB); \
	fi

.PHONY: doxygen_check_lib
doxygen_check_lib:
	@if [ -z "$(CHECK_DOXYGEN_LIB)" ]; then \
		echo "Installing $(DOXYGEN_LIB)"; \
		$(INSTALL_DOXYGEN_LIB); \
	fi

.PHONY: xetex_check_lib
xetex_check_lib:
	@if [ -z "$(CHECK_XETEX_LIB)" ]; then \
		echo "Installing $(XETEX_LIB)"; \
		$(INSTALL_XETEX_LIB); \
	fi

.PHONY: cyrillic_check_lib
cyrillic_check_lib:
	@if [ -z "$(CHECK_CYRILLIC_LIB)" ]; then \
		echo "Installing $(CYRILLIC_LIB)"; \
		$(INSTALL_CYRILLIC_LIB); \
	fi