#ifndef BOARD
#define BOARD
#include <string>

class Board {
protected:
    char** arr;
    int n;
    int m;
public:
    Board(int rows, int cols);
    virtual ~Board();
    virtual void print() const;
    virtual void set(int row, int col, char symbol);
    virtual char get(int row, int col) const;
    virtual std::string serialize() const;
    virtual void deserialize(const std::string& serialized);
    virtual void saveBoard(const std::string& filename) const;
    virtual void loadboard(const std::string& filename);
};

#endif