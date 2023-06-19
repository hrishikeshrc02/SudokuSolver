#include <iostream>
#include <vector>
#include <random>
using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number is already present in a row
bool isSafeInRow(const vector<vector<int>>& grid, int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is already present in a column
bool isSafeInCol(const vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is already present in a 3x3 box
bool isSafeInBox(const vector<vector<int>>& grid, int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + boxStartRow][col + boxStartCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if it's safe to place a number at a given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    return isSafeInRow(grid, row, num) &&
           isSafeInCol(grid, col, num) &&
           isSafeInBox(grid, row - row % 3, col - col % 3, num);
}

// Function to find an empty cell in the grid
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    if (!findEmptyCell(grid, row, col)) {
        return true; // No empty cells, puzzle solved
    }
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true; // Puzzle solved
            }
            grid[row][col] = 0; // Undo the choice and try another number
        }
    }
    return false; // Puzzle cannot be solved
}

// Function to generate a Sudoku puzzle
void generateSudoku(vector<vector<int>>& grid) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 9);
    grid.resize(N, vector<int>(N, 0));
    solveSudoku(grid);
    int numToRemove = 40; // Number of cells to remove (adjust as desired)
    while (numToRemove > 0) {
        int row = dis(gen) % 9;
        int col = dis(gen) % 9;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            numToRemove--;
        }
    }
}

int main() {
    int choice;
    cout << "Choose an option:\n";
    cout << "1. Generate a Sudoku puzzle\n";
    cout << "2. Solve a Sudoku puzzle\n";
    cin >> choice;

    vector<vector<int>> grid(N, vector<int>(N, 0));

    switch (choice) {
        case 1:
            generateSudoku(grid);
            cout << "Generated Sudoku puzzle:\n";
            printGrid(grid);
            break;
        case 2:
            cout << "Enter the Sudoku puzzle row by row(use 0 for empty cells):\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cin >> grid[i][j];
                }
            }
            if (solveSudoku(grid)) {
                cout << "Solved Sudoku puzzle:\n";
                printGrid(grid);
            } else {
                cout << "No solution exists for the given Sudoku puzzle.\n";
            }
            break;
        default:
            cout << "Invalid choice. Exiting...\n";
            break;
    }

    return 0;
}
