#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Player.h"
#include "Maze.h"

using namespace std;

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    system("cls");
    hideCursor();

    Player player;
    player.hp = 5;
    int currentLevel = 1;

    Maze gameMaze;
    bool isGameOver = false;

    while (!isGameOver) {
        gameMaze.generateNewMaze(); 
        player.x = gameMaze.getEntranceX();
        player.y = gameMaze.getEntranceY();

        bool isLevelClear = false;

        while (!isLevelClear && !isGameOver) {
            int next_x = player.x;
            int next_y = player.y;

            if (_kbhit()) {
                int key = _getch();
                if (key == 224) {
                    key = _getch();
                    if (key == 72) next_y--;
                    if (key == 80) next_y++;
                    if (key == 75) next_x--;
                    if (key == 77) next_x++;
                } 
                else if (key == 'q' || key == 'Q') {
                    isGameOver = true;
                }
            }

            char targetTile = gameMaze.getTile(next_x, next_y);
            if (targetTile != '#') { 
                player.x = next_x;
                player.y = next_y;
            }

            char currentTile = gameMaze.getTile(player.x, player.y);
            
            if (currentTile == '\'') { 
                player.hp -= 1;
                gameMaze.setTile(player.x, player.y, ' ');
                if (player.hp <= 0) {
                    isGameOver = true;
                }
            } 
            else if (currentTile == 'E') { 
                isLevelClear = true;
                currentLevel++;
            }

            gotoxy(0, 0);
            gameMaze.drawMap(player.x, player.y);

            cout << "\n======================\n";
            cout << " Level: " << currentLevel << "\n";
            cout << " HP: ";
            for (int i = 0; i < 5; i++) {
                if (i < player.hp) cout << "O ";
                else cout << "- ";
            }
            cout << "\n======================\n";

            Sleep(30); 
        }
    }

    system("cls");
    cout << "\n\n\tGAME OVER\n";
    cout << "\tYou reached Level " << currentLevel << "\n\n";
    
    system("pause");
    return 0;
}