########################################################
#						 RULES						   #
#						   \/						   #
########################################################

%.o: %.cpp
	@$(CC) $(CFLAGS) $(DEBUG_FLAG) -c $< -o $@

########################################################
#					SUPPORT TARGETS					   #
#						   \/						   #
########################################################

.PHONY: valgrind_all_tests
valgrind_test_all: valgrind_test_graph valgrind_test_algos

.PHONY: valgrind_test_graph
valgrind_test_graph: test_graph
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all \
	--track-origins=yes -s ./$(FILE_NAME_TEST_GRAPH)

.PHONY: valgrind_test_algos
valgrind_test_algos: test_algorithms
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all \
	--track-origins=yes -s ./$(FILE_NAME_TEST_ALGORITHMS)

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