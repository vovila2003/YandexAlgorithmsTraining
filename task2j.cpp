#include "task2j.h"

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using namespace std;

Task2J::Task2J() {}

struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

ostream& operator<<(ostream& stream, const Point point) {
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

struct Rect {
    vector<Point> points;
    Point start;
    Point finish;
};


void Task2J::doTask()
{
    int m, n;
    cin >> m >> n;
    char c;
    vector<vector<char>> field = vector<vector<char>> (m + 2, vector<char>(n + 2 , 'Z'));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c;
            field[i][j] = c;
        }
    }

    bool ok;
    Point start;
    tie(ok, start) = findPoint(field);
    if (!ok) {
        cout << "NO";
        return;
    }
    Rect rect1 = makeRect(start, field);
    decorateField(rect1, 'b', field);
    tie(ok, start) = findPoint(field);
    if (!ok) {
        Rect rect2;
        tie(ok, rect2) = trySplit(rect1);
        if (!ok) {
            cout << "NO";
            return;
        }
        decorateField(rect2, 'a', field);
    }
    tie(ok, start) = findPoint(field);
    if (ok) {
        cout << "NO";
        return;
    }
    cout << "YES" << endl;
    printField(field);
}

pair<bool, Point> Task2J::findPoint(const vector<vector<char> > &field)
{
    int i, j;
    bool find = false;
    for (i = 1; i < (int)field.size() - 1; ++i) {
        for (j = 1; j < (int)field.at(i).size() - 1; ++j) {
            if (field[i][j] == '#') {
                find = true;
                break;
            }
        }
        if (find) {
            break;
        }
    }
    Point point {i, j};
    return make_pair(find, point);
}

set<Point> Task2J::makeFigure(Point start)
{
    set<Point> result;



    return result;
}

Rect Task2J::makeRect(Point start, const vector<vector<char> > &field)
{
    Rect rect;
    rect.start = start;
    map<int, vector<int>> xToYMap;
    map<int, vector<int>> yToXMap;
    rect.points.push_back(start);
    refreshMaps(start, xToYMap, yToXMap);
    int maxX = start.x;
    int maxY = start.y;
    while (canToRight(maxY, yToXMap, field)) {
        ++maxY;
        moveToRight(maxY, xToYMap, yToXMap, rect);
    }
    while(canToDown(maxX, xToYMap, field)) {
        ++maxX;
        moveToDown(maxX, xToYMap, yToXMap, rect);
    }
    rect.finish = {maxX, maxY};
    return rect;
}

void Task2J::refreshMaps(Point point, map<int, vector<int> > &xToYMap,
                         map<int, vector<int> > &yToXMap)
{
    xToYMap[point.x].push_back(point.y);
    yToXMap[point.y].push_back(point.x);
}

bool Task2J::canToRight(int y, const map<int, vector<int> > &yToXMap,
                        const vector<vector<char> > &field)
{
    const vector<int>& xs = yToXMap.at(y);
    for (size_t i = 0; i < xs.size(); ++i) {
        int x = xs.at(i);
        if (field.at(x).at(y + 1) != '#')
            return false;
    }
    return true;
}

bool Task2J::canToDown(int x, const map<int, vector<int> > &xToYMap,
                       const vector<vector<char> > &field)
{
    const vector<int>& ys = xToYMap.at(x);
    for (size_t i = 0; i < ys.size(); ++i) {
        int y = ys.at(i);
        if (field.at(x + 1).at(y) != '#')
            return false;
    }
    return true;
}

void Task2J::moveToRight(int y, map<int, vector<int> > &xToYMap, map<int, vector<int> > &yToXMap,
                         Rect &rect)
{
    const vector<int>& xs = yToXMap.at(y - 1);
    for (size_t i = 0; i < xs.size(); ++i) {
        int x = xs.at(i);
        Point point {x, y};
        rect.points.push_back(point);
        refreshMaps(point, xToYMap, yToXMap);
    }
}

void Task2J::moveToDown(int x, map<int, vector<int> > &xToYMap, map<int, vector<int> > &yToXMap,
                        Rect &rect)
{
    const vector<int>& ys = xToYMap.at(x - 1);
    for (size_t i = 0; i < ys.size(); ++i) {
        int y = ys.at(i);
        Point point {x, y};
        rect.points.push_back(point);
        refreshMaps(point, xToYMap, yToXMap);
    }
}

void Task2J::decorateField(const Rect &rect, char c, vector<vector<char> > &field)
{
    for (size_t i = 0; i < rect.points.size(); ++i) {
        Point point = rect.points.at(i);
        field[point.x][point.y] = c;
    }
}

void Task2J::printRect(const Rect &rect)
{
    cout << rect.start << " " << rect.finish << endl;
}

void Task2J::printField(const std::vector<std::vector<char> > &field)
{
    for (size_t i = 1; i < field.size() - 1; ++i) {
        for (size_t j = 1; j < field[i].size() - 1; ++j) {
            cout << field[i][j];
        }
        cout << endl;
    }
}

pair<bool, Rect> Task2J::trySplit(Rect &rect)
{
    Rect newRect;
    if (rect.points.size() == 1) {
        return make_pair(false, std::move(newRect));
    }
    if (rect.start.x == rect.finish.x || rect.start.y == rect.finish.y) {
        newRect.start = rect.start;
        newRect.finish = rect.start;
        newRect.points.push_back(Point{rect.start.x, rect.start.y});
        return make_pair(true, std::move(newRect));
    }
    newRect.start = Point {rect.start.x,rect.start.y};
    newRect.finish = Point {rect.start.x,rect.finish.y};

    for (int y = rect.start.y; y <= rect.finish.y; ++y) {
        Point point {rect.start.x, y};
        newRect.points.push_back(point);
    }
    return make_pair(true, std::move(newRect));
}
