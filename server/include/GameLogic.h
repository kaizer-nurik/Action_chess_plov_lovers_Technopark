#pragma once //TODO: добавить конструкторы копирования

#include <stdlib.h>
#include <string>
#include <vector>

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"
#define BOARD_SIZE 64

enum figure_color
{
    WHITE = 1,
    BLACK = -1
};

enum move_status
{
    MOVE_OK,
    MOVE_EAT,
    MOVE_CAST,
    MOVE_CHECK_WHITE,
    MOVE_CHECKMATE_WHITE,
    MOVE_CHECK_BLACK,
    MOVE_CHECKMATE_BLACK,
    MOVE_DRAW,
    MOVE_ERROR,
    MOVE_ENPASSANT,
    MOVE_SET_ENPASSANT,
    WHITE_LEAVE,
    BLACK_LEAVE
};

struct coords
{
    std::string str;
    int index;
    int x;
    int y;
};
class Figure // имя класса
{
public:
    figure_color color;
    std::string name;
    std::string FEN_name;
    int isDead;
    Figure(const Figure &figure) = default;
    Figure() = default;
    ~Figure()= default;
};

class King : public Figure
{
public:
    King(figure_color color);
    int isCheked = 0;
    int moved = 0;
    int cast_k = 0; // рокировка со стороны короля
    int cast_q = 0; // рокировка со стороны ферзя
    int mateCheck(Figure **table);
    int checkMateCheck(Figure **table);
    
};

class Queen : public Figure
{
public:
    int wasPawn = 0;
    Queen(figure_color color);
    
};

class Bishop : public Figure
{
public:
    int wasPawn = 0;
    Bishop(figure_color color);
    
};

class Knight : public Figure
{
public:
    int wasPawn = 0;
    Knight(figure_color color);
    
};

class Rock : public Figure
{
public:
    int wasPawn = 0;
    Rock(figure_color color);
    
};

class Pawn : public Figure
{
public:
    bool enPassant = false;
    Pawn(figure_color color);
    
};


struct return_after_move
{
    move_status moveStatus;
    std::string table_fen;
    int move_from;
    int move_to;
};

class ChessTable
{
public:
    ChessTable();
    ChessTable(const ChessTable &mainTable);
    Figure **get_table() const;
    void set_table(Figure **input_table);
    void kill_figure(int index);
    move_status move_figure(int from, int to);
    void make_move(int from, int to);
    move_status is_legal(int from, int to);
    bool Check_mate(int King_ind);
    void set_enpassant(char letter, char number);
    bool check_en_passant(int from, int to);
    bool Rock_move(figure_color color, coords from, coords to);
    bool Bishop_move(figure_color color, coords from, coords to);
    bool Queen_move(figure_color color, coords from, coords to);
    bool get_hit_table(figure_color color, coords to);
    bool check_cast(Figure *fig_actor, figure_color enemy, coords from, coords to);
    bool check_draw(figure_color enemy_color);
    Figure *get_figure(int index);
    ~ChessTable();
    int Black_king_ind = -1;
    int White_king_ind = -1;
    void FEN_parser(std::string FEN);
     std::string  get_FEN() const;
    figure_color turn;

private:
    void delete_table();
    Figure **table;
    std::string whiteDeadFigures = "";
    std::string blackDeadFigures = "";
    std::vector<int> black_enpassant;
    std::vector<int> white_enpassant;
};

class GameSession
{
public:
    const std::string id;
    std::string moveHistory = "";
    const std::string whitePlayerId;
    const std::string blackPlayerId;
    time_t white_timer = 0;
    time_t black_timer = 0;
    int turns = 0;
    ChessTable table;
    int ended = 0;
    int beggined = 1;
    
    move_status gameResult = MOVE_OK;
    GameSession(const std::string &id, const std::string &whitePlayerId, const std::string &blackPlayerId, const std::string &FEN = START_POSITION);
    return_after_move makeMove(std::string move, const std::string &player_id);
    bool end_game(move_status why);
    ~GameSession();

private:
    void create_error_response(return_after_move &result);
};
coords data_to_coords(char letter, char number);
int str_to_index(char letter, char number);
coords data_to_coords(int index);
coords data_to_coords(std::string input);
std::string index_to_str(const int index);
