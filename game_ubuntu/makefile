IDIR = include/
SDIR = src/

LIBRARYDIR = -L ../network/lib/
INCLUDEDIR = -I $(IDIR) -I ../network/include/

CC = g++
FLAG = -std=c++14 -fmax-errors=1
LIBRARY = -lncurses -ltcp

OBJS = control-snake.o coord.o cursor.o map.o\
		ViewInterface.o model.o SingleView.o connection.o

all : main clean

main : $(OBJS)
	$(CC) $(FLAG) $(INCLUDEDIR) $(LIBRARYDIR) main.cpp $(OBJS) $(LIBRARY)

%.o : $(SDIR)%.cpp $(IDIR)%.h
	$(CC) $(FLAG) $(INCLUDEDIR) $(LIBRARYDIR) -c $<

clean :
	rm *.o
