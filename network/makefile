OBJS = tcp.o

OBJS_LOCATION = $(patsubst %.o, bin/%.o, $(OBJS))

main : $(OBJS)
	rm lib/* || true
	ar -cvq lib/libtcp.a bin/*.o

%.o : src/%.cc include/%.h
	g++ -c $< -O4 -o bin/$@ -I include/

clean :
	rm bin/* lib/*