TESTFLAGS = -std=c++20 -I include
MAINFLAGS = -std=c++20 -I include


build:
	g++ main.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${MAINFLAGS}-o main

run:
	./main

test:
	g++ test.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${TESTFLAGS} -o tester

runTest:
	./tester

clean: 
	rm -f test main