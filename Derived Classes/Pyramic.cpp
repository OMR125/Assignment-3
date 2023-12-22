#include <iostream>
#include"BoardGame_Classes.hpp"
#include <iomanip>
using namespace std;
Pyramic::Pyramic() {
    n_rows =3; n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}
bool Pyramic::update_board(int x, int y, char mark) {
    if ((!((x==0&&y==0) || (x==0&&y==1) || (x==0&&y==3) || (x==0 && y==4) || (x==1&&y==0) || (x==1&&y==4))) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}
void Pyramic::display_board() {
    for (int i: {0,1,2}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4}) {
            if (!((i==0&&j==0) || (i==0&&j==1) || (i==0&&j==3) || (i==0 && j==4) || (i==1&&j==0) || (i==1&&j==4))){
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << board [i][j] << " |";
            }
            else
            {
                cout<<"        ";
            }
        }
        cout << "\n----------------------------------------------------------";
    }
    cout << endl;
}
bool check(char a,char b,char c)
{
    return (a==b&&b==c&&(c=='X'||c=='O'));
}
bool Pyramic::is_winner() {
    char diag_win[2];
    bool raw[4],col[1];
    diag_win[0] = board[0][2] & board[1][1] & board[2][0];
    diag_win[1] = board[0][2] & board[1][3] & board[2][4];
    raw[0] = check(board[1][1],board[1][2],board[1][3]);
    col[0] = check(board[0][2],board[1][2],board[2][2]);
    for (int i = 1; i < 4 ; ++i) {
        raw[i] = check(board[2][i-1],board[2][i],board[2][i+1]);
    }
    if (col[0])return true;
    for (int i = 0; i < 4; ++i) {
        if (raw[i])return true;
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[2][4]))
    {return true;}
    return false;
}
bool Pyramic::is_draw() {
    return (n_moves == 9 && !is_winner());
}
bool Pyramic::game_is_over() {
    return n_moves >= 9;
}