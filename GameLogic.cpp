
#include "GameLogic.h"
#include <string>
#include <stdlib.h>

Figure::Figure(){

};

move_status Figure::makeMove(Figure** table, std::string move){

};
void Figure::set_name(std::string name){

};

void Figure::set_color(figure_color color){

};


King::King(figure_color color){

};

move_status King::makeMove(Figure** table, std::string move){

};

Queen::Queen(figure_color color, int wasPawn){

};

move_status Queen::makeMove(Figure** table, std::string move){

};

Bishop::Bishop(figure_color color, int wasPawn){

};

move_status Bishop::makeMove(Figure** table, std::string move){

};

Knight::Knight(figure_color color, int wasPawn){

};

move_status Knight::makeMove(Figure** table, std::string move){

};

Rock::Rock(figure_color color, int wasPawn){

};

move_status Rock::makeMove(Figure** table, std::string move){

};

Pawn::Pawn(figure_color color, int enPassant){

};

move_status Pawn::makeMove(Figure** table, std::string move){

};


GameSession::GameSession(int whitePlayerId, int blackPlayerId, std::string FEN ){

};

return_after_move GameSession::makeMove(std::string move){

};

GameSession::~GameSession(){

};

Figure** FEN_parser(std::string FEN){

};