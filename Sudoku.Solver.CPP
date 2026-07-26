#include <iostream>

// Define the dimensions of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid with clean visual formatting
void printGrid(int grid[N][N]) {
    for (int r = 0; r < N; ++r) {
        if (r % 3 == 0 && r != 0) {
            std::cout << "------+-------+------\n";
        }
        for (int c = 0; c < N; ++c) {
            if (c % 3 == 0 && c != 0) {
                std::cout << "| ";
            }
            if (grid[r][c] == 0) {
                std::cout << ". ";
            } else {
                std::cout << grid[r][c] << " ";
            }
        }
        std::cout << "\n";
    }
}

// Function to check if placing 'num' at grid[row][col] is valid
bool isValid(int grid[N][N], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num)
            return false;
    }

    // Check the column
    for (int x = 0; x < N; ++x) {
        if (grid[x][col] == num)
            return false;
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Recursive backtracking algorithm to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N]) {
    int row = -1;
    int col = -1;
    bool isEmpty = false;

    // Find the first empty cell (represented by 0)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    // Base case: If no empty cell is found, the puzzle is solved
    if (!isEmpty)
        return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    // Standard 2D array representation
    int grid[N][N] = {0};

    std::cout << "===================================================\n";
    std::cout << "               SUDOKU SOLVER (C++)                 \n";
    std::cout << "===================================================\n";
    std::cout << "Enter your puzzle row by row (9 numbers per row).\n";
    std::cout << "Use spaces between numbers, and '0' for empty spaces:\n\n";

    // Input the Sudoku puzzle
    for (int i = 0; i < N; ++i) {
        std::cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < N; ++j) {
            if (!(std::cin >> grid[i][j])) {
                std::cout << "\nError: Invalid input detected! Please enter digits only.\n";
                return 1;
            }
        }
    }

    std::cout << "\n---------------------\n";
    std::cout << "Your Inputted Puzzle:\n";
    printGrid(grid);
    std::cout << "---------------------\n\n";

    // Solve and display the result
    if (solveSudoku(grid)) {
        std::cout << "Solved Sudoku Puzzle:\n";
        printGrid(grid);
    } else {
        std::cout << "No valid solution exists for the provided puzzle constraints.\n";
    }

    return 0;
}
