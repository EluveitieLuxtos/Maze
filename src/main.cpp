#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>

#include "DisplayConsoleMazeTiled.h"
#include "MazeTiled.h"
//#include "DisplayConsoleMazeWalls.h"
//#include "MazeWithWalls.h"

int main(){
    srand(time(NULL));
    string buffer;
    string changeParam = "n";
    MazeType mazeType = SQUARE;
    int width = 8;
    int length = 10;
    int cycles = 5;
    int sets = 4;
    bool externalWalls = false;
    while (true) {
        if (changeParam == "y") {
            cout << "Type of tiles :\n0 for TRIANGLE\n1 for SQUARE\n2 for HEXAGON\nWhich one do you choose ?\n";
            cin >> buffer;
            switch (atoi(buffer.c_str())) {
                case 0 : mazeType = TRIANGLE; break;
                case 1 : mazeType = SQUARE; break;
                case 2 : mazeType = HEXAGON; break;
                default: break;
            }
            cout << "Width of the maze ?\n";
            cin >> buffer;
            width = atoi(buffer.c_str());
            cout << "Length of the maze ?\n";
            cin >> buffer;
            length = atoi(buffer.c_str());
            cout << "Number of cycles within sets ?\n";
            cin >> buffer;
            cycles = atoi(buffer.c_str());
            cout << "Number of sets in the maze ?\n";
            cin >> buffer;
            sets = atoi(buffer.c_str());
            cout << "Do you want external walls ? (y for yes)\n";
            cin >> buffer;
            if (buffer == "y")
                externalWalls = true;
            else
                externalWalls = false;
        }
        MazeTiled maze(mazeType, width, length, cycles, sets, externalWalls);
        displayConsoleMazeTiled(maze);
//        MazeWithWalls maze(mazeType, width, length, cycles, sets);
//        displayConsoleMazeWalls(maze);
        cout << "\nDo you want to change the parameters ? (y for yes)";
        cin >> changeParam;
    }
    return EXIT_SUCCESS;
}


