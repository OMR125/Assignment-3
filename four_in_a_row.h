#ifndef CONNECTFOUR_FOUR_IN_A_ROW_H
#define CONNECTFOUR_FOUR_IN_A_ROW_H

#include <string>
#include "BoardGame_Classes.hpp"

using namespace std;

class ConnectFour_Board : public Board {
public:
    ConnectFour_Board() {
        n_cols = 7;
        n_rows = 6;
        board = new char *[n_rows];
        for (int i = 0; i < n_rows; i++) {
            board[i] = new char[n_cols];
            for (int j = 0; j < n_cols; j++)
                board[i][j] = '.';
        }

    }

    ConnectFour_Board(char **x) {
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

    bool update_board(int x, int y, char symbol) {
        for (int i = n_rows - 1; ~i; i--) {
            if (board[i][y - 1] == '.') {
                board[i][y - 1] = symbol;
                n_moves++;
                return 1;
            }
        }
        return 0;
    }

    bool is_winner() {
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

    bool is_draw() {
        return n_moves == 42;
    }

    void display_board() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|\n";
        }
        for (int i = 1; i <= 7; i++)
            cout << "  " << i << " \n"[i == 7];
    }

    char **get_board() {
        return board;
    }

    bool game_is_over() {
        return n_moves >= 42;
    }


};

class ConnectFour_Player : public Player {
public:
    ConnectFour_Player(char symbol1, string name) : Player(symbol1) {
        this->name = name;
        this->symbol = symbol;
    }

    void get_move(int &x, int &y) override {
        int z;
        cout << "Enter Column number " << name << "\n";
        cin >> z;
        y = z;
    }
};

class Random_Player : public Player {
private:
    int difficulty;
public:
    Random_Player(char sym, int dif) : Player(sym) {
        difficulty = dif;
        name = "Computer";
        symbol = sym;
    }

    void get_move(int &y, char **board) {
        y = minimax(board, difficulty, 1).first;
    }

    int get_score(char **board) {
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

    vector<int> valid_moves(char **board) {
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

    pair<int, int> minimax(char **board, int depth, bool turn) {
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
                int score = minimax(x, depth - 1, 0).second;
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
                int score = minimax(x, depth - 1, 1).second;
                if (score < val) {
                    val = score;
                    column = col;
                }
            }
            return {column, val};
        }
    }
};

class ConnectFour_GameManager {
private:
    Board *Board_ptr;
    Player *players[2];
public:
    void run() {
        Board_ptr = new ConnectFour_Board();
        string name;
        cout << "Enter Player 1 name:\n";
        cin >> name;
        bool real = 1;
        players[0] = new ConnectFour_Player('X', name);
        cout << "Enter Player 2 name (Press 0 to face a computer):\n";
        cin >> name;
        if (name == "0") {
            int dif;
            cout << "Pick the difficulty level from 1 to 6 (easy to hard):\n";
            cin >> dif;
            while (dif < 1 || dif > 6) {
                cout << "Pick a number from 1 to 6!!\n";
                cin >> dif;
            }
            players[1] = new Random_Player('O', dif), real = 0;
        } else
            players[1] = new ConnectFour_Player('O', name);
        bool turn = 0;
        while (!Board_ptr->game_is_over()) {
            int X, Y;
            if (turn && !real) {
                ConnectFour_Board *ptr = dynamic_cast<ConnectFour_Board *>(Board_ptr);
                char **b = ptr->get_board();
                Random_Player *p = dynamic_cast<Random_Player *>(players[turn]);
                p->get_move(Y, b);
                Y++;
                Board_ptr->update_board(-1, Y, players[turn]->get_symbol());
            } else {
                Board_ptr->display_board();
                players[turn]->get_move(X, Y);
                while (!Board_ptr->update_board(-1, Y, players[turn]->get_symbol())) {
                    players[turn]->get_move(X, Y);
                }
            }
            if (Board_ptr->is_winner()) {
                cout << (players[turn]->to_string()) << " Has Won" << "\n";
                Board_ptr->display_board();
                break;
            }
            turn ^= 1;
        }
        if (Board_ptr->is_draw()) {
            Board_ptr->display_board();
            cout << "The Game is a Draw\n";
        }
    }

};

#endif //CONNECTFOUR_FOUR_IN_A_ROW_H
