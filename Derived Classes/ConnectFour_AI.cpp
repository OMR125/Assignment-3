#include "BoardGame_Classes.hpp"

ConnectFour_AI::ConnectFour_AI(char sym, int dif) : Player(sym) {
    difficulty = dif;
    name = "Computer";
    symbol = sym;
}

vector<int> ConnectFour_AI::valid_moves(char **board) {
    vector<int> v;
    for (int j = 0; j < 7; j++) {
        for (int i = 5; ~i; i--) {
            if (board[i][j] == '.') {
                v.push_back(j);
                break;
            }
        }
    }
    return v;
}

void ConnectFour_AI::get_move(int &y, char **board) {
    y = minimax(board, difficulty, true).first;
}

pair<int, int> ConnectFour_AI::minimax(char **board, int depth, bool turn) {
    Board *ptr = new ConnectFour_Board(board);
    if (ptr->is_draw())
        return {0, 0};
    if (depth == 0) {
        return {0, get_score(board)};
    }
    vector<int> valid = valid_moves(board);
    int column = valid[0];
    if (turn) {
        int val = INT_MIN;
        for (const auto &col: valid) {
            int row;
            for (int i = 5; ~i; i--)
                if (board[i][col] == '.') {
                    row = i;
                    break;
                }
            char **x = new char *[6];

            for (int i = 0; i < 6; i++) {
                x[i] = new char[7];
                for (int j = 0; j < 7; j++) {
                    x[i][j] = board[i][j];
                }
            }
            x[row][col] = symbol;
            int score = minimax(x, depth - 1, false).second;
            if (score > val) {
                val = score;
                column = col;
            }
        }
        return {column, val};
    } else {
        int val = INT_MAX;
        for (const auto &col: valid) {
            int row;
            for (int i = 5; ~i; i--)
                if (board[i][col] == '.') {
                    row = i;
                    break;
                }
            char **x = new char *[6];
            for (int i = 0; i < 6; i++) {
                x[i] = new char[7];
                for (int j = 0; j < 7; j++) {
                    x[i][j] = board[i][j];
                }
            }
            x[row][col] = (symbol == 'X' ? 'O' : 'X');
            int score = minimax(x, depth - 1, true).second;
            if (score < val) {
                val = score;
                column = col;
            }
        }
        return {column, val};
    }
}

int ConnectFour_AI::get_score(char **board) {
    int score = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == '.')
                continue;
            if (i >= 3 && board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] &&
                board[i - 2][j] == board[i - 3][j])
                score += board[i][j] == symbol ? 99999 : -99999;
            if (i >= 3 && j >= 3 && board[i][j] == board[i - 1][j - 1] &&
                board[i - 1][j - 1] == board[i - 2][j - 2] && board[i - 2][j - 2] == board[i - 3][j - 3])
                score += board[i][j] == symbol ? 99999 : -99999;
            if (j < 4 && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] &&
                board[i][j + 2] == board[i][j + 3])
                score += board[i][j] == symbol ? 99999 : -99999;
            if (i >= 3 && j < 4 && board[i][j] == board[i - 1][j + 1] &&
                board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3])
                score += board[i][j] == symbol ? 99999 : -99999;
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == '.')
                continue;
            if (i >= 3 && board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] &&
                '.' == board[i - 3][j])
                score += board[i][j] == symbol ? 99 : -999;
            if (i >= 3 && j >= 3 && board[i][j] == board[i - 1][j - 1] &&
                board[i - 1][j - 1] == board[i - 2][j - 2] && '.' == board[i - 3][j - 3])
                score += board[i][j] == symbol ? 99 : -999;
            if (j < 4 && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] &&
                '.' == board[i][j + 3])
                score += board[i][j] == symbol ? 99 : -999;
            if (i >= 3 && j < 4 && board[i][j] == board[i - 1][j + 1] &&
                board[i - 1][j + 1] == board[i - 2][j + 2] && '.' == board[i - 3][j + 3])
                score += board[i][j] == symbol ? 99 : -999;
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == '.')
                continue;
            if (i >= 2 && board[i][j] == board[i - 1][j] && '.' == board[i - 2][j])
                score += board[i][j] == symbol ? 5 : 0;
            if (i >= 2 && j >= 2 && board[i][j] == board[i - 1][j - 1] &&
                '.' == board[i - 2][j - 2])
                score += board[i][j] == symbol ? 5 : 0;
            if (j < 5 && board[i][j] == board[i][j + 1] && '.' == board[i][j + 2])
                score += board[i][j] == symbol ? 5 : 0;
            if (i >= 2 && j < 5 && board[i][j] == board[i - 1][j + 1] &&
                '.' == board[i - 2][j + 2])
                score += board[i][j] == symbol ? 5 : 0;
        }
    }
    return score;
}