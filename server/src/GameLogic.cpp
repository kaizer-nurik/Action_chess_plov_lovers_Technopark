
#include "GameLogic.h"
#include <string>
#include <stdlib.h>
#include <vector>

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
Figure::Figure(){

};

Figure::~Figure(){

};
move_status Figure::makeMove(Figure** table, std::string move){

};




King::King(figure_color color){
    King::isDead = 0;
    King::name = "King";
    King::color = color;
};

move_status King::makeMove(Figure** table, std::string move){

};

Queen::Queen(figure_color color){
    Queen::isDead = 0;
    Queen::name = "Queen";
    Queen::color = color;
};

move_status Queen::makeMove(Figure** table, std::string move){

};

Bishop::Bishop(figure_color color){
    Bishop::isDead = 0;
    Bishop::name = "Bishop";
    Bishop::color = color;
};

move_status Bishop::makeMove(Figure** table, std::string move){

};

Knight::Knight(figure_color color){
    Knight::isDead = 0;
    Knight::name = "Knight";
    Knight::color = color;
};

move_status Knight::makeMove(Figure** table, std::string move){

};

Rock::Rock(figure_color color){
    Rock::isDead = 0;
    Rock::name = "Rock";
    Rock::color = color;
};


move_status Rock::makeMove(Figure** table, std::string move){

};

Pawn::Pawn(figure_color color){
    Pawn::isDead = 0;
    Pawn::name = "Pawn";
    Pawn::color = color;
};

move_status Pawn::makeMove(Figure** table, std::string move){

};


GameSession::GameSession(int id,int whitePlayerId, int blackPlayerId, std::string FEN = START_POSITION){
    GameSession::id = id;
    GameSession::whitePlayerId = whitePlayerId;
    GameSession::blackPlayerId = blackPlayerId;
    GameSession::FEN_parser(FEN);
};

return_after_move GameSession::makeMove(std::string move, int player_id){

};

GameSession::~GameSession(){

};

int utils::coord_to_index(const char letter,const char number){
    int coord = (letter - 'A') + number*8; 
    return coord;
}
void ChessTable::set_enpassant(const char letter,const char number){
    int index = utils::coord_to_index(letter, number);
    if((index <49) && (index >40)){
        index -= 8;
        Pawn* cur = dynamic_cast<Pawn*>(table[index]);
        if (cur != NULL){
        cur ->enPassant = true;
        }
    }

    if((index <33) && (index >24)){
        index += 8;
        Pawn* cur = dynamic_cast<Pawn*>(table[index]);
        if (cur != NULL){
        cur ->enPassant = true;
        }
    }
}

void GameSession::FEN_parser(const std::string FEN){ //TODO: добавить ошибки
    
    
    Figure** ttable = GameSession::table.get_table(); //temp_table
    bool err_flag = false;
    const char *data = FEN.c_str();
    int cursor = 56;//FEN нотация идёт от черных к белым, слева направо
    int data_cursor = 0;
    King* Black_king = NULL;
    King* White_king = NULL;

    while (data[data_cursor] != ' '){ //считываем нотацию доски
        switch (data[cursor])
        {
        case 'k':
            if (Black_king == NULL){
                Black_king = new King(BLACK);
                ttable[cursor] = Black_king;
                cursor++;
            }
            break;
        case 'K':
            if (White_king == NULL){
                White_king = new King(WHITE);
                ttable[cursor] = White_king;
                cursor++;
            }
            
            break;

        case 'q':
            ttable[cursor] = new Queen(BLACK);
            cursor++;
            break;
        case 'Q':
            ttable[cursor] = new Queen(WHITE);
            cursor++;
            break;
        
        case 'r':
            ttable[cursor] = new Rock(BLACK);
            cursor++;
            break;
        case 'R':
            ttable[cursor] = new Rock(WHITE);
            cursor++;
            break;

        case 'b':
            ttable[cursor] = new Bishop(BLACK);
            cursor++;
            break;
        case 'B':
            ttable[cursor] = new Bishop(WHITE);
            cursor++;
            break;

        case 'n':
            ttable[cursor] = new Knight(BLACK);
            cursor++;
            break;
        case 'N':
            ttable[cursor] = new Knight(WHITE);
            cursor++;
            break;

        case 'p':
            ttable[cursor] = new Pawn(BLACK);
            cursor++;
            break;
        case 'P':
            ttable[cursor] = new Pawn(WHITE);
            cursor++;
            break;
        case '1'...'8':
            cursor += data[cursor] - '0'; // преобразование из char  в int
            break;
        case '/':
            cursor -= 16;
            break;
        default:
            break;
        }
        data_cursor++;
    }

    data_cursor++;

    figure_color turn = (data[data_cursor] == 'w') ? WHITE:BLACK;

    data_cursor++;

    while (data[data_cursor] != ' '){ //считываем нотацию Рокировок
        switch (data[cursor])
        {
        case 'k':
            Black_king->cast_k = 1;
            break;
        case 'K':
            White_king->cast_k = 1;
            break;

        case 'q':
            Black_king->cast_q = 1;
            break;
        case 'Q':
            White_king->cast_q = 1;
            break;
        }
        data_cursor++;
    }

    data_cursor++;

    if (data[data_cursor] != '-'){
        data_cursor++;
        while (data[data_cursor] != ' '){ //считываем нотацию взятий на проходе
        GameSession::table.set_enpassant(data[data_cursor],data[data_cursor+1]);
        data_cursor+=2;
    }
    }
    data_cursor++;
};