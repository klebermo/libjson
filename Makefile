export cc := g++
export cpp_flags := -Wall -pedantic -fPIC -g

all: libjson

libjson: value.o nullable.o string.o number.o boolean.o array.o object.o
	${cc} ${cpp_flags} -shared -o libjson.so value.o nullable.o  string.o number.o boolean.o array.o object.o

value.o: src/value.cpp
	${cc} ${cpp_flags} -c src/value.cpp -o value.o

nullable.o: src/nullable.cpp
	${cc} ${cpp_flags} -c src/nullable.cpp -o nullable.o

string.o: src/string.cpp
	${cc} ${cpp_flags} -c src/string.cpp -o string.o

number.o: src/number.cpp
	${cc} ${cpp_flags} -c src/number.cpp -o number.o

boolean.o: src/boolean.cpp
	${cc} ${cpp_flags} -c src/boolean.cpp -o boolean.o

array.o: src/array.cpp
	${cc} ${cpp_flags} -c src/array.cpp -o array.o

object.o: src/object.cpp
	${cc} ${cpp_flags} -c src/object.cpp -o object.o

clean:
	rm -f *.o *.so
