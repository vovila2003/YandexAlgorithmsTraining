#ifndef TASK2J_H
#define TASK2J_H

#include <vector>
#include <set>
#include <map>

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
    std::pair<bool, std::vector<Rect>> trySplit(const std::set<Point>& figure);
    bool isRect(const std::set<Point>& figure);
    void test1();
    Rect makeRect(Point start, const std::set<Point> &figure);
    void refreshMaps(Point point, std::map<int, std::vector<int> > &xToYMap,
                     std::map<int, std::vector<int> > &yToXMap);
    bool canToRight(int y, const std::map<int, std::vector<int> > &yToXMap,
                    const std::set<Point> &figure);
    bool canToDown(int x, const std::map<int, std::vector<int> > &xToYMap,
                   const std::set<Point> &figure);
    void moveToRight(int y, std::map<int, std::vector<int> > &xToYMap,
                     std::map<int, std::vector<int> > &yToXMap, Rect &rect);
    void moveToDown(int x, std::map<int, std::vector<int> > &xToYMap,
                    std::map<int, std::vector<int> > &yToXMap, Rect &rect);
};

#endif // TASK2J_H
