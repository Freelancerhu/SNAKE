IDIR=include
SDIR=src

CC=g++
FLAG=-std=c++11

OBJS=control-snake.o coord.o cursor.o map.o view.o model.o

all : main clean

main : $(OBJS)
	$(CC) $(FLAG) -I $(IDIR) main.cpp *.o -lncurses

%.o : $(SDIR)/%.cpp $(IDIR)/%.h
	$(CC) $(FLAG) -c -I $(IDIR) $<

clean :
	rm *.o