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

struct Vector2 {
    int x;
    int y;

    bool operator<(const Vector2& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

ostream& operator<<(ostream& stream, const Vector2 point) {
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

struct Rect {
    vector<Vector2> points;
    Vector2 start;
    Vector2 finish;
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

    auto [ok, start] = findPoint(field);
    if (!ok) {
        ostream << "NO";
        return;
    }
    set<Vector2> figure1 = makeFigure(start, field);
    decorateField(figure1, 'b', field);
    tie(ok, start) = findPoint(field);
    if (!ok) {
        Rect rect;
        tie(ok, rect) = trySplitFigure(figure1);
        if (!ok) {
            ostream << "NO";
            return;
        }
        decorateField(rect, 'a', field);
    } else {
        set<Vector2> figure2 = makeFigure(start, field);
        Rect rect1, rect2;
        tie(ok, rect1) = toRect(figure1);
        if (ok) {
            tie(ok, rect2) = toRect(figure2);
            if (!ok) {
                ostream << "NO";
                return;
            }
            decorateField(rect2, 'a', field);
        }
    }

    tie(ok, start) = findPoint(field);
    if (ok) {
        ostream << "NO";
        return;
    }
    ostream << "YES" << "\n";
    printField(field, ostream);
}

pair<bool, Vector2> Task2J::findPoint(const vector<vector<char> > &field)
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
    Vector2 point {i, j};
    return make_pair(find, point);
}

set<Vector2> Task2J::makeFigure(Vector2 start, const std::vector<std::vector<char>>& field)
{
    set<Vector2> result;
    queue<Vector2> inProgress;
    inProgress.push(start);
    vector<int> dx {0, 1, 0, -1};
    vector<int> dy {1, 0, -1, 0};
    result.insert(start);

    while(!inProgress.empty()) {
        Vector2 currentPoint = inProgress.front();
        inProgress.pop();
        for (size_t k = 0; k < dx.size(); ++k) {
            Vector2 newPoint {currentPoint.x + dx[k], currentPoint.y + dy[k]};
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
        Vector2 point = rect.points.at(i);
        field[point.x][point.y] = c;
    }
}

void Task2J::decorateField(const set<Vector2> &figure, char c, vector<vector<char> > &field)
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

pair<bool, Rect> Task2J::trySplitFigure(const set<Vector2>& figure)
{
    bool ok;
    Rect rect;
    tie(ok, rect) = toRect(figure);
    if (ok) {
        Rect newRect;
        if (rect.points.size() == 1) {
            return make_pair(false, std::move(newRect));
        }
        if (rect.start.x == rect.finish.x || rect.start.y == rect.finish.y) {
            newRect.start = rect.start;
            newRect.finish = rect.start;
            newRect.points.push_back(Vector2{rect.start.x, rect.start.y});
            return make_pair(true, std::move(newRect));
        }
        newRect.start = Vector2 {rect.start.x,rect.start.y};
        newRect.finish = Vector2 {rect.start.x,rect.finish.y};

        for (int y = rect.start.y; y <= rect.finish.y; ++y) {
            Vector2 point {rect.start.x, y};
            newRect.points.push_back(point);
        }
        return make_pair(true, std::move(newRect));
    }
    return trySplitFigureTo2Rect(figure);
}

pair<bool, Rect> Task2J::toRect(const set<Vector2> &figure)
{
    Rect rect;
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
        rect.points.push_back(Vector2{*it});
    }
    rect.start = Vector2{minX, minY};
    rect.finish = Vector2{maxX, maxY};
    bool isRect = (maxX - minX + 1) * (maxY - minY + 1) == (int)figure.size();
    return make_pair(isRect, std::move(rect));
}

pair<bool, Rect> Task2J::trySplitFigureTo2Rect(const set<Vector2>& figure) {
    map<int, vector<int>> xToYMap;
    map<int, vector<int>> yToXMap;
    for (auto it = figure.begin(); it != figure.end(); ++it) {
        xToYMap[it->x].push_back(it->y);
        yToXMap[it->y].push_back(it->x);
    }
    set<Vector2> figure1;
    set<Vector2> figure2(figure);

    for (auto it = xToYMap.begin(); it != xToYMap.end(); ++it) {
        int x = it->first;
        auto& ys = it->second;
        for (size_t i = 0; i < ys.size(); ++i) {
            int y = ys.at(i);
            Vector2 point{x, y};
            figure1.insert(point);
            figure2.erase(point);
        }
        bool ok;
        Rect rect;
        tie(ok, rect) = toRect(figure2);
        if (!ok) {
            continue;
        }
        tie(ok, rect) = toRect(figure1);
        if (!ok) {
            continue;
        }
        return make_pair(true, std::move(rect));
    }

    figure1.clear();
    figure2.insert(figure.begin(), figure.end());

    for (auto it = yToXMap.begin(); it != yToXMap.end(); ++it) {
        int y = it->first;
        auto& xs = it->second;
        for (size_t i = 0; i < xs.size(); ++i) {
            int x = xs.at(i);
            Vector2 point{x, y};
            figure1.insert(point);
            figure2.erase(point);
        }
        bool ok;
        Rect rect;
        tie(ok, rect) = toRect(figure2);
        if (!ok) {
            continue;
        }
        tie(ok, rect) = toRect(figure1);
        if (!ok) {
            continue;
        }
        return make_pair(true, std::move(rect));
    }
    return make_pair(false, Rect());
}

void Task2J::test1()
{
    string input(
        "3 5 \n"
        "..#..\n"
        "###..\n"
        "..#..\n"
        );
    stringstream si(input);
    stringstream so;
    calculate(si, cout);
}


