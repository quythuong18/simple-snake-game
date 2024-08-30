FLAGS = -lSDL2 -lSDL2_ttf -Wall


all: core.o snake.o main.o snake

snake: ./build/snake.o ./build/main.o ./build/core.o
	g++ $(FLAGS) $? -o ./build/snake

main.o: main.cpp
	g++ $(FLAGS) -c $? -o ./build/main.o

snake.o: snake.cpp
	g++ $(FLAGS) -c $? -o ./build/snake.o

core.o: core.cpp
	g++ $(FLAGS) -c $? -o ./build/core.o

# testing
test.o: ./test/test.cpp
	g++ $(FLAGS) -c $< -o ./build/test.o
test: ./build/core.o ./build/test.o
	g++ $(FLAGS) $? -o ./build/test

clean:
	rm -f build/*.o ./build/snake
