#ifndef TASK2J_H
#define TASK2J_H

#include <vector>
#include <map>
#include <set>

struct Rect;
struct Point;

class Task2J
{
public:
    Task2J();
    void doTask();

private:
    std::pair<bool, Point> findPoint(const std::vector<std::vector<char>>& field);
    std::set<Point> makeFigure(Point start);
    Rect makeRect(Point start, const std::vector<std::vector<char>>& field);
    void refreshMaps(Point point, std::map<int, std::vector<int>>& xToYMap,
                     std::map<int, std::vector<int>>& yToXMap);
    bool canToRight(int y, const std::map<int, std::vector<int>>& yToXMap,
                    const std::vector<std::vector<char>>& field);
    bool canToDown(int x, const std::map<int, std::vector<int>>& xToYMap,
                    const std::vector<std::vector<char>>& field);
    void moveToRight(int y, std::map<int, std::vector<int>>& xToYMap,
                     std::map<int, std::vector<int>>& yToXMap,
                     Rect &rect);
    void moveToDown(int x, std::map<int, std::vector<int>>& xToYMap,
                     std::map<int, std::vector<int>>& yToXMap,
                     Rect &rect);
    void decorateField(const Rect& rect, char c, std::vector<std::vector<char>>& field);
    void printRect(const Rect& rect);
    void printField(const std::vector<std::vector<char>>& field);
    std::pair<bool, Rect> trySplit(Rect& rect);
};

#endif // TASK2J_H
