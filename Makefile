
all: main test

main: main.cpp
	g++ -o main main.cpp

test: tests.cpp
	g++ -o test tests.cpp -std=c++11

clean:
	rm main test
