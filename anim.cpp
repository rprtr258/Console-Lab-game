#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

int man() {
    string v[] = {
        string("                     \n") +
        string(" ##########          \n") +
        string(" #        ##      #  \n") +
        string("#  #  #     ###  # # \n") +
        string("# # ## #       ##  # \n") +
        string("#  ####            # \n") +
        string("#                  # \n") +
        string("#                  # \n") +
        string(" #  ##  ####  ##  #  \n") +
        string(" # ### ##  # ### ##  \n") +
        string("  #   #     #   #    \n"),

        string("  ##########         \n") +
        string("  #        ##      # \n") +
        string(" #  #  #     ###  # #\n") +
        string(" # # ## #       ##  #\n") +
        string(" #  ####            #\n") +
        string(" #                  #\n") +
        string(" #                  #\n") +
        string("  #  ##  ####  ##  # \n") +
        string("  # ### ##  # ### ## \n") +
        string("   #   #     #   #   \n") +
        string("                     \n")
    };
    bool game = true;
    int cur_frame = 0;
    clock_t tim = clock();
    while(game) {
        if(clock() - tim >= 70) {
            tim = clock();
            system("cls");
            cout << v[cur_frame];
            cur_frame = (cur_frame + 1) % (sizeof(v) / sizeof(string));
        }
    }
    return 0;
}
