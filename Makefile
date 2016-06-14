CXX = gcc
CXX_FLAGS = -g -Wall
BIN_NAME = "timer_per"

all:
	$(CXX) $(CXX_FLAGS) -lm -O3 -o $(BIN_NAME) timer_per.c

clean:
	rm -rf *.o *~ *$(BIN_NAME)
