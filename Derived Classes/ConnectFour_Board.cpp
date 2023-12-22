#include <iostream>
#include "BoardGame_Classes.hpp"

using namespace std;

ConnectFour_Board::ConnectFour_Board() {
    n_cols = 7;
    n_rows = 6;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = '.';
    }

}

ConnectFour_Board::ConnectFour_Board(char **x) {
    n_cols = 7;
    n_rows = 6;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++) {
            board[i][j] = x[i][j];
            n_moves += x[i][j] != '.';
        }
    }
}

bool ConnectFour_Board::update_board(int x, int y, char symbol) {
    if (y < 1 || y > 7)
        return 0;
    for (int i = n_rows - 1; ~i; i--) {
        if (board[i][y - 1] == '.') {
            board[i][y - 1] = symbol;
            n_moves++;
            return 1;
        }
    }
    return 0;
}

bool ConnectFour_Board::is_winner() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == '.')
                continue;
            if (i >= 3 && board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] &&
                board[i - 2][j] == board[i - 3][j])
                return 1;
            if (i >= 3 && j >= 3 && board[i][j] == board[i - 1][j - 1] &&
                board[i - 1][j - 1] == board[i - 2][j - 2] && board[i - 2][j - 2] == board[i - 3][j - 3])
                return 1;
            if (j < 4 && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] &&
                board[i][j + 2] == board[i][j + 3])
                return 1;
            if (i >= 3 && j < 4 && board[i][j] == board[i - 1][j + 1] &&
                board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3])
                return 1;
        }
    }
    return 0;
}

bool ConnectFour_Board::is_draw() {
    return n_moves == 42;
}

void ConnectFour_Board::display_board() {
    cout << "\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }
    for (int i = 1; i <= 7; i++)
        cout << "  " << i << " \n"[i == 7];
}

char **ConnectFour_Board::get_board() {
    return board;
}

bool ConnectFour_Board::game_is_over() {
    return n_moves >= 42;
}
