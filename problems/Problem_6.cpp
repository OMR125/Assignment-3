//purpose:problem 6
// author:mohamed ahmed shawky
//id:20220275
//section:s3
//Date:12/8/2023
#include<iostream>
#include <thread>
#include <cstdlib>
#define s "\n"
#define sp " "
#define End return 0
#define ll long long
#define all(x) x.begin(),x.end()
#define Fast ios_base::sync_with_stdio;cin.tie(0);cout.tie(0);
using namespace std;
class Game {
private:
    int dx[8] = { 1, 0, -1, 0, -1, -1, 1, 1 };
    int dy[8] = { 0, -1, 0, 1, -1, 1, -1, 1 };
    int num_run;
    int size;
    pair<int, int>alive_daid[25][30];
    bool array[25][30], new_array[25][30];
    bool check(int x, int y) const {
        return x >= 0 && x < 25&& y >= 0 && y < size;
    }
public:
    Game() {
        initialize();
    }
    void initialize() {
        size = 30;
        cout << "Enter number of alive ciel: ";
        int x; cin >> x;
        cout << "choose ceil by enter its row and column  :"<<s;
        for (int i = 0; i < 25;i++) {
            cout << "Row " << i + 1 << " :";
            for (int j = 0; j < 30;j++) {
                cout << j + 1 << " ";
                array[i][j] = false;
            }
            cout << s;
        }
        while (x--){
            int a, b; cin >>  a >> b;
            array[a-1][b-1] = true;

        }
    }
    void reset() {
        for (auto& i : array) {
            for (bool& j : i) {
                j = false;
            }
        }
    }
    void count_neighbors() {
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < 8; ++k) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (check(nx, ny)) {
                        (array[nx][ny] ? alive_daid[i][j].first++ : alive_daid[i][j].second++);
                    }
                }
            }
        }
    }
    void next_generation() {
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i][j]) {
                    if (alive_daid[i][j].first < 2) {
                        new_array[i][j] = false;
                    }
                    else if (alive_daid[i][j].first > 3) {
                        new_array[i][j] = false;
                    }
                    else
                        new_array[i][j] = true;
                }
                else {
                    if (alive_daid[i][j].first == 3) {
                        new_array[i][j] = true;
                    }
                    else {
                        new_array[i][j] = false;
                    }
                }
            }
        }
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < size; ++j) {
                array[i][j] = new_array[i][j];
                alive_daid[i][j].first = 0;
                alive_daid[i][j].second = 0;
            }
        }
    }
    void display() {
        system("cls");
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << (new_array[i][j] ? char(254) : ' ');
            }
            cout << s;
        }
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    void run() {
        cout << "Enter number of run:";
        cin >> num_run;
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << (array[i][j] ? char(254) : ' ' );
            }
            cout << s;
        }
        while (num_run--) {
            count_neighbors();
            next_generation();
            display();
            //        usleep(500000);
        }
    }
};
int main() {
    Game ob;
    ob.run();
}
