ContadorStrings:
	g++ -o ContadorStrings main.cpp -w -lpthread -std=c++11

all:
	rm ContadorStrings
	g++ -o ContadorStrings main.cpp -w -lpthread -std=c++11

clean:
	rm ContadorStrings
