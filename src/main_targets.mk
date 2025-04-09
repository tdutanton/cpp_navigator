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

#### <<ADDITIONAL LIBS - STACK AND QUEUE>> ####
.PHONY: s21_stack
s21_stack: $(LINKED_LIST_O) $(LIB_STACK_O)
	@ar rcs $(LIB_NAME_STACK) $(LINKED_LIST_O) $(LIB_STACK_O)
	@ranlib $(LIB_NAME_STACK)
	@rm -f $(LINKED_LIST_O) $(LIB_STACK_O)

.PHONY: s21_queue
s21_queue: $(LINKED_LIST_O) $(LIB_QUEUE_O)
	@ar rcs $(LIB_NAME_QUEUE) $(LINKED_LIST_O) $(LIB_QUEUE_O)
	@ranlib $(LIB_NAME_QUEUE)
	@rm -f $(LINKED_LIST_O) $(LIB_QUEUE_O)

#### <<TESTING>> ####
.PHONY: test
test: test_graph test_algorithms

.PHONY: test_graph
test_graph: $(TEST_GRAPH_O) $(LIB_NAME_GRAPH)
	@echo "Start testing graph"
	@rm -f $(FILE_NAME_TEST_GRAPH)
	@$(CC) $(CFLAGS) $(TEST_GRAPH_O) -DTEST -o $(FILE_NAME_TEST_GRAPH)\ 
	-L. l:$(LIB_NAME_GRAPH) $(LFLAGS) $(DEBUG_FLAG)
	@./$(FILE_NAME_TEST_GRAPH) || exit 1

.PHONY: test_algorithms
test_algorithms: $(TEST_ALGORITHMS_O) $(LIB_NAME_ALGORITHMS)
	@echo "Start testing graph algorithms"
	@rm -f $(FILE_NAME_TEST_ALGORITHMS)
	@$(CC) $(CFLAGS) $(TEST_ALGORITHMS_O) -DTEST -o $(FILE_NAME_TEST_ALGORITHMS)\
	 -L. -l:$(LIB_NAME_ALGORITHMS) $(LFLAGS) $(DEBUG_FLAG)
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
	@rm -rf $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS) $(LIB_NAME_STACK) $(LIB_NAME_QUEUE)
	@rm -rf *.out
	@rm -rf $(UML_FILE_NAME)
	@rm -rf out.png
	@rm -rf $(UML_PNG_FILE_NAME)
	@rm -rf $(DIR_DOCS)
	@rm -rf build
	@rm -rf $(DIR_REPORT)
	@rm -rf *.exe

.PHONY: install
install:
	@echo "INSTALLATION IN PROGRESS"
	@(make -s $(LIB_NAME_GRAPH))
	@(make -s $(LIB_NAME_ALGORITHMS))
	@mkdir -p $(DIR_INSTALL)/
	@mv $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS) $(DIR_INSTALL)/
	@(make -s clean)
	@echo "INSTALLATION COMPLETED - LIBS IN $(DIR_INSTALL) FOLDER"

.PHONY: uml_diagram
uml_diagram: pip3_check_lib uml_check_lib plantuml_check_lib
	@$(UML_LIB) -i "model/**/*.h" -i "gui/*.h" -o $(UML_FILE_NAME) -d
	@plantuml $(UML_FILE_NAME)
	@echo "UML diagram saved to $(UML_PNG_FILE_NAME), puml file saved to $(UML_FILE_NAME)"

.PHONY: dvi
dvi: clean doxygen_check_lib xetex_check_lib cyrillic_check_lib
	@mkdir -p $(DIR_DOCS)
	@doxygen Doxyfile > /dev/null 2>&1
	@cd $(DIR_DOCS)/latex && xelatex -interaction=batchmode refman.tex > /dev/null 2>&1
	@if [ $$? -eq 0 ]; then echo "DVI make success. See $(DIR_DOCS)/latex/refman.pdf for \
	pdf and $(DIR_DOCS)/html/index.html for html"; else echo "DVI ERROR"; fi

.PHONY: dist
dist: build
	@mkdir -p $(DIR_DIST)/
	@cp build/$(DIST_FILE) $(DIR_DIST)/$(DIST_FILE)
	tar cvzf $(DIR_DIST).tgz $(DIR_DIST)/
	@rm -rf $(DIR_DIST)/

.PHONY: rebuild
rebuild: clean build

