#pragma once

#include <stdlib.h>
#include <string>

enum figure_color{
    WHITE,
    BLACK
};

enum move_status{
    MOVE_OK,
    MOVE_ERROR
};

class Figure // имя класса
{
    public: 
    figure_color color;
    std::string name;
    int isDead;
    Figure();
    virtual move_status makeMove(Figure** table, std::string move);
    void set_name(std::string name);
    void set_color(figure_color color);
};

class King : public Figure
{
public:
    King(figure_color color);
    int isCheked;
    int moved;
    int mateCheck(Figure** table);
    int checkMateCheck(Figure** table);
    move_status makeMove(Figure** table, std::string move); 
};

class Queen : public Figure
{
public:
    int wasPawn;
    Queen(figure_color color, int wasPawn);
    move_status makeMove(Figure** table, std::string move); 

};

class Bishop : public Figure
{
public:
    int wasPawn;
    Bishop(figure_color color, int wasPawn);
    move_status makeMove(Figure** table, std::string move); 
};

class Knight : public Figure
{
public:
    int wasPawn;
    Knight(figure_color color, int wasPawn);
    move_status makeMove(Figure** table, std::string move); 
};

class Rock : public Figure
{
public:
    int wasPawn;
    Rock(figure_color color, int wasPawn);
    move_status makeMove(Figure** table, std::string move); 
};

class Pawn : public Figure
{
public:
    int enPassant;
    Pawn(figure_color color, int enPassant);
    move_status makeMove(Figure** table, std::string move); 
};

enum game_result{
    WhiteWinCheckmate,
    BlackWinCheckmate,
    WhiteWinTime,
    BlackWinTime,
    Draw,
    WhiteLeave,
    BlackLeave,
    NotBeginned
};

struct return_after_move
{
    move_status moveStatus;
    Figure** table;
};

class GameSession{
    public:
    int id;
    std::string moveHistory;
    int whitePlayerId;
    int blackPlayerId;
    time_t white_timer;
    time_t black_timer;
    Figure** whiteDeadFigures;
    Figure** blackDeadFigures;
    Figure** table;
    int ended;
    int beggined;
    figure_color turn;
    game_result gameResult;
    GameSession(int whitePlayerId, int blackPlayerId, std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    return_after_move makeMove(std::string move);
    void setUp(std::string FEN);
    ~GameSession();
};

Figure** FEN_parser(std::string FEN);