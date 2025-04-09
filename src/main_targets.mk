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
	find . -name '*.cpp' -exec clang-format -i {} \;
	find . -name '*.h' -exec clang-format -i {} \;
	@rm -rf .clang-format

.PHONY: clean
clean:
	@rm -rf $(FILE_NAME_TEST_GRAPH) $(FILE_NAME_TEST_ALGORITHMS) *.o .clang-format
	@rm -rf $(LIB_GRAPH_O) $(LIB_ALGORITHMS_O) ./tests/**/*.o *.gcno *.gcda ./report
	@rm -rf $(GCOV_NAME)
	@rm -rf $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS)
	@rm -rf *.out
	@rm -rf $(UML_FILE_NAME)
	@rm -rf out.png
	@rm -rf $(UML_PNG_FILE_NAME)
	@rm -rf $(DOCS_FOLDER)
	@rm -rf build
	@rm -rf $(REPORT_DIR)
	@rm -rf *.exe

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
dist: build
	@mkdir -p $(DIST_FOLDER)/
	@cp build/$(DIST_FILE) $(DIST_FOLDER)/$(DIST_FILE)
	tar cvzf $(DIST_FOLDER).tgz $(DIST_FOLDER)/
	@rm -rf $(DIST_FOLDER)/

.PHONY: rebuild
rebuild: clean build

.PHONY: valgrind_test_all
valgrind_test_all: valgrind_test_graph valgrind_test_algos

.PHONY: valgrind_test_graph
valgrind_test_graph: test_graph
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s ./$(FILE_NAME_TEST_GRAPH)

.PHONY: valgrind_test_algos
valgrind_test_algos: test_algorithms
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s ./$(FILE_NAME_TEST_ALGORITHMS)