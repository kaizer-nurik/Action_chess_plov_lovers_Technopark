compile: ./main.cpp
	g++ -c -g ./main.cpp ./textbox.hpp ./textbox.cpp ./button.hpp ./button.cpp ./menu_window.hpp ./menu_window.cpp ./chess_game.hpp ./chess_game.cpp ./Gamesession.hpp ./Gamesession.cpp
	g++ -g main.o textbox.o button.o menu_window.o chess_game.o Gamesession.o -o app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./app