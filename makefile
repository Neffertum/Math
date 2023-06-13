#---------------Опции-----------------------
# Компилятор
CC=gcc

# Дополнительные флаги сборки
CFLAG=-Wall -Wextra -Werror

# Используемый стандарт Си
CSTANDARD=-std=c11 -pedantic

# Флаг для отладки
DEBUG=-g

# Исходные файлы
SRC_FILES=s21_*.c

# Заголовочные файлы
HDR_FILES=s21_*.h

# Файл с тестами
TEST_FILE=test.c

# Файл с тестами в разметке CHECK
TEST_FILE_CHECK=test.check

# Исполняемый файл
EXEC=tests.out

# Имя собираемой статической библиотеки
LIBNAME=s21_math.a

# Тип операционной системы
UNAME_S=$(shell uname -s);
#-------------------------------------------


all: style_checks s21_math.a gcov_report

s21_math.a:
	$(CC) $(CFLAG) $(CSTANDARD) -c $(SRC_FILES)
	ar rcs $(LIBNAME) $(SRC_FILES:.c=.o)
	ranlib $(LIBNAME)
	rm -rf *.o

test: s21_math.a test_$(UNAME_S)

gcov_report: test gcov_$(UNAME_S)

clean:
	rm -rf *.info *.gcda *.gcno report *.out *.a *.gcov
	rm -rf report a.out.dsym cpplint.py *.dSYM
	rm -rf $(OBJ_PATH)/*.o
	rm -rf *.o
	rm -f $(TEST_FILE)
	rm -f CPPLINT.CFG CPPLINT.cfg

rebuild: clean all

test_Darwin: checkmk
	$(CC) $(CSTANDARD) $(TEST_FILE) $(SRC_FILES) -coverage -o $(EXEC) -lcheck -lm
	./$(EXEC)

gcov_Darwin: test_Darwin
	gcov *.gcda
	geninfo *.gcda *.gcno -b . -o  report.info
	genhtml -o report report.info;
	rm -rf *.info *.gcda *.gcno
	open ./report 

# Цели для проверки проекта в OS Linux и на WSL
test_Linux: checkmk
	$(CC) $(CSTANDARD) $(TEST_FILE) $(DEBUG) $(SRC_FILES) -coverage -lcheck_pic -pthread -lrt -lm -lsubunit -o $(EXEC)
	./$(EXEC)

gcov_Linux: test_Linux
	gcov *.gcda
	geninfo *.gcda *.gcno -b . -o  report.info
	genhtml -o report report.info;
	rm -rf *.info *.gcda *.gcno
	open ./report || explorer.exe .


# Дополнительные цели

# Проверка на стили
style_checks:
	cp -f ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c $(SRC_FILES) $(HDR_FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config $(SRC_FILES) $(HDR_FILES)  

# проверка на утечки памяти
test_leaks_Darwin: checkmk s21_math.a test
	$(CC) $(CSTANDARD) $(TEST_FILE) -L. $(LIBNAME) -coverage -o $(EXEC) -lcheck -lm
	leaks -atExit -- ./$(EXEC) | grep LEAK:

test_leaks_Linux: checkmk s21_math.a
	$(CC) $(CSTANDARD) $(TEST_FILE) $(DEBUG) -L. $(LIBNAME) -coverage -lcheck_pic -pthread -lrt -lm -lsubunit -o $(EXEC)
	valgrind --leak-check=full -v ./$(EXEC)

# конвертация файлов с тестами

# проверка на утечки памяти

checkmk:
	checkmk $(TEST_FILE_CHECK) > $(TEST_FILE)
