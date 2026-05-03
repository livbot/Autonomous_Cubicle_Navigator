#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <vector>
#include <string>
#include <unordered_map>

struct Point {
    int x, y;
    // Overload == to compare points easily
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

struct Node {
    Point pos;
    int g, h;
    Node* parent;
    int f() const { return g + h; }
};

class CubicleNavigator {
public:
    CubicleNavigator();
    ~CubicleNavigator();
    void loadEmployees(const std::string& filename);
    void findPath(std::string startName, std::string endName);

private:
    std::unordered_map<std::string, Point> directory;
    std::vector<std::vector<int>> isSafe;
    int calculateH(Point p1, Point p2) const;
    int width, height;
};

#endif