#include <iostream>
#include <ctime>

using namespace std;

enum State {MENU, GAME, HELP};
enum MoveState {NOPASS, MOVE, EXIT};

const int SIZE_X = 10, SIZE_Y = 10;
char map[SIZE_X][SIZE_Y];
int px = 0, py = 0;
bool last_comm_wrong = false;

inline void clrscr() {
    system("cls");
}

void print_state(const State &state) {
    switch(state) {
        case (MENU) : {
            cout << "Labyrinth game" << endl;
            cout << "   [S] Start" << endl;
            cout << "   [C] Continue" << endl;
            cout << "   [H] Help" << endl;
            cout << "   [Q] Quit" << endl;
            break;
        }
        case (GAME) : {
            for(int i = 0;i < 10;i++) {
                for(int j = 0;j < 10;j++) {
                    cout << map[j][i];
                }
                cout << endl;
            }
            if(last_comm_wrong) {
                cout << "You can't go this way" << endl;
                last_comm_wrong = false;
            }
            break;
        }
        case (HELP) : {
            cout << "Controlling:" << endl;
            cout << "    Moving:" << endl;
            cout << "        L - Left, R - Right" << endl;
            cout << "        U - Up, D - Down" << endl;
            cout << "    M - Menu" << endl;
            break;
        }
    }
}

bool test_comm_and_state(const string &comm, const State &state) {
    switch(state) {
        case (MENU) : {
            return (comm == "S" || comm == "C" || comm == "H" || comm == "Q");
        }
        case (GAME) : {
            if(comm == "M") {
                return true;
            } else {
                for(const char &e : comm) {
                    if(e != 'L' && e != 'R' && e != 'U' && e != 'D') {
                        return false;
                    }
                }
                return true;
            }
        }
        case (HELP) : {
            return true;
        }
    }
    return false;
}

void generate_map() {
    //TODO: gen lab
    for(int i = 0;i < SIZE_Y;i++) {
        for(int j = 0;j < SIZE_X;j++) {
            map[j][i] = (rand() % 10 < 3) ? 'W' : '_';
        }
    }
    map[0][0] = 'P';
    map[SIZE_X - 1][SIZE_Y - 1] = 'E';
}

void load_map() {
    //TODO: load map
    generate_map();
}

MoveState move(const int &dx, const int &dy) {
    if(px + dx < 0 ||
       px + dx >= SIZE_X ||
       py + dy < 0 ||
       py + dy >= SIZE_Y ||
       map[px + dx][py + dy] == 'W')
        return NOPASS;
    if(map[px + dx][py + dy] == 'E') return EXIT;
    swap(map[px][py], map[px + dx][py + dy]);
    px += dx;
    py += dy;
    return MOVE;
}

int main() {
    srand(time(NULL));
    string c;
    State state = MENU;
    bool game = true;
    while(game) {
        clrscr();
        print_state(state);
        cout << "> ";
        cin >> c;
        while(!test_comm_and_state(c, state)) {
            cout << "Wrong command, try again" << endl;
            cout << "> ";
            cin >> c;
        }
        switch(state) {
            case (MENU) : {
                if(c == "S") {
                    state = GAME;
                    generate_map();
                } else if(c == "C") {
                    state = GAME;
                    load_map();
                } else if(c == "H") {
                    state = HELP;
                } else if(c == "Q") {
                    game = false;
                }
                break;
            }
            case (GAME) : {
                if(c == "M") {
                    state = MENU;
                } else {
                    int move_state;
                    for(const char &e : c) {
                        if(e == 'L') {
                            move_state = move(-1, 0);
                        } else if(e == 'R') {
                            move_state = move(+1, 0);
                        } else if(e == 'U') {
                            move_state = move(0, -1);
                        } else if(e == 'D') {
                            move_state = move(0, +1);
                        }
                    }
                    if(move_state == NOPASS) {
                        last_comm_wrong = true;
                    } else if(move_state == EXIT) {
                        //TODO: Win state
                        state = MENU;
                        px = 0;
                        py = 0;
                    }
                }
                break;
            }
            case (HELP) : {
                state = MENU;
                break;
            }
        }
    }
    return 0;
}
