#ifndef TASK2J_H
#define TASK2J_H

#include <vector>
#include <set>
#include <istream>

struct Rect;
struct Point;

class Task2J
{
public:
    Task2J();
    void doTask();
    void runTests();

private:
    void calculate(std::istream& istream, std::ostream& ostream);
    std::pair<bool, Point> findPoint(const std::vector<std::vector<char>>& field);
    std::set<Point> makeFigure(Point start, const std::vector<std::vector<char>>& field);
    void decorateField(const Rect &rect, char c, std::vector<std::vector<char> > &field);
    void decorateField(const std::set<Point> &figure, char c, std::vector<std::vector<char> > &field);
    void printRect(const Rect& rect, std::ostream &stream);
    void printField(const std::vector<std::vector<char>>& field, std::ostream &stream);
    std::pair<bool, Rect> trySplitFigure(const std::set<Point>& figure);
    void test1();
    std::pair<bool, Rect> toRect(const std::set<Point> &figure);
    std::pair<bool, Rect> trySplitFigureTo2Rect(const std::set<Point>& figure);
};

#endif // TASK2J_H
