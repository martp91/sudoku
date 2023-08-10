/* Sudoku generator MP august 2023*/

#include "sudoku.h"

using namespace std;

Sudoku::Sudoku(int Nholes) : Nholes(Nholes)
{
    fillBoard();
    createHoles();
}

void Sudoku::printBoard()
{
    cout << "Board: " << endl;
    for (int i = 0; i < Nsize; i++)
    {
        for (int j = 0; j < Nsize; j++)
        {
            cout << gridWithHoles[i][j] << " ";
        }
        cout << endl;
    }
}

void Sudoku::printSolution()
{
    cout << "Solution: " << endl;
    for (int i = 0; i < Nsize; i++)
    {
        for (int j = 0; j < Nsize; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}


void Sudoku::fillBoard()
{
    fillDiagonal();
    fillRemaining();

}

void Sudoku::fillDiagonal()
{
    for (int i = 0; i < Nsize; i += sqrtN)
    {
        fillBox(i, i);
    }
}

int Sudoku::getRandom()
{
    return randomIntDistribution(mt);
}

void Sudoku::fillBox(int row, int col)
{
    int num = 0;
    for (int i = 0; i < sqrtN; i++)
    {
        for (int j = 0; j < sqrtN; j++)
        {
            while (!checkBox(grid, row, col, num))
            {
                num = getRandom();
            }
            grid[row + i][col + j] = num;
        }
    }
}

bool Sudoku::checkBox(int board[Nsize][Nsize], int row, int col, int num)

{
    for (int i = 0; i < sqrtN; i++)
    {
        for (int j = 0; j < sqrtN; j++)
        {
            if (board[row + i][col + j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::checkCol(int board[Nsize][Nsize], int col, int num)
{
    for (int i = 0; i < Nsize; i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::checkRow(int board[Nsize][Nsize], int row, int num)
{
    for (int i = 0; i < Nsize; i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::checkAll(int board[Nsize][Nsize], int row, int col, int num)
{
    if (checkRow(board, row, num) && checkCol(board, col, num) && checkBox(board, row - row % sqrtN, col - col % sqrtN, num) && (board[row][col] == 0))
    {
        return true;
    }
    return false;
}

bool Sudoku::checkEmpty(int board[Nsize][Nsize], int &row, int &col)
{
    for (row = 0; row < Nsize; row++)
    {
        for (col = 0; col < Nsize; col++)
        {
            if (board[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::solve(int board[Nsize][Nsize])
{

    //TODO: bug is here, need to be able to solve without filling whole
    int row = 0;
    int col = 0;

    if (!checkEmpty(board, row, col))
    {
        return true;
    }

    for (int num = 1; num <= Nsize; num++)
    {
        if (checkAll(board, row, col, num))
        {
            board[row][col] = num;
            if (solve(board))
            {
                return true;
            }
            // if not solvable set to zero again and move on
            board[row][col] = 0;
        }
    }

    // not solved yet
    return false;
}

bool Sudoku::solveHoles(){
    return solve(gridWithHoles);
}

void Sudoku::fillRemaining()
{
    // fill remaining by solving board
    solve(grid);
}


void Sudoku::createHoles()

{

    //set gridWithHoles
    for (int i = 0; i < Nsize; i++) {
        for (int j = 0; j < Nsize; j++) {
            gridWithHoles[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < Nholes; i++)
    {
        while (true)
        {
            int row = getRandom() - 1;
            int col = getRandom() - 1;
            grid[row][col] = 0;


            //grid is auto filled again
            if (solve(grid))
            {
                //hole is OK, set hole in gridWithHoles
                gridWithHoles[row][col] = 0;
                break;
            }
            else
            {
                // set back original number and try again
                grid[row][col] = gridWithHoles[row][col];
            }
        }
    }
}