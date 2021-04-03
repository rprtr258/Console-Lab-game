#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

enum State {MENU, GAME, HELP};
enum CellType {WALL, FREE_SPACE, EXIT};
enum MoveType {MOVED, NOPASS, EXITED};

const int SIZE_X = 10, SIZE_Y = 10;
char map[SIZE_X][SIZE_Y];
State state = MENU;
bool game = true;
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
            cout << "        You can FREE_SPACE several times like this:" << endl;
            cout << "            RRRRDDRRDDLD" << endl;
            cout << "    M - Menu" << endl;
            break;
        }
    }
}

bool test_comm_and_state(const string &comm, const State &state) {
    switch(state) {
        case (MENU) : return (comm == "S" || comm == "C" || comm == "H" || comm == "Q");
        case (GAME) : return (comm == "M") ^ all_of(comm.begin(), comm.end(), [](const char &e) {
            return (e == 'L' || e == 'R' || e == 'U' || e == 'D');
        });
        case (HELP) : return true;
    }
    return false;
}

void generate_map() {
    //TODO: gen lab
    px = 0;
    py = 0;
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

CellType get_cell(const int &x, const int &y) {
    if(x < 0 || x >= SIZE_X ||
       y < 0 || y >= SIZE_Y ||
       map[x][y] == 'W')
        return WALL;
    return map[x][y] == 'E' ? EXIT : FREE_SPACE;
}

int decide(const char &value, const char &first, const char &second) {
    if (value == first || value == second)
        return (value == first) ? -1 : 1;
    return 0;
}

MoveType move(const char &dir) {
    const int dx = decide(dir, 'L', 'R');
    const int dy = decide(dir, 'U', 'D');
    const int new_x = px + dx;
    const int new_y = py + dy;
    const CellType next_cell = get_cell(new_x, new_y);
    switch (next_cell) {
        case (WALL) : return NOPASS;
        case (EXIT) : return EXITED;
        case (FREE_SPACE) : {
            swap(map[px][py], map[new_x][new_y]);
            px = new_x;
            py = new_y;
            return MOVED;
        }
    }
    return EXITED; // Unreachable
}

string get_input() {
    string input;
    cout << "> ";
    cin >> input;
    while(!test_comm_and_state(input, state)) {
        cout << "Wrong command, try again" << endl;
        cout << "> ";
        cin >> input;
    }
    return input;
}

int main() {
    srand(time(NULL));
    string c;
    while(game) {
        clrscr();
        print_state(state);
        c = get_input();
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
                break; // Unreachable
            }
            case (GAME) : {
                if(c == "M") {
                    state = MENU;
                } else {
                    MoveType move_type;
                    for(const char &e : c) {
                        move_type = move(e);
                    }
                    if(move_type == NOPASS) {
                        last_comm_wrong = true;
                    } else if(move_type == EXITED) {
                        //TODO: Win state
                        state = MENU;
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
