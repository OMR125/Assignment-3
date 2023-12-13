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
        return n_moves == 36;
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

    bool game_is_over() {
        return n_moves >= 36;
    }


};

class ConnectFour_Player : public Player {
public:
    ConnectFour_Player(char symbol1, string name) : Player(symbol1) {
        this->name = name;
        this->symbol = symbol;
    }
    void get_move(int &x, int &y) override{
        int z;
        cout << "Enter Column number " << name << "\n";
        cin >> z;
        y = z;
    }
};
class Random_Player:public Player{
public:
    Random_Player(char symbol):Player(symbol){
        name = "Computer";
        this->symbol = symbol;
    }
    void get_move(int &x, int &y) override{
        y = 5;
    }
};
class ConnectFour_GameManager{
private:
    Board* Board_ptr;
    Player* players[2];
public:
    void run() {
        Board_ptr = new ConnectFour_Board();
        string name;
        cout << "Enter Player 1 name:\n";
        cin >> name;
        bool real = 1;
        players[0] = new ConnectFour_Player('X',name);
        cout << "Enter Player 2 name (Press Enter to face a computer):\n";
        cin >> name;
        if (name == "")
            players[1] = new Random_Player('O') , real = 0;
        else
            players[1] = new ConnectFour_Player('O',name);
        bool turn = 0;
        while (!Board_ptr->game_is_over()) {
            int X,Y;
            if(!real){
                players[turn]->get_move(X,Y);
            }else{
                Board_ptr->display_board();
                players[turn]->get_move(X,Y);
                while(!Board_ptr->update_board(-1, Y, players[turn]->get_symbol())){
                    players[turn]->get_move(X,Y);
                }
                if (Board_ptr->is_winner()) {
                    cout << (players[turn]->to_string()) << " Has Won" << "\n";
                    Board_ptr->display_board();
                    break;
                }
            }
            turn ^= 1;
        }
        if (Board_ptr->is_draw())
            cout << "The Game is a Draw\n";
    }

};
#endif //CONNECTFOUR_FOUR_IN_A_ROW_H
