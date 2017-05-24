OBJS = tcp.o session.o

OBJS_LOCATION = $(patsubst %.o, bin/%.o, $(OBJS))

main : make_dir $(OBJS)
	mkdir lib/ bin/ || true
	rm lib/* || true
	ar -cvq lib/libtcp.a bin/*.o

make_dir :
	mkdir -p lib/ bin/

%.o : src/%.cc include/%.h
	g++ -c $< -O4 -o bin/$@ -I include/

clean :
	rm bin/* lib/*