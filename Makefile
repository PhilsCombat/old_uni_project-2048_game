.PRECIOUS: %.o
.SUFFIXES:
.PHONY: clean compile test checkstyle

LIB = -lncurses
TESTLIB = -lgtest -lpthread -lgtest_main

CPP = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))
MAIN_CPP = $(basename $(wildcard *Main.cpp))
TEST_CPP = $(basename $(wildcard *Test.cpp))
HEADERS = $(wildcard *.h)

all: compile test checkstyle


compile: $(MAIN_CPP) $(TEST_CPP)

test: $(TEST_CPP)
	for T in $(TEST_CPP); do ./$$T; done



%Main: %Main.o $(CPP)
	g++ -g -Wall -o $@ $^ $(LIB)

%Test: %Test.o $(CPP) 
	g++ -g -Wall -o $@ $^ $(TESTLIB) $(LIB)


%.o: %.cpp $(HEADERS)
	g++ -g -Wall -c $<



checkstyle:
	python3 ../cpplint.py --repository=. *.h *.cpp



clean:
	rm -f $(MAIN_CPP)
	rm -f $(TEST_CPP)




