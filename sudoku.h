#ifndef SUDOKU_H
#define SUDOKU_H

#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <iterator>


class Sudoku
{
private:
    const static unsigned int Nsize = 9;
    const static unsigned int sqrtN = 3;
    int Nholes;
    int Ntotal;
    int grid[Nsize][Nsize] = {0};
    int gridWithHoles[Nsize][Nsize] = {0};

    // Obscure way to get random numbers
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> randomIntDistribution{1, 9};

public:
    Sudoku(int Nholes = 45);
    void fillBoard();
    void fillBox(int row, int col);
    int getRandom();

    void fillDiagonal();

    void fillRemaining();

    void createHoles();

    void printBoard();
    void printSolution();

    bool checkBox(int board[Nsize][Nsize], int row, int col, int num);
    bool checkCol(int board[Nsize][Nsize], int col, int num);
    bool checkRow(int board[Nsize][Nsize], int row, int num);
    bool checkAll(int board[Nsize][Nsize], int row, int col, int num);

    bool checkEmpty(int board[Nsize][Nsize], int& row, int& col);
    bool solve(int board[Nsize][Nsize]);
    bool solveHoles();
};

#endif