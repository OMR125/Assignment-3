#include <iostream>
#include "BoardGame_Classes.hpp"
#include <random>
#include <iomanip>

using namespace std;

bool TIC_TAC_TOE_Board::is_valid(int xx, int yy) {
    return xx >= 0 && xx < n_rows && yy >= 0 && yy < n_cols;
}

int TIC_TAC_TOE_Board::count_valid(char c) {
    n_valid = 0;
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            int nr = 1, nd = 1, ndi1 = 1, ndi2 = 1;
            if (board[i][j] == c) {
                for (int k = 1; k <= 2; ++k) {
                    if (is_valid(i, j + k) && board[i][j + k] == c) {
                        nr++;
                    }
                }
                if (nr == 3) { n_valid++; }
                for (int k = 1; k <= 2; ++k) {
                    if (is_valid(i + k, j) && board[i + k][j] == c) {
                        nd++;
                    }
                }
                if (nd == 3) { n_valid++; }
                for (int k = 1; k <= 2; ++k) {
                    if (is_valid(i + k, j + k) && board[i + k][j + k] == c) {
                        ndi1++;
                    }
                }
                if (ndi1 == 3) { n_valid++; }

                for (int k = 1; k <= 2; ++k) {
                    if (is_valid(i + k, j - k) && board[i + k][j - k] == c) {
                        ndi2++;
                    }
                }
                if (ndi2 == 3) { n_valid++; }
            }
        }
    }
    return n_valid;
}

bool TIC_TAC_TOE_Board::is_draw() {
    if (count_valid('X') == count_valid('O'))
        return true;
    else
        return false;
}

bool TIC_TAC_TOE_Board::is_winner() {
    int nx = count_valid('X'), ny = count_valid('O');
    if (nx > ny) {
        return true;
    } else
        return false;
}

bool TIC_TAC_TOE_Board::update_board(int x, int y, char mark) {
    if (!(x < 0 || x > 4 || y < 0 || y > 4) && (board[x][y] == 0)) {
        board[x][y] = mark;
        n_moves++;
        return true;
    } else
        return false;
}

void TIC_TAC_TOE_Board::display_board() {
    for (int i = 0; i < n_rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < n_cols; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

TIC_TAC_TOE_Board::TIC_TAC_TOE_Board() {
    n_rows = n_cols = 5;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

TIC_TAC_TOE_Board::~TIC_TAC_TOE_Board() {
    for (int i = 0; i < n_rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

bool TIC_TAC_TOE_Board::game_is_over() {
    return (n_moves >= 24);
}
