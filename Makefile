TESTFLAGS = -std=c++20



test:
	g++ test.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${TESTFLAGS} -o tester

runTest:
	./tester

build:
	g++ Card.cpp Hand.cpp Player.cpp Table.cpp -o main

run:
	./main

clean: 
	rm -f test main