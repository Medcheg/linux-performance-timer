CXX = gcc
CXX_FLAGS = -g -Wall
V9_FLAG = 
LD_FLAGS =

all:
	$(CXX) $(V9_FLAG) -lm -O3 -o timer_per timer_per.c

clean :
	\rm -fr *.o *~ aes_attack describe_key aes_test