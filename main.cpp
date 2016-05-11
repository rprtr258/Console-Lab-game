#include <iostream>
#include <string>

using namespace std;

enum State {
    MENU,
    GAME,
    HELP
};

char map[10][10];

inline void clrscr() {
    static string cls = string(100, '\n');
    cout << cls;
}

void print_state(const State &state) {
    switch(state) {
        case (MENU) : {
            cout << "Labyrinth game\n";
            cout << "   >Start - S\n";
            cout << "   >Continue - C\n";
            cout << "   >Help - H\n";
            cout << "   >Quit - Q\n";
            break;
        }
        case (GAME) : {
            for(int i = 0;i < 10;i++) {
                for(int j = 0;j < 10;j++) {
                    cout << map[j][i];
                }
                cout << '\n';
            }
            break;
        }
        case (HELP) : {
            cout << "Controlling:\n";
            cout << "    Moving:\n";
            cout << "        L - Left, R - Right\n";
            cout << "        U - Up, D - Down\n";
            cout << "    M - Menu";
            break;
        }
    }
}

bool test_comm_and_state(const string &comm, const State &state) {
    switch(state) {
        case (MENU) : {
            if(comm == "S" || comm == "C" || comm == "H" || comm == "Q") {
                return true;
            } else {
                return false;
            }
        }
        case (GAME) : {
            if(comm == "L" || comm == "R" || comm == "U" || comm == "D") {
                return true;
            } else {
                return false;
            }
        }
        case (HELP) : {
            return true;
        }
    }
}

int main() {
    string c;
    State state = MENU;
    bool game = true;
    //TODO: gen lab
    for(int i = 0;i < 10;i++) {
        for(int j = 0;j < 10;j++) {
            map[j][i] = '_';
        }
    }
    while(game) {
        clrscr();
        print_state(state);
        cout << "> ";
        cin >> c;
        while(!test_comm_and_state(c, state)) {
            cout << "Wrong command, try again\n";
            cout << "> ";
            cin >> c;
        }
        switch(state) {
            case (MENU) : {
                if(c == "S") {
                    state = GAME;
                } else if(c == "C") {
                    state = GAME;
                    //load save into map[][]
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
                } else if(c == "L") {
                    //move_left
                } else if(c == "R") {
                    //move_right
                } else if(c == "U") {
                    //move_up
                } else if(c == "D") {
                    //move_down
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
