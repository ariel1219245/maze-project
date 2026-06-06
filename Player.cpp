#include "Player.h"
#include "Maze.h"
#include <queue>
#include <algorithm>

Player::Player() {
    x = 1;
    y = 1;
    hp = 5; 
}

Player::~Player() {}

bool Player::isValidMove(int targetX, int targetY, const Maze& maze) const {
    return maze.getTile(targetX, targetY) != '#';
}

void Player::handleWallCollision(int& next_x, int& next_y, int dx, int dy, const Maze& maze) const {
    
    if (isValidMove(next_x, next_y, maze)) {
        return;
    }

    
    next_x = this->x;
    next_y = this->y;

    if (dy != 0) {
        
        if (isValidMove(this->x - 1, this->y, maze)) {
            next_x = this->x - 1;
        } else if (isValidMove(this->x + 1, this->y, maze)) {
            next_x = this->x + 1;
        }
    } 
    else if (dx != 0) {
        
        if (isValidMove(this->x, this->y - 1, maze)) {
            next_y = this->y - 1;
        } else if (isValidMove(this->x, this->y + 1, maze)) {
            next_y = this->y + 1;
        }
    }
}

std::vector<Point> Player::findShortestPath(const Maze& maze) const {
    std::vector<Point> shortestPath;
    const int MAP_WIDTH = 21;
    const int MAP_HEIGHT = 11;

    
    int endX = -1, endY = -1;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (maze.getTile(j, i) == 'E') {
                endX = j;
                endY = i;
                break;
            }
        }
    }

    if (endX == -1 || endY == -1) return shortestPath;

    std::vector<std::vector<bool>> visited(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));
    std::vector<std::vector<Point>> parent(MAP_HEIGHT, std::vector<Point>(MAP_WIDTH, {-1, -1}));
    std::queue<Point> q;

    Point startNode = { this->x, this->y };
    Point endNode = { endX, endY };

    q.push(startNode);
    visited[startNode.y][startNode.x] = true;

    int dirX[] = {0, 0, -1, 1};
    int dirY[] = {-1, 1, 0, 0};
    bool found = false;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr == endNode) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dirX[i];
            int ny = curr.y + dirY[i];

            if (isValidMove(nx, ny, maze) && !visited[ny][nx]) {
                visited[ny][nx] = true;
                parent[ny][nx] = curr;
                q.push({nx, ny});
            }
        }
    }

    if (found) {
        Point curr = endNode;
        while (!(curr == startNode)) {
            shortestPath.push_back(curr);
            curr = parent[curr.y][curr.x];
        }
        shortestPath.push_back(startNode);
        std::reverse(shortestPath.begin(), shortestPath.end());
    }

    return shortestPath;
}
