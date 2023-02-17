TESTFLAGS = -std=c++14



test:
	g++ test.cpp Card.cpp Hand.cpp ${TESTFLAGS} -o test

runTest:
	./test

build:
	g++ Card.cpp Hand.cpp Player.cpp Table.cpp -o main

run:
	./main