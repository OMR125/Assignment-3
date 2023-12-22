#include <iostream>
#include"BoardGame_Classes.hpp"

using namespace std;

int main() {
    int choice;
    cout << "Welcome to X-O Game :)  : \n";
    cout << "1- 3x3 Tic Tac Toe.\n";
    cout << "2- Pyramic Tic-Tac-Toe .\n";
    cout << "3- Four-in-a-row.\n";
    cout << "4- 5x5 Tic Tac Toe.\n";
    cout << "Enter Your Choice: \n";
    cin >> choice;
    switch (choice) {
        case 1: {
            Player *players[2];
            players[0] = new Player(1, 'X');
            cout << "Welcome to FCAI X-O Game. :)\n";
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'O');
            else
                players[1] = new RandomPlayer('O', 3);// Player pointer points to child
            GameManagerXo x_o_game(new X_O_Board(), players);
            x_o_game.run();
            system("pause");
            break;
        }
        case 2: {
            Player *players[2];
            players[0] = new Player(1, 'X');
            cout << "Welcome to FCAI X-O Game. :)\n";
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'O');
            else
                players[1] = new RandomPlayer('O', 3);// Player pointer points to child
            GameManagerXo x_o_game(new Pyramic(), players);
            x_o_game.run();
            system("pause");
            break;
        }
        case 3: {
            Player *players[2];
            players[0] = new ConnectFour_Player(1, 'X');
            cout << "Welcome to FCAI X-O Game. :)\n";
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new ConnectFour_Player(2, 'O');
            else {
                int dif;
                cout << "Pick the difficulty level from 1 to 6 (easy to hard):\n";
                cin >> dif;
                while (dif < 1 || dif > 6) {
                    cout << "Pick a number from 1 to 6!!\n";
                    cin >> dif;
                }
                players[1] = new ConnectFour_AI('O', dif);// Player pointer points to child
            }
            ConnectFour_GameManager ConnectFour(new ConnectFour_Board(), players);
            ConnectFour.run();
            system("pause");
            break;
        }
        case 4: {
            Player *players[2];
            players[0] = new Player(1, 'X');
            cout << "Welcome to FCAI X-O Game.)\n";
            cout << "Press 1 if you want to play with computer: ";
            cin >> choice;
            if (choice != 1)
                players[1] = new Player(2, 'O');
            else
                players[1] = new RandomPlayer('O', 5);// Player pointer points to child
            GameManager x_o_game(new TIC_TAC_TOE_Board(), players);
            x_o_game.run();
            system("pause");
            break;
        }
    }

}
