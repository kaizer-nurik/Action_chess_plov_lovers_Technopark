#include <gtest/gtest.h>
#include <iostream>
#include "string"
#include "GameLogic.h"

/*
class FooTest :
    public testing::TestWithParam<const char*> {
};

struct test_suite{
    std::string question;
    Figure** table;
};

class ChessTest : public::testing::TestWithParam<test_suite>{};
TEST_P(ChessTest, FEN_parser_test) { // тестируем парсер FEN
    test_suite suite = GetParam();
    Figure** board = FEN_parser(suite.question);
    for(int i = 0;i<64;i++){
        EXPECT_EQ(board[i],suite.table[i]);
    };
    delete board;
    delete suite.table;
};

//Тестируем make move фигур

//тестируем спец ходы (en passant, рокировка, превращение)

//Тестируем поведение GameSession

//Тестируем несанкционированный доступ и нелегальные ходы

//Тестируем шах, шах и мат, окончание игры


Figure* case1[64];
test_suite case11 = {"",case1};
INSTANTIATE_TEST_CASE_P(All, ChessTest,::testing::Values(case11,case11));
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

*/
void print_fen(std::string fen){
    for(int i= 0;i<fen.length();i++){
        switch (fen.at(i))
        {
        case '1'...'8':
            for(int j=1;j<=fen.at(i)-'0';j++){
                std::cout<<'.';
            }
            break;
        case '/':
            std::cout<<std::endl;
            break;
        default:
            std::cout<<fen.at(i);
            break;
        }
    }
}
int main(){
    std::string id = "1";
    std::string id1 = "2";
    std::string id2 = "3";
    GameSession game = GameSession(id, id1,id2);
    //std::cout<<game.table.get_table()[50]->FEN_name << std::endl;
    std::string outp = game.get_FEN();
    print_fen(outp);
    //std::cout<<outp<<'\n'<<std::endl;

    std::string move;
    std::cin>>move;
    return_after_move res = game.makeMove(move,id1);
    
    //std::cout<<'\n'<<res.move_from<<' '<<res.move_to<<std::endl;
    switch(res.moveStatus){
        case MOVE_OK:
            std::cout<<'\n'<<"ok"<<std::endl;
            break;
        case MOVE_ERROR:
            std::cout<<'\n'<<"error"<<std::endl;
            break;
        case MOVE_EAT:
            std::cout<<'\n'<<"eat"<<std::endl;
            break;
        case MOVE_CAST:
            std::cout<<'\n'<<"CAST"<<std::endl;
            break;
    }
    print_fen(res.table_fen);
    return 0;
}