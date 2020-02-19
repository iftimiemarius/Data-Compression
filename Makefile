all: build

build: algo.o algo2.o
	g++ tester.cpp algo.o algo2.o -o tester -lstdc++ -Wall

algo.o: algo.cpp
	g++ -c algo.cpp

algo2.o: algo2.cpp
	g++ -c algo2.cpp

run: build
	./tester ${ARGS}

generate_test: compile_generator
	java TestGenerator ${ARGS}

compile_generator: TestGenerator.java
	javac TestGenerator.java

.PHONY: clean
clean:
	rm -rf *.class *.o tester out/* out_decompressed/*
