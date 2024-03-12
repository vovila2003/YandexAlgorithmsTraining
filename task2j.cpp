#include "task2j.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <map>

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
    calculate(cin, cout);
}

void Task2J::runTests()
{
    test1();
}

void Task2J::calculate(istream &istream, ostream &ostream)
{
    int m, n;
    istream >> m >> n;
    char c;
    vector<vector<char>> field = vector<vector<char>> (m + 2, vector<char>(n + 2 , 'Z'));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            istream >> c;
            field[i][j] = c;
        }
    }

    bool ok;
    Point start;
    tie(ok, start) = findPoint(field);
    if (!ok) {
        ostream << "NO";
        return;
    }
    set<Point> figure1 = makeFigure(start, field);
    decorateField(figure1, 'a', field);
    tie(ok, start) = findPoint(field);
    if (!ok) {
        vector<Rect> rects;
        tie(ok, rects) = trySplit(figure1);
        if (!ok) {
            ostream << "NO";
            return;
        }
        decorateField(rects.at(1), 'b', field);
    } else {
        set<Point> figure2 = makeFigure(start, field);
        if (!isRect(figure1) || !isRect(figure2)) {
            ostream << "NO";
            return;
        }
        decorateField(figure2, 'b', field);
    }

    tie(ok, start) = findPoint(field);
    if (ok) {
        ostream << "NO";
        return;
    }
    ostream << "YES" << "\n";
    printField(field, ostream);
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

set<Point> Task2J::makeFigure(Point start, const std::vector<std::vector<char>>& field)
{
    set<Point> result;
    queue<Point> inProgress;
    inProgress.push(start);
    vector<int> dx {0, 1, 0, -1};
    vector<int> dy {1, 0, -1, 0};
    result.insert(start);

    while(!inProgress.empty()) {
        Point currentPoint = inProgress.front();
        inProgress.pop();
        for (size_t k = 0; k < dx.size(); ++k) {
            Point newPoint {currentPoint.x + dx[k], currentPoint.y + dy[k]};
            if (field[newPoint.x][newPoint.y] == '#' && result.count(newPoint) == 0) {
                result.insert(newPoint);
                inProgress.push(newPoint);
            }
        }
    }

    return result;
}


void Task2J::decorateField(const Rect &rect, char c, vector<vector<char> > &field)
{
    for (size_t i = 0; i < rect.points.size(); ++i) {
        Point point = rect.points.at(i);
        field[point.x][point.y] = c;
    }
}

void Task2J::decorateField(const set<Point> &figure, char c, vector<vector<char> > &field)
{
    for (auto it = figure.begin(); it != figure.end(); ++it) {
        field[it->x][it->y] = c;
    }
}

void Task2J::printRect(const Rect &rect, ostream& stream)
{
    stream << rect.start << " " << rect.finish << endl;
}

void Task2J::printField(const std::vector<std::vector<char> > &field, ostream& stream)
{
    for (size_t i = 1; i < field.size() - 1; ++i) {
        for (size_t j = 1; j < field[i].size() - 1; ++j) {
            stream << field[i][j];
        }
        stream << "\n";
    }
}

pair<bool, vector<Rect>> Task2J::trySplit(const set<Point>& figure)
{
    //TODO
    vector<Rect> rects;
    // if (rect.points.size() == 1) {
    //     return make_pair(false, std::move(newRect));
    // }
    // if (rect.start.x == rect.finish.x || rect.start.y == rect.finish.y) {
    //     newRect.start = rect.start;
    //     newRect.finish = rect.start;
    //     newRect.points.push_back(Point{rect.start.x, rect.start.y});
    //     return make_pair(true, std::move(newRect));
    // }
    // newRect.start = Point {rect.start.x,rect.start.y};
    // newRect.finish = Point {rect.start.x,rect.finish.y};

    // for (int y = rect.start.y; y <= rect.finish.y; ++y) {
    //     Point point {rect.start.x, y};
    //     newRect.points.push_back(point);
    // }
    return make_pair(true, std::move(rects));
}

bool Task2J::isRect(const std::set<Point> &figure)
{
    auto it = figure.begin();
    int minX = it->x;
    int maxX = it->x;
    int minY = it->y;
    int maxY = it->y;
    for (;it != figure.end(); ++it) {
        minX = min(minX, it->x);
        minY = min(minY, it->y);
        maxX = max(maxX, it->x);
        maxY = max(maxY, it->y);
    }
    return (maxX - minX + 1) * (maxY - minY + 1) == (int)figure.size();
}

void Task2J::test1()
{
    string input(
        "2 5 \n"
        "..###\n"
        "#####\n"
        );
    stringstream si(input);
    stringstream so;
    calculate(si, cout);
}

Rect Task2J::makeRect(Point start, const set<Point> &figure)
{
    //TODO
    Rect rect;
    rect.start = start;
    map<int, vector<int>> xToYMap;
    map<int, vector<int>> yToXMap;
    rect.points.push_back(start);
    refreshMaps(start, xToYMap, yToXMap);
    int maxX = start.x;
    int maxY = start.y;
    while (canToRight(maxY, yToXMap, figure)) {
        ++maxY;
        moveToRight(maxY, xToYMap, yToXMap, rect);
    }
    while(canToDown(maxX, xToYMap, figure)) {
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
                        const set<Point> &figure)
{
    const vector<int>& xs = yToXMap.at(y);
    for (size_t i = 0; i < xs.size(); ++i) {
        Point point {xs.at(i), y + 1};
        if (figure.count(point) == 0)
            return false;
    }
    return true;
}

bool Task2J::canToDown(int x, const map<int, vector<int> > &xToYMap,
                       const set<Point> &figure)
{
    const vector<int>& ys = xToYMap.at(x);
    for (size_t i = 0; i < ys.size(); ++i) {
        Point point {x + 1, ys.at(i)};
        if (figure.count(point) == 0)
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
