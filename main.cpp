#include "sudoku.h"

using namespace std;

int main(int argc, char *argv[]) { 
    auto start = chrono::high_resolution_clock::now();

    int Nholes;

    if (argc == 1){
        Nholes = 45;
    } else if (argc == 2) {
        Nholes = atoi(argv[1]);
    } else {
        cout << "Usage: ./main Nholes. If you do not specify Nholes the default = 45 holes" << endl;
        return 1;
    }

    cout << "Creating board with " << Nholes << " holes." << endl;

    Sudoku sudoku(Nholes);
    sudoku.printBoard();

    // if (sudoku.solveHoles()){
    //     cout << "Solved solution succes:" << endl;
    //     sudoku.printBoard();
    // }

    sudoku.printSolution();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << "Time it took: " << duration << " ms" << endl;
    return 0;
}