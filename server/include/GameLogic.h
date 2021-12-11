#pragma once //TODO: добавить конструкторы копирования

#include <stdlib.h>
#include <string>
#include <vector>
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
    ~Figure();
    virtual move_status makeMove(Figure** table, std::string move);
};

class King : public Figure
{
public:
    King(figure_color color);
    int isCheked = 0;
    int moved = 0;
    int cast_k = 0; // рокировка со стороны короля
    int cast_q = 0; // рокировка со стороны ферзя
    int mateCheck(Figure** table);
    int checkMateCheck(Figure** table);
    move_status makeMove(Figure** table, std::string move); 
};

class Queen : public Figure
{
public:
    int wasPawn = 0;
    Queen(figure_color color);
    move_status makeMove(Figure** table, std::string move); 

};

class Bishop : public Figure
{
public:
    int wasPawn = 0;
    Bishop(figure_color color);
    move_status makeMove(Figure** table, std::string move); 
};

class Knight : public Figure
{
public:
    int wasPawn = 0;
    Knight(figure_color color);
    move_status makeMove(Figure** table, std::string move); 
};

class Rock : public Figure
{
public:
    int wasPawn = 0;
    Rock(figure_color color);
    move_status makeMove(Figure** table, std::string move); 
};

class Pawn : public Figure
{
public:
    bool enPassant = false;
    Pawn(figure_color color);
    move_status makeMove(Figure** table, std::string move); 
};

enum game_result{
    InGame,
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
    std::string table_fen;
};


class ChessTable{
    public:
    ChessTable();
    Figure** get_table();
    void set_table(Figure** input_table);
    void kill_figure(std::string coords);
    void move_figure(std::string from, std::string to);
    void set_enpassant(const char letter,const char number);
    ~ChessTable();
    private:
    Figure** table;
    std::string whiteDeadFigures;
    std::string blackDeadFigures;
};

class GameSession{
    public:
    std::string id;
    std::string moveHistory = "";
    std::string whitePlayerId;
    std::string blackPlayerId;
    time_t white_timer = 0;
    time_t black_timer = 0;

    ChessTable table;
    int ended = 0;
    int beggined = 1;
    figure_color turn;
    game_result gameResult = InGame;
    GameSession(int id,int whitePlayerId, int blackPlayerId, std::string FEN);
    return_after_move makeMove(std::string move, int player_id);
    void setUp(std::string FEN);
    std::string get_FEN(std::string FEN);
    void FEN_parser(std::string FEN);
    ~GameSession();
};

namespace utils{
    int coord_to_index(const char letter,const char number);
};