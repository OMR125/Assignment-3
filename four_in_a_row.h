#ifndef CONNECTFOUR_FOUR_IN_A_ROW_H
#define CONNECTFOUR_FOUR_IN_A_ROW_H

#include "Board.h"

using namespace std;

// i want to create a player class . or might forget about it
// but just make sure to create the smart computer player
class four_in_a_row : public Board {
public:
    four_in_a_row() {
        n_cols = 7;
        n_rows = 6;
        board.resize(n_rows);
        for (auto &v: board) {
            v.resize(n_cols, '.');
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
                if (i >= 3 && board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] && board[i - 2][j] == board[i - 3][j])
                    return 1;
                if (i >= 3 && j >= 3 && board[i][j] == board[i - 1][j - 1] && board[i - 1][j - 1] == board[i - 2][j - 2] && board[i - 2][j - 2] == board[i - 3][j - 3])
                    return 1;
                if (j < 4 && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3])
                    return 1;
                if (i >= 3 && j < 4 && board[i][j] == board[i - 1][j + 1] &&board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3])
                    return 1;
            }
        }
        return 0;
    }

    bool is_draw() {
        return n_moves == 36;
    }

    void display_board() {
        for (const auto &row: board) {
            for (const auto &cell: row) {
                cout << "| " << cell << " ";
            }
            cout << "|\n";
        }
        for (int i = 1; i <= 7; i++)
            cout << "  " << i << " \n"[i == 7];
    }

    bool game_is_over() {
        return n_moves >= 36;
    }

    void run() {
        string player1, player2;
        cout << "Enter Player 1 name: \n";
        cin >> player1;
        cout << "Enter Player 2 name (Press Enter to face a computer):\n";
        cin >> player2;
        if (player2 == "") player2 = "Computer";
        bool turn = 1;
        while (!game_is_over()) {
            display_board();
            cout << "Enter a Column Number " << (turn ? player1 : player2) << ": \n";
            int Y;
            if (!turn && player2 == "Computer") {
                Y = 1;
            } else cin >> Y;
            update_board(-1, Y, (turn ? 'X' : 'O'));
            if (is_winner()) {
                cout << (turn ? player1 : player2) << " Has Won" << "\n";
                display_board();
                break;
            }
            turn ^= 1;
        }
        if (is_draw())
            cout << "The Game is a Draw\n";
    }

};

#endif //CONNECTFOUR_FOUR_IN_A_ROW_H
