#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>

Board::Board(int rows, int cols) : n(rows), m(cols) {
    arr = new char*[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new char[m];
        for (int j = 0; j < m; ++j) {
            arr[i][j] = ' ';
        }
    }
}

Board::~Board(){
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}
void Board::print() const {
    std::cout << "+---+---+---+" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << '|';
        for (int j = 0; j < m; ++j) {
            std::cout << ' ' << arr[i][j] << ' ' << '|';
        }
        std::cout << std::endl;
        std::cout << "+---+---+---+" << std::endl;
    }
}

void Board::set(int row, int col, char symbol) {
    arr[row][col] = symbol;
}

char Board::get(int row, int col) const{
    return arr[row][col];
}

std::string Board::serialize() const {
    std::ostringstream serialized;
    for (int i = 0; i < n; ++i) {
        serialized << "+---+---+---+\n";
        for (int j = 0; j < m; ++j) {
            serialized << "| " << arr[i][j] << " ";
        }
        serialized << "|\n";
    }
    serialized << "+---+---+---+\n";
    return serialized.str();
}

void Board::deserialize(const std::string& serilized) {
    int index = 0;
    for (int i = 0; i < n; ++i) {
        index += 9;
        for (int j = 0; j < m; ++j) {
            index += 2;
            arr[i][j] = serilized[index++];
            index += 4;
        }
        index += 2;
    }
}

void Board::saveBoard(const std::string& filename) const {
    std::string serilizedboard = serialize();
    std::ofstream outputfile(filename);
    if (outputfile.is_open()) {
        outputfile << serilizedboard;
        outputfile.close();
        std::cout << "Board is saved." << std::endl;
    }
    else {
        std::cout << "Couldn't open the file" << std::endl;
    }
}

void Board::loadboard(const std::string& filename) {
    std::ifstream inputfile(filename);
    std::stringstream buf;
    buf << inputfile.rdbuf();
    std::string serializedboard = buf.str();
    inputfile.close();
    deserialize(serializedboard);
}