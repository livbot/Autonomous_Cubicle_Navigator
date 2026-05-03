#define DEBUG
#include "Navigator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>

CubicleNavigator::CubicleNavigator() {
    // 0 = Walkable, 1 = Cubicle Wall
    grid = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=0
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 0}, //Y=1
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //Y=2
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 0}, //Y=3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=4
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=5
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Y=8
       //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    height = grid.size();
    width = grid[1].size();
    std::cout << "[DEBUG] Navigator Initialized: " << width << "x" << height << std::endl;
}

CubicleNavigator::~CubicleNavigator() {
    std::cout << "[DEBUG] Navigator Destroyed. Memory Cleared. " << std::endl;
}

void CubicleNavigator::loadEmployees(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return;
    }
    std::string line, name, x, y;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, name, ',');
        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        directory[name] = {std::stoi(x), std::stoi(y)};
    }
}

int CubicleNavigator::calculateH(Point p1, Point p2) const{
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

void CubicleNavigator::findPath(std::string startName, std::string endName) {
    std::vector<std::vector<bool>> visited(height,std::vector<bool>(width, false));
    #ifdef DEBUG
        std::cout << "[TRACE] Starting search from " <<startName << "..." << std::endl;
    #endif
    
    if (directory.find(startName) == directory.end() || directory.find(endName) == directory.end()) {
        std::cout << "Employee not found!" << std::endl;
        return;
    }

    Point start = directory[startName];
    Point goal = directory[endName];
    Point current = start;
    int steps = 0;

    while(!(current.x == goal.x && current.y == goal.y))
    {
        steps++;
        visited[current.y][current.x] = true;
        #ifdef DEBUG
            std::cout << "Navigating " << startName << " to(" << current.x <<"," << current.y << ")"<< std::endl;
        #endif
            // Logic: In a full A* implementation, you'd use a priority_queue here.
        //if(current.x < goal.x && grid[current.y][current.x + 1] == 0 && !visited[current.y][current.x + 1]){
        if(current.x < goal.x && isValidMove(current.x + 1, current.y, visited)){
            current.x++; //Move East
        }else if (current.y <goal.y && isValidMove(current.x, current.y + 1, visited)){
            current.y++; //Move South
        }else if (current.x > goal.x && isValidMove(current.x - 1, current.y, visited)){
            current.x--; //Move West 
        }else if (current.y >goal.y && isValidMove(current.x, current.y - 1, visited)){
            current.y--; //Move North
        }else{
            // If Heuristic path is blocked, try ANY valid neighbour (simple backtracking)
            if (isValidMove(current.x + 1, current.y, visited)) current.x++;
            else if (isValidMove(current.x -1, current.y, visited)) current.x--;
            else if (isValidMove(current.x, current.y + 1, visited)) current.y++;
            else if (isValidMove(current.x, current.y - 1, visited)) current.y--;
            else{
                std::cout << "!!Path Blocked at (" << current.x << ',' << current.y << ')' << std::endl;
            }
            
        }
        if (steps > 1000){
            std::cout << "Search timed out." << std::endl;
            break;
        }

    }
    // For now, we print the target coordinates to verify the directory works.
    if (current.x == goal.x && current.y == goal.y){
        std::cout << "Success! Path found in steps" << steps << "at (" << goal.x << ", " << goal.y << ")" << std::endl;
    }
      
}

bool CubicleNavigator::isValidMove(int x, int y, const std::vector<std::vector<bool>>& visited) {
    // Gate 1: Are we still inside the office? (Boundary Check)
    if (x < 0 || x >= width || y < 0 || y >= height) return false;

    // Gate 2: Is it a hallway (0) or a wall (1)? (Safety Check)
    if (grid[y][x] != 0) return false;

    // Gate 3: Have we been here before? (Memory Check)
    return !visited[y][x];
}