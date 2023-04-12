TESTFLAGS = -std=c++20 -I include
MAINFLAGS = -std=c++20 -I include
MAIN_EXECUTABLE = main
TEST_EXECUTABLE = tester
TABLE_GENERATION_FILE = ./TableGeneration/generate_table.cpp
TABLE_GENERATION_EXECUTABLE = ./TableGeneration/generate_table
TABLE = ./TableGeneration/HandRanks.dat

build:
	g++ main.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${MAINFLAGS} -o ${MAIN_EXECUTABLE}
	./${MAIN_EXECUTABLE}
	

test:
	g++ test.cpp Card.cpp Hand.cpp Player.cpp Table.cpp ${TESTFLAGS} -o ${TEST_EXECUTABLE}

runTest:
	./${TEST_EXECUTABLE}

clean: 
	rm -f ${TEST_EXECUTABLE} ${MAIN_EXECUTABLE} ${TABLE_GENERATION_EXECUTABLE} ${TABLE}

table:
	g++ ${TABLE_GENERATION_FILE} -o ${TABLE_GENERATION_EXECUTABLE}
	${TABLE_GENERATION_EXECUTABLE}