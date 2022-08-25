
all: clean main main4d

main: main.cpp
	g++ -o main main.cpp -lboost_system -lboost_thread

main4d: main4d.cpp
	g++ -o $@ $^ -lboost_system -lboost_thread

.PHONY: clean

clean:
	rm -f main main4d
