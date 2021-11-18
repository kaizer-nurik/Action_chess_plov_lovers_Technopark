#include <gtest/gtest.h>

#include "string"
#include "GameLogic.h"
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