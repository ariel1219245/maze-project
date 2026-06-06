#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Maze;


struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

class Player {
public:
    
    int x;
    int y;
    int hp;

    Player();
    ~Player();

   
    bool isValidMove(int targetX, int targetY, const Maze& maze) const;

    
    void handleWallCollision(int& next_x, int& next_y, int dx, int dy, const Maze& maze) const;

    
    std::vector<Point> findShortestPath(const Maze& maze) const;
};

#endif 
