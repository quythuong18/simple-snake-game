FLAGS = -lSDL2 -Wall

snake: ./build/snake.o ./build/main.o
	g++ $(FLAGS) $? -o ./build/snake

main.o: main.cpp
	g++ $(FLAGS) -c $? -o ./build/main.o

snake.o: snake.cpp
	g++ $(FLAGS) -c $? -o ./build/snake.o

clean:
	rm -f build/*.o ./build/snake
