#include "sudoku.h"

int main() { 
    auto start = std::chrono::high_resolution_clock::now();

    Sudoku sudoku;
    sudoku.printBoard();

    // if (sudoku.solveHoles()){
    //     std::cout << "Solved solution succes:" << std::endl;
    //     sudoku.printBoard();
    // }

    sudoku.printSolution();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    std::cout << "Time it took: " << duration << " ms" << std::endl;
}