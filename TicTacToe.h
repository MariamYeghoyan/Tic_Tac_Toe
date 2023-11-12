#ifndef TICTACTOE
#define TICTACTOE
#include "Board.h"

class TicTacToe : public Board {
public:
    TicTacToe();
    void print() const override;
    void set(int row, int col, char symbol) override;
    bool checkwinner(char player) const;
};

#endif