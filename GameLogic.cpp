
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

void Figure::set_name(std::string name){

};

void Figure::set_color(figure_color color){

};


King::King(figure_color color){
    King::isDead = 0;
    King::name = "King";
    King::color = color;
    King::moved = 0;
    King::isCheked = 0;    
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


GameSession::GameSession(int id,int whitePlayerId, int blackPlayerId, std::string FEN ){
    GameSession::id = id;
    GameSession::moveHistory = "";
    GameSession::whitePlayerId = whitePlayerId;
    GameSession::blackPlayerId = blackPlayerId;
    GameSession::white_timer = 0;
    GameSession::black_timer = 0;
    GameSession::whiteDeadFigures.clear();
    GameSession::blackDeadFigures.clear();
    GameSession::table = new Figure*[64];
    GameSession::table = FEN_parser(START_POSITION);
    GameSession::ended = 0;
    GameSession::beggined = 1;
    GameSession::turn = WHITE;
    GameSession::gameResult = InGame;
};

return_after_move GameSession::makeMove(std::string move){

};

GameSession::~GameSession(){

};

int coord_to_index(const char letter,const char number){
    int coord = (letter - 'A') + number*8; 
    return coord;
}
void set_enpassant(const Figure** ttable,const char letter,const char number){
    int index = coords_to_index(letter, number);
    if data[c]
}

Figure** FEN_parser(std::string FEN){ //TODO: добавить ошибки
    
    
    Figure** ttable = new Figure*[64]; //temp_table
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
                ttable[cursor] = new King(BLACK);
                Black_king = ttable[cursor];
                cursor++;
            }
            break;
        case 'K':
            if (White_king == NULL){
                ttable[cursor] = new King(WHITE);
                White_king = ttable[cursor];
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
        while (data[data_cursor] != ' '){ //считываем нотацию Рокировок
        set_enpassant(ttable,data[data_cursor],data[data_cursor+1]);
        data_cursor+=2;
    }
    }
    data_cursor++;
};