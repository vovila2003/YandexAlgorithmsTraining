#ifndef TASK2J_H
#define TASK2J_H

#include <vector>
#include <set>
#include <istream>

struct Rect;
struct Vector2;

class Task2J
{
public:
    Task2J();
    void doTask();
    void runTests();

private:
    void calculate(std::istream& istream, std::ostream& ostream);
    std::pair<bool, Vector2> findPoint(const std::vector<std::vector<char>>& field);
    std::set<Vector2> makeFigure(Vector2 start, const std::vector<std::vector<char>>& field);
    void decorateField(const Rect &rect, char c, std::vector<std::vector<char> > &field);
    void decorateField(const std::set<Vector2> &figure, char c, std::vector<std::vector<char> > &field);
    void printRect(const Rect& rect, std::ostream &stream);
    void printField(const std::vector<std::vector<char>>& field, std::ostream &stream);
    std::pair<bool, Rect> trySplitFigure(const std::set<Vector2>& figure);
    void test1();
    std::pair<bool, Rect> toRect(const std::set<Vector2> &figure);
    std::pair<bool, Rect> trySplitFigureTo2Rect(const std::set<Vector2>& figure);
};

#endif // TASK2J_H
