#include "BoardGame_Classes.hpp"

ConnectFour_GameManager::ConnectFour_GameManager(Board *bPtr, Player **playerPtr) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void ConnectFour_GameManager::run() {
    int X = -1;
    while (!boardPtr->game_is_over()) {
        for (int i: {0, 1}) {
            int Y = 8;
            ConnectFour_AI *p = dynamic_cast<ConnectFour_AI *>(players[i]);
            if (p != nullptr) {
                ConnectFour_Board *ptr = dynamic_cast<ConnectFour_Board *>(boardPtr);
                char **b = ptr->get_board();
                p->get_move(Y, b);
                Y++;
            } else
                boardPtr->display_board();

            while (!boardPtr->update_board(-1, Y, players[i]->get_symbol()))
                players[i]->get_move(X, Y);

            if (boardPtr->is_winner()) {
                boardPtr->display_board();
                cout << players[i]->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                boardPtr->display_board();
                cout << "Draw!\n";
                return;
            }

        }
    }
}