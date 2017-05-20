IDIR = include
SDIR = src

CC = g++
FLAG = -std=c++14

OBJS = control-snake.o coord.o cursor.o map.o ViewInterface.o model.o SingleView.o

all : main clean

main : $(OBJS)
	$(CC) $(FLAG) -I $(IDIR) -fmax-errors=1 main.cpp *.o -lncurses 

%.o : $(SDIR)/%.cpp $(IDIR)/%.h
	$(CC) $(FLAG) -c -I $(IDIR) $<

clean :
	rm *.o
