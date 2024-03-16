#include "task3g.h"

#include <iostream>
#include <map>
#include <set>
#include <iterator>
#include <vector>

using namespace std;

Task3G::Task3G()
{

}

struct Point {
    int x;
    int y;

    bool operator==(const Point& other) {
        return x == other.x && y == other.y;
    }
};

void processY(const map<int, set<int>>& pointOnLine, vector<Point>& pointsInRect,
              int x, int newX, int y1, int y2) {
    pointsInRect.push_back(Point{x, y1});
    pointsInRect.push_back(Point{x, y2});
    if (pointOnLine.at(y1).count(newX) != 0) {
        pointsInRect.push_back(Point{newX, y1});
    }
    if (pointOnLine.at(y2).count(newX) != 0) {
        pointsInRect.push_back(Point{newX, y2});
    }
}

void processX(const map<int, set<int>>& pointOnLine, vector<Point>& pointsInRect,
              int x1, int x2, int y, int newY) {
    pointsInRect.push_back(Point{x1, y});
    pointsInRect.push_back(Point{x2, y});
    if (pointOnLine.at(x1).count(newY) != 0) {
        pointsInRect.push_back(Point{x1, newY});
    }
    if (pointOnLine.at(x2).count(newY) != 0) {
        pointsInRect.push_back(Point{x2, newY});
    }
}

bool checkResult(vector<Point>& pointsInRect, vector<Point>& result, size_t maxCount) {
    if (pointsInRect.size() == 4) {
        result.swap(pointsInRect);
        return true;
    }

    if (pointsInRect.size() > maxCount) {
        maxCount = pointsInRect.size();
        result.swap(pointsInRect);
    }
    return false;
}

vector<Point> makeRectFrom1Point(vector<Point>& points) {
    int delta = 1;
    vector<Point> result;
    int x = points[0].x;
    int y = points[0].y;
    result.push_back(Point{x + delta, y});
    result.push_back(Point{x, y + delta});
    result.push_back(Point{x + delta, y + delta});
    return result;
}

vector<Point> makeRectFrom2Points(vector<Point>& points) {
    vector<Point> result;
    int x1 = points[0].x;
    int y1 = points[0].y;

    int x2 = points[1].x;
    int y2 = points[1].y;
    return result;
}

vector<Point> makeRectFrom3Points(vector<Point>& points) {
    vector<Point> result;

    return result;
}

vector<Point> makeRect(vector<Point>& points) {
    vector<Point> result;
    if (points.size() == 1) {
        return makeRectFrom1Point(points);
    } else if (points.size() == 2) {
        return makeRectFrom2Points(points);
    } else if (points.size() == 3) {
        return makeRectFrom3Points(points);
    }
    return result;
}

void printResult(const vector<Point>& result) {
    cout << result.size();
    for (auto p : result) {
        cout << endl << p.x<< " " << p.y;
    }
}

void Task3G::doTask()
{
    int n;
    cin >> n;


    map<int, set<int>> pointsOnX;
    map<int, set<int>> pointsOnY;
    int x = 0;
    int y = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        pointsOnX[x].insert(y);
        pointsOnY[y].insert(x);
    }

    size_t maxCount = 0;
    vector<Point> result;
    result.reserve(4);
    vector<Point> pointsInRect1;
    pointsInRect1.reserve(4);
    vector<Point> pointsInRect2;
    pointsInRect2.reserve(4);
    bool found = false;
    \
    for (auto& [x, points] : pointsOnX) {
        auto y1It = points.begin();
        auto y2It = next(y1It);
        while(y1It != points.end()) {
            while (y2It != points.end()) {
                pointsInRect1.clear();
                pointsInRect2.clear();
                int size = *y2It - *y1It;

                processY(pointsOnY, pointsInRect1, x, x + size, *y1It, *y2It);
                processY(pointsOnY, pointsInRect2, x, x - size, *y1It, *y2It);

                found = checkResult(pointsInRect1, result, maxCount);
                if (found) {
                    break;
                }

                found = checkResult(pointsInRect2, result, maxCount);
                if (found) {
                    break;
                }

                ++y2It;
            }
            if (found) {
                break;
            }
            ++y1It;
        }
        if (found) {
            break;
        }
    }

    if (!found) {
        for (auto& [y, points] : pointsOnY) {
            auto x1It = points.begin();
            auto x2It = next(x1It);
            while(x1It != points.end()) {
                while (x2It != points.end()) {
                    pointsInRect1.clear();
                    pointsInRect2.clear();
                    int size = *x2It - *x1It;

                    processX(pointsOnX, pointsInRect1, *x1It, *x2It, y, y + size);
                    processX(pointsOnX, pointsInRect2, *x1It, *x2It, y, y - size);

                    found = checkResult(pointsInRect1, result, maxCount);
                    if (found) {
                        break;
                    }

                    found = checkResult(pointsInRect2, result, maxCount);
                    if (found) {
                        break;
                    }

                    ++x2It;
                }
                if (found) {
                    break;
                }
                ++x1It;
            }
            if (found) {
                break;
            }
        }
    }

    if (result.empty()) {
        auto it = pointsOnX.begin();
        Point point1{it->first, *it->second.begin()};
        result.push_back(point1);
        if (n != 1) {
            it = pointsOnY.begin();
            Point point2{*it->second.begin(), it->first};
            if (point2 == point1) {
                ++it;
                point2.x = *it->second.begin();
                point2.y = it->first;
            }
            result.push_back(point2);
        }
    }

    result = makeRect(result);

    printResult(result);

}
