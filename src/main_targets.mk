########################################################
#						TARGETS						   #
#						   \/						   #
########################################################

.PHONY: all
all: build
	@echo "\n$(GREEN)$(BOLD)$(UNDERLINE)DONE. NOW YOU CAN TESTING LIBS\
	 OR PUSH \"MAKE RUN\" TO TRY IT IN CONSOLE$(RESET)\n"
	@echo "\n$(BLUE)$(BOLD)Few interesting make targets (all targets You can see in main_targets.mk file) :$(RESET)"
	@echo "\n$(BLUE)- build\n\
	- run\n\
	- test\n\
	- style_check\n\
	- clean\n\
	- install\n\
	- uninstall\n\
	- dvi\n\
	- dist\n\
	- gcov_report\n\
	- uml_diagram\n\
	- valgrind_all_tests\n$(RESET)"

.PHONY: run
run:
	@echo "$(GREEN)Compiling and running...$(RESET)"
	@$(CC) $(CFLAGS) $(MAIN_CPP) view/cli.cpp -L$(EXE_DIR) -l:$(LIB_NAME_GRAPH) -l:$(LIB_NAME_ALGORITHMS) -o $(EXE)
	@$(EXE_DIR)$(EXE)

#### <<BUILD>> ####
.PHONY: build
build: s21_graph s21_graph_algorithms

.PHONY: s21_graph
s21_graph: 
	@echo "$(GREEN)Compiling $(LIB_NAME_GRAPH) library...$(RESET)"
	@make -s $(LIB_GRAPH_O)
	@ar rcs $(LIB_NAME_GRAPH) $(LIB_GRAPH_O)
	@ranlib $(LIB_NAME_GRAPH)
	@rm -f $(LIB_GRAPH_O)

.PHONY: s21_graph_algorithms
s21_graph_algorithms: 
	@echo "$(GREEN)Compiling $(LIB_NAME_ALGORITHMS) library...$(RESET)"
	@make -s $(LIB_ALGORITHMS_O)
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
	@echo "$(GREEN)Start testing graph$(RESET)"
	@rm -f $(FILE_NAME_TEST_GRAPH)
	@$(CC) $(CFLAGS) $(TEST_GRAPH_O) -DTEST -o $(FILE_NAME_TEST_GRAPH) \
	-L. -l:$(LIB_NAME_GRAPH) $(LFLAGS) $(DEBUG_FLAG)
	@./$(FILE_NAME_TEST_GRAPH) || exit 1

.PHONY: test_algorithms
test_algorithms: $(TEST_ALGORITHMS_O) $(LIB_NAME_ALGORITHMS)
	@echo "$(GREEN)Start testing graph algorithms$(RESET)"
	@rm -f $(FILE_NAME_TEST_ALGORITHMS)
	@$(CC) $(CFLAGS) $(TEST_ALGORITHMS_O) -DTEST -o $(FILE_NAME_TEST_ALGORITHMS) \
	 -L. -l:$(LIB_NAME_ALGORITHMS) $(LFLAGS) $(DEBUG_FLAG)
	@./$(FILE_NAME_TEST_ALGORITHMS) || exit 1
#### >>TESTING<< ####

.PHONY: style_check
style_check:
	@cp ../materials/linters/.clang-format .clang-format
	@find . -name '*.cpp' -o -name '*.tpp' -o -name '*.h' | xargs clang-format -Werror -n
	@rm -rf .clang-format

.PHONY: style_fix
style_fix:
	@cp ../materials/linters/.clang-format .clang-format
	find . -name '*.cpp' -exec clang-format -i {} \;
	find . -name '*.tpp' -exec clang-format -i {} \;
	find . -name '*.h' -exec clang-format -i {} \;
	@rm -rf .clang-format

.PHONY: clean
clean: gcov_clean
	@echo "$(GREEN)CLEANING...$(RESET)"
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
	@rm -rf $(EXE)
	@echo "$(GREEN)CLEANING DONE$(RESET)"

.PHONY: clean_hard
clean_hard: clean
	@echo "$(GREEN)CLEANING CREATED FILES...$(RESET)"
	@rm -rf *.dot
	@echo "$(GREEN)CLEANING CREATED FILES DONE$(RESET)"

.PHONY: install
install:
	@echo "$(GREEN)INSTALLATION IN PROGRESS$(RESET)"
	@(make -s $(LIB_NAME_GRAPH))
	@(make -s $(LIB_NAME_ALGORITHMS))
	@mkdir -p $(DESTDIR)$(LIBDIR)
	@cp $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS) $(DESTDIR)$(LIBDIR)
	@mkdir -p $(DESTDIR)$(INCDIR)
	@cp $(ALL_HEADERS) $(DESTDIR)$(INCDIR)
	@echo "$(GREEN)INSTALLATION COMPLETED - LIBS IN $(DESTDIR)$(LIBDIR) FOLDER. HEADERS - IN $(DESTDIR)$(INCDIR) FOLDER$(RESET)"

.PHONY: uninstall
uninstall:
	@echo "$(GREEN)UNINSTALLING...$(RESET)"
	@rm -f $(DESTDIR)$(LIBDIR)/$(LIB_NAME_GRAPH)
	@rm -f $(DESTDIR)$(LIBDIR)/$(LIB_NAME_ALGORITHMS)
	@rm -f $(addprefix $(DESTDIR)$(INCDIR)/, $(notdir $(ALL_HEADERS)))
	@echo "$(GREEN)UNINSTALL COMPLETED$(RESET)"

.PHONY: dvi
dvi: doxygen_check_lib xetex_check_lib cyrillic_check_lib
	@mkdir -p $(DIR_DOCS)
	@doxygen Doxyfile > /dev/null 2>&1
	@cd $(DIR_DOCS)/latex && xelatex -interaction=batchmode refman.tex > /dev/null 2>&1
	@if [ $$? -eq 0 ]; then echo "$(GREEN)DVI make success\nSee $(DIR_DOCS)/latex/refman.pdf for \
	pdf and $(DIR_DOCS)/html/index.html for html version$(RESET)"; else echo "$(RED)DVI ERROR$(RESET)"; fi

.PHONY: dist
dist: all
	@echo "$(GREEN)Creating dist archive...$(RESET)"
	@mkdir -p $(DIR_DIST)/lib
	@mkdir -p $(DIR_DIST)/include/graph
	@cp $(LIB_NAME_GRAPH) $(LIB_NAME_ALGORITHMS) $(DIR_DIST)/lib/
	@cp $(ALL_HEADERS) $(DIR_DIST)/include/graph/
	@cp -r readme_src Makefile $(DIR_DIST)/
	tar czf $(DIST_NAME).tar.gz -C dist $(DIST_NAME)
	@rm -rf $(DIR_DIST)
	@echo "$(GREEN)Archive created: $(DIST_NAME).tar.gz$(RESET)"

.PHONY: rebuild
rebuild: clean build

.PHONY: gcov_report
gcov_report: gcov_clean gcov_graph gcov_algorithms

PHONY: gcov_graph
gcov_graph:
	@echo "$(GREEN)Start making gcov report - graph lib$(RESET)"
	@$(CC) $(CFLAGS) $(GFLAGS) -c $(LIB_GRAPH_SRC)
	@$(CC) $(CFLAGS) $(GFLAGS) -c $(TEST_GRAPH_SRC)
	@$(CC) *.o -o $(FILE_NAME_TEST_GRAPH) $(LFLAGS) $(GFLAGS)
	@./$(FILE_NAME_TEST_GRAPH)
	@lcov -t "gcov_tests" -o $(GCOV_NAME) -c -d . \
		--exclude '/usr/include/*' \
		--exclude '/usr/local/include/*' \
		--exclude '*tests*' \
		--exclude '*gtest*'
	@genhtml -o $(DIR_REPORT) $(GCOV_NAME)
	@echo "$(GREEN)Open $(DIR_REPORT)/index.html to view coverage report$(RESET)"

PHONY: gcov_algorithms
gcov_algorithms:
	@echo "$(GREEN)Start making gcov report - graph_algorithms lib$(RESET)"
	@$(CC) $(CFLAGS) $(GFLAGS) -c $(LIB_ALGORITHMS_SRC)
	@$(CC) $(CFLAGS) $(GFLAGS) -c $(TEST_ALGORITHMS_SRC)
	@$(CC) *.o -o $(FILE_NAME_TEST_ALGORITHMS) $(LFLAGS) $(GFLAGS)
	@./$(FILE_NAME_TEST_ALGORITHMS)
	@lcov -t "gcov_tests" -o $(GCOV_NAME) -c -d . \
		--exclude '/usr/include/*' \
		--exclude '/usr/local/include/*' \
		--exclude '*tests*' \
		--exclude '*gtest*'
	@genhtml -o $(DIR_REPORT) $(GCOV_NAME)
	@echo "$(GREEN)Open $(DIR_REPORT)/index.html to view coverage report$(RESET)"

.PHONY: gcov_clean
gcov_clean:
	@rm -f *.gcno *.gcda $(GCOV_NAME) *.o
	@rm -f $(FILE_NAME_TEST_GRAPH) $(FILE_NAME_TEST_ALGORITHMS)
	@rm -rf $(DIR_REPORT)