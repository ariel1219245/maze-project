#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
private:
    std::vector<std::string> map;
    int entranceX;
    int entranceY;
    int exitX;
    int exitY;
    int width;
    int height;

    void loadTemplate(int type);

public:
    Maze();
    void generateNewMaze();
    void drawMap(int playerX, int playerY) const;
    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);
    int getEntranceX() const;
    int getEntranceY() const;
};

#endif