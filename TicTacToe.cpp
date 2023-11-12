#include "TicTacToe.h"
#include <iostream>
TicTacToe::TicTacToe() : Board(3, 3) {}

void TicTacToe::print() const {
    std::cout << "+---+---+---+" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << '|';
        for (int j = 0; j < 3; ++j) {
            std::cout << ' ' << arr[i][j] << ' ' << '|';
        }
        std::cout << std::endl;
        std::cout << "+---+---+---+" << std::endl;
    }
}

void TicTacToe::set(int row, int col, char symbol) {
    if (get(row, col) == ' ' && (symbol == 'x' || symbol == 'o')) {
        arr[row][col] = symbol;
    }
}

bool TicTacToe::checkwinner(char player) const {
    for (int i = 0; i < 3; ++i) {
        if (arr[i][0] == player && arr[i][1] == player && arr[i][2] == player)
            return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (arr[0][i] == player && arr[1][i] == player && arr[2][i] == player)
            return true;
    }
    if (arr[0][0] == player && arr[1][1] == player && arr[2][2] == player)
        return true;

    if (arr[0][2] == player && arr[1][1] == player && arr[2][0] == player)
        return true;

    return false;
}
