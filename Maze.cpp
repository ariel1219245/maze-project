#include "Maze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Maze::Maze() {
    srand(static_cast<unsigned int>(time(0)));
    width = 0;
    height = 0;
    entranceX = 1;
    entranceY = 1;
    exitX = 1;
    exitY = 1;
}

void Maze::loadTemplate(int type) {
    map.clear();
    if (type == 0) {
        map.push_back("#####################");
        map.push_back("# #       #         #");
        map.push_back("# # ##### # ####### #");
        map.push_back("#   #   #   #   #   #");
        map.push_back("##### # ####### # ###");
        map.push_back("#   # #       # #   #");
        map.push_back("# # # ####### # # # #");
        map.push_back("# #   #     #   # # #");
        map.push_back("# ####### # ##### # #");
        map.push_back("#         #         #");
        map.push_back("#####################");
    } 
    else if (type == 1) {
        map.push_back("#####################");
        map.push_back("#                   #");
        map.push_back("# ####### ######### #");
        map.push_back("# #     # #       # #");
        map.push_back("# # ### # # ##### # #");
        map.push_back("# # #   #   #   # # #");
        map.push_back("# # # ######### # # #");
        map.push_back("# # #           # # #");
        map.push_back("# # ############# # #");
        map.push_back("#                   #");
        map.push_back("#####################");
    } 
    else {
        map.push_back("#####################");
        map.push_back("#     #       #     #");
        map.push_back("### # # # ### # # ###");
        map.push_back("#   #   # #   # #   #");
        map.push_back("# ####### # ####### #");
        map.push_back("# #       #       # #");
        map.push_back("# # ############# # #");
        map.push_back("# # #           # # #");
        map.push_back("#   ##### # #####   #");
        map.push_back("#         #         #");
        map.push_back("#####################");
    }

    height = map.size();
    width = map[0].size();
}

void Maze::generateNewMaze() {
    int templateType = rand() % 3;
    loadTemplate(templateType);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (map[y][x] == ' ') {
                if (rand() % 12 == 0) {
                    map[y][x] = '\''; 
                }
            }
        }
    }

    while (true) {
        entranceX = 1 + rand() % (width - 2);
        entranceY = 1 + rand() % (height - 2);
        if (map[entranceY][entranceX] == ' ') {
            map[entranceY][entranceX] = 'S'; 
            break;
        }
    }

    while (true) {
        exitX = 1 + rand() % (width - 2);
        exitY = 1 + rand() % (height - 2);
        if (map[exitY][exitX] == ' ' && (abs(exitX - entranceX) + abs(exitY - entranceY) > 5)) {
            map[exitY][exitX] = 'E'; 
            break;
        }
    }
}

void Maze::drawMap(int playerX, int playerY) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                std::cout << "P "; 
            } 
            else if (abs(x - playerX) <= 2 && abs(y - playerY) <= 2) {
                std::cout << map[y][x] << " ";
            } 
            else {
                std::cout << "? "; 
            }
        }
        std::cout << "\n";
    }
}

char Maze::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return '#';
    }
    return map[y][x];
}

void Maze::setTile(int x, int y, char tile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        map[y][x] = tile;
    }
}

int Maze::getEntranceX() const { return entranceX; }
int Maze::getEntranceY() const { return entranceY; }