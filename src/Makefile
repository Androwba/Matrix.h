CC          =  gcc
CFLAGS      = -std=c11 -Wall -Wextra -Werror -g
GCOV_FLAGS := -fprofile-arcs -ftest-coverage -fprofile-abs-path
LCHECK      = -lcheck
LIN_FLAGS  := -lpthread -pthread -lrt -lm -lsubunit -D_GNU_SOURCE
UNITNAME    =  unit_tests
RM          =  rm -rf
ARCHIVER    =  ar
ARFLAGS     =  cr -s
SOURCE      = s21_create_remove/s21_create_matrix.c \
		      s21_create_remove/s21_remove_matrix.c \
			  s21_comparison/s21_eq_matrix.c \
			  s21_comparison/correctness_of_the_matrix.c \
			  s21_adding_subtracting/s21_sub_matrix.c \
			  s21_adding_subtracting/s21_sum_matrix.c \
			  s21_multiplication/s21_mult_number.c \
			  s21_multiplication/s21_mult_matrix.c \
			  s21_transpose/s21_transpose.c \
			  s21_complements/s21_calc_complements.c \
			  s21_complements/determ_helper.c \
			  s21_complements/minor_of_matrix.c \
			  s21_complements/reduce.c \
			  s21_complements/s21_determinant.c \
			  s21_inverse/s21_inverse_matrix.c

FIND&CHECK        =      $(wildcard *.c *.h \
	./s21_create_remove/*.h ./s21_create_remove/*.c ./s21_comparison/*.h ./s21_comparison/*.c \
	./s21_adding_subtracting/*.c ./s21_adding_subtracting/*.h ./s21_multiplication/*.c ./s21_multiplication/*.h \
	./s21_transpose/*.c ./s21_transpose/*.h ./s21_complements/*.c ./s21_complements/*.h ./s21_inverse/*.c ./s21_inverse/*.h)

ifeq ($(shell uname), Linux)
LCHECK += $(LIN_FLAGS)
OPEN = xdg-open report/index.html
LEAKS = CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s
else
OPEN = open report/index.html
LEAKS = @CK_FORK=no leaks --atExit --
endif

OBJ_DIR := ./obj
OBJ_GCOV_DIR := ./obj_gcov
OBJECTS := $(addprefix obj/,$(SOURCE:.c=.o))
OBJECTS_GCOV := $(addprefix obj_gcov/,$(SOURCE:.c=.o))
HEADER = s21_matrix.h

all: s21_matrix.a

s21_matrix.a: make_directory $(OBJECTS)
	$(ARCHIVER) $(ARFLAGS) $@ $(OBJ_DIR)/*.o

lib_gcov.a: make_directory $(OBJECTS_GCOV)
	$(ARCHIVER) $(ARFLAGS) $@ $(OBJ_GCOV_DIR)/*.o

make_directory:
	mkdir -p $(OBJ_DIR) $(OBJ_GCOV_DIR)

test: s21_unit_tests.c $(HEADER) lib_gcov.a
	$(CC) $(CFLAGS) $^ -o $(UNITNAME) $(LCHECK) $(GCOV_FLAGS)
	./$(UNITNAME)
	@mv *gcda *gcno $(OBJ_GCOV_DIR)/

gcov_report: test
	@$(RM) report
	@$(RM) $(OBJ_GCOV_DIR)/*tests*
	@mkdir report
	@gcovr --html --html-details --html-details-syntax -o report/index.html
	@$(OPEN)

lcov: test
	@$(RM) $(OBJ_GCOV_DIR)/*tests*
	@lcov --capture --directory $(OBJ_GCOV_DIR)/. -o $(OBJ_GCOV_DIR)/coverage.info
	@genhtml $(OBJ_GCOV_DIR)/coverage.info --output-directory report
	@$(OPEN)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	@mv *.o $(OBJ_DIR)/

$(OBJ_GCOV_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $(subst /,_,$@) $(LIN_FLAGS)
	@mv *.o *gcno $(OBJ_GCOV_DIR)/

google:
	clang-format -i $(FIND&CHECK)

check: cpp style leaks

cpp:
	@echo "\033[92m◄----------------------- CPP ------------------------------►\033[0m"
	@cppcheck --enable=all --suppress=missingIncludeSystem  $(FIND&CHECK)

style:	
	@echo "\033[96m◄----------------------- Style Test -----------------------►\033[0m"
	@cp ../materials/linters/.clang-format .
	@clang-format -n $(FIND&CHECK) 
	@echo "\033[92mTest Done\033[0m"

leaks:
	@echo "\033[92m◄----------------------- Leaks ----------------------------►\033[0m"
	$(LEAKS) ./$(UNITNAME)

clean:
	@$(RM) .clang-format
	$(RM) $(OBJ_DIR) $(OBJ_GCOV_DIR)
	$(RM) s21_matrix.a lib_gcov.a
	$(RM) *.o *gc* test_test report
	$(RM) *.html *.css
	$(RM) $(UNITNAME)

rebuild:
	$(MAKE) clean
	$(MAKE) all 

# make git m="your message"
git:
	git add .
	git commit -m "$m"
	git push origin develop

.PHONY: all clean rebuild test check make_foulder gcov_report lcov
