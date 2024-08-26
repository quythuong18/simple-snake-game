FLAGS = -lSDL2 -Wall

snake: ./build/snake.o ./build/main.o ./build/core.o
	g++ $(FLAGS) $? -o ./build/snake

main.o: main.cpp
	g++ $(FLAGS) -c $? -o ./build/main.o

snake.o: snake.cpp
	g++ $(FLAGS) -c $? -o ./build/snake.o

core.o: core.cpp
	g++ $(FLAGS) -c $? -o ./build/core.o
# testing
grid.o: ./test/grid.cpp
	g++ $(FLAGS) -c $< -o ./build/grid.o
grid: ./build/snake.o ./build/grid.o
	g++ $(FLAGS) $? -o ./build/grid

clean:
	rm -f build/*.o ./build/snake
