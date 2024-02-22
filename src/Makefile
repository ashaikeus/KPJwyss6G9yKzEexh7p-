FLAGS = -Wall -Werror -Wextra -g
LIB_FLAGS = -lgtest -lgcov
CODE_FILES = s21_matrix_oop.cpp
TEST_FILES = tests/test.cpp

all:
	g++ $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) $(FLAGS)
	./a.out

style:
	clang-format -n *.cpp *.h
	clang-format -i *.cpp *.h

checks: style
	g++ $(FLAGS) $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS)
	cppcheck *.c *.h

clean:
	rm -rf report *.a *.o *.gcda *.gcno *.gcov *.info test *.out *.dSYM *.exe

test: clean s21_matrix_oop.a
	g++ $(TEST_FILES) -o test s21_matrix_oop.a -lcheck
	./test
	rm ./test

main:
	g++ $(CODE_FILES)
	./a.out
	rm ./a.out

s21_matrix_oop.a:
	g++ -c $(CODE_FILES)
	ar rcs s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a

gcov_report: s21_matrix_oop.a
	g++ --coverage $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) -o test
	./test
	lcov -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
