TESTFLAGS = -std=c++20 -I include
MAINFLAGS = -std=c++20 -I include
MAIN_EXECUTABLE = main
TEST_EXECUTABLE = tester
TEST_GENERATION_FILE = ./TableGeneration/generate_table.cpp
TEST_GENERATION_EXECUTABLE = ./TableGeneration/generate_table

build:
	g++ main.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${MAINFLAGS}-o ${MAIN_EXECUTABLE}

run:
	./${MAIN_EXECUTABLE}

test:
	g++ test.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${TESTFLAGS} -o ${TEST_EXECUTABLE}

runTest:
	./${TEST_EXECUTABLE}

clean: 
	rm -f ${TEST_EXECUTABLE} ${MAIN_EXECUTABLE} ${TEST_GENERATION_EXECUTABLE}

table:
	g++ ${TEST_GENERATION_FILE} -o ${TEST_GENERATION_EXECUTABLE}
	${TEST_GENERATION_EXECUTABLE}