IDIR = ../include/
SDIR = ../src/

LIBRARYDIR = -L ../../network/lib/
INCLUDEDIR = -I $(IDIR) -I ../../network/include/

CC = g++
FLAG = -std=c++14 -fmax-errors=1
LIBRARY = -lncurses -ltcp

OBJS = map.o connection.o
PROGRAM = test-snake.cc

all : main clean

main : $(OBJS)
	$(CC) $(FLAG) $(INCLUDEDIR) $(LIBRARYDIR) $(PROGRAM)\
		$(OBJS) $(LIBRARY)

%.o : $(SDIR)%.cpp $(IDIR)%.h
	$(CC) $(FLAG) $(INCLUDEDIR) $(LIBRARYDIR) -c $<

clean :
	rm *.o
