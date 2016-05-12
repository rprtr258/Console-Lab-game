#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    string v[] = {
        string("  ***\n") +
        string("  ** \n") +
        string("  *  \n") +
        string("     \n") +
        string("     \n"),

        string("   **\n") +
        string("   **\n") +
        string("  ** \n") +
        string("     \n") +
        string("     \n"),

        string("     \n") +
        string("    *\n") +
        string("  ***\n") +
        string("    *\n") +
        string("     \n"),

        string("     \n") +
        string("     \n") +
        string("  ***\n") +
        string("   **\n") +
        string("    *\n"),

        string("     \n") +
        string("     \n") +
        string("  *  \n") +
        string("  ***\n") +
        string("   **\n"),

        string("     \n") +
        string("     \n") +
        string("  *  \n") +
        string("  *  \n") +
        string(" *** \n"),


        string("     \n") +
        string("     \n") +
        string("  *  \n") +
        string(" **  \n") +
        string("***  \n"),


        string("     \n") +
        string("     \n") +
        string(" **  \n") +
        string("**   \n") +
        string("**   \n"),


        string("     \n") +
        string("*    \n") +
        string("***  \n") +
        string("*    \n") +
        string("     \n"),

        string("*    \n") +
        string("**   \n") +
        string("***  \n") +
        string("     \n") +
        string("     \n"),

        string("**   \n") +
        string("***  \n") +
        string("  *  \n") +
        string("     \n") +
        string("     \n"),

        string(" *** \n") +
        string("  *  \n") +
        string("  *  \n") +
        string("     \n") +
        string("     \n")
    };
    bool game = true;
    char c;
    int cur_frame = 0;
    clock_t tim = clock();
    while(game) {
        if(clock() - tim >= 70) {
            tim = clock();
            system("cls");
            cout << v[cur_frame];
            cur_frame = (cur_frame + ((rand() % 2) * 2 - 1) + (sizeof(v) / sizeof(string))) % (sizeof(v) / sizeof(string));
        }
    }
    return 0;
}
