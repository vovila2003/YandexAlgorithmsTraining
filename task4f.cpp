#include "task4f.h"

#include <iostream>
#include <vector>

using namespace std;

Task4F::Task4F() {}

template<class T>
void print(const vector<vector<T>>& data) {
    for (auto& vec: data) {
        for(auto v : vec) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int getColumnSum(int stX, int fX, int y, const vector<vector<int>>& plates) {
    int sum = 0;
    for (int i = stX; i < fX; ++i) {
        sum += plates[i][y];
    }
    return sum;
}

int getRowSum(int x, int stY, int fY, const vector<vector<int>>& plates) {
    int sum = 0;
    if (x < 0) {
        return 0;
    }
    for (int i = stY; i < fY; ++i) {
        sum += plates[x][i];
    }
    return sum;
}

int getSum(int stX, int stY, int fX, int fY, const vector<vector<int>>& plates) {
    int sum = 0;
    for (int i = stX; i < fX; ++i) {
        for(int j = stY; j < fY; ++j) {
            sum += plates[i][j];
        }
    }
    return sum;
}

bool checkWidth(int width, const vector<vector<int>>& plates, int w, int h, int n) {
    int x = 0;
    int sum1 = getSum(0, 0, h, width, plates);
    int sum2 = getSum(0, width, width, w, plates);
    int sum = sum1 + sum2;
    while(x <= h - width) {
        int y = 0;
        if (x != 0) {
            sum -= getRowSum(x - 1, width, w, plates);
            sum += getRowSum(x + width - 1, width, w, plates);
        }
        int currentSum = sum;
        while(y <= w - width) {
            if (y != 0) {
                int ss = getColumnSum(0, x, y - 1, plates);
                if (ss > 0) {
                    break;
                }
                currentSum -= ss;
                currentSum -= getColumnSum(x + width, h, y - 1, plates);
                currentSum += getColumnSum(0, x, y + width - 1, plates);
                currentSum += getColumnSum(x + width, h, y + width - 1, plates);
            }
            if (currentSum == n) {
                return true;
            }
            ++y;
        }
        ++x;
    }
    return false;
}

int calculate(int l, int r, const vector<vector<int>>& plates, int w, int h, int n) {
    while (l < r) {
        u_int64_t m = (u_int64_t(l) + r) / 2;
        if (checkWidth(m, plates, w, h, n)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

void Task4F::doTask()
{
    int w = 0;
    int h = 0;
    int n = 0;
    cin >> w >> h >> n;
    int x = 0;
    int y = 0;
    vector<vector<int>> plates = vector<vector<int>>(h, vector<int>(w, 0));
    for (int i = 0; i < n; ++i) {
        cin >> y >> x;
        plates[x - 1][y - 1] = 1;
    }

    auto result= calculate(1, min(w, h), plates, w, h, n);

    cout << result;
}

/*
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point& operator=(const Point& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
};

u_int64_t sqrDistance(Point&& p1, Point& p2) {
    return (u_int64_t(p1.x) - p2.x) * (u_int64_t(p1.x) - p2.x) +
            (u_int64_t(p1.y) - p2.y) * (u_int64_t(p1.y) - p2.y);
//    return (p1.x - p2.x) * (p1.x - p2.x) +
//            (p1.y - p2.y) * (p1.y - p2.y);
}

bool check(int width, const Point& p, Point& h1, Point& h2, Point& v1, Point& v2,
           vector<vector<int>>& minMax, int index) {
    int minH = min(min(h1.y, h2.y), p.y);
//    if (minMax[index][0] > minH) {
//        minMax[index][0] = minH;
//    }
    int maxH = max(max(h1.y, h2.y), p.y);
//    if (minMax[index][1] < maxH) {
//        minMax[index][1] = maxH;
//    }
    bool inHoriz = maxH - minH + 1 <= width;

    int minV = min(min(v1.x, v2.x), p.x);
//    if (minMax[index][2] > minV) {
//        minMax[index][2] = minV;
//    }
    int maxV = max(max(v1.x, v2.x), p.x);
//    if (minMax[index][3] < maxV) {
//        minMax[index][3] = maxV;
//    }
    bool inVert = maxV - minV + 1 <= width;



    return inHoriz || inVert;
}

void fillMinMax(vector<vector<int>>& minMax, Point& c1, Point& c2, Point& c3, Point& c4) {
    minMax[0][0] = min(c1.y, c2.y);
    minMax[0][1] = max(c1.y, c2.y);
    minMax[0][2] = min(c3.x, c4.x);
    minMax[0][3] = max(c3.x, c4.x);

    minMax[1][0] = min(c3.y, c4.y);
    minMax[1][1] = max(c3.y, c4.y);
    minMax[1][2] = min(c1.x, c2.x);
    minMax[1][3] = max(c1.x, c2.x);

    minMax[2][0] = min(c1.y, c3.y);
    minMax[2][1] = max(c1.y, c3.y);
    minMax[2][2] = min(c2.x, c4.x);
    minMax[2][3] = max(c2.x, c4.x);

    minMax[3][0] = min(c2.y, c4.y);
    minMax[3][1] = max(c2.y, c4.y);
    minMax[3][2] = min(c1.x, c3.x);
    minMax[3][3] = max(c1.x, c3.x);

    minMax[4][0] = min(c1.y, c4.y);
    minMax[4][1] = max(c1.y, c4.y);
    minMax[4][2] = min(c2.x, c3.x);
    minMax[4][3] = max(c2.x, c3.x);

    minMax[5][0] = min(c2.y, c3.y);
    minMax[5][1] = max(c2.y, c3.y);
    minMax[5][2] = min(c1.x, c4.x);
    minMax[5][3] = max(c1.x, c4.x);
}

bool checkWidth(int width, const vector<Point>& plates,
                Point& c1, Point& c2, Point& c3, Point& c4) {
    vector<bool> results(6, true);
    vector<vector<int>> minMax = vector<vector<int>>(6, vector<int>(4, 0));
    fillMinMax(minMax, c1, c2, c3, c4);
    for (auto& p : plates) {
        if (results[0]) {
            results[0] = results[0] && check(width, p, c1, c2, c3, c4, minMax, 0);
        }
        if (results[1]) {
            results[1] = results[1] && check(width, p, c3, c4, c1, c2, minMax, 1);
        }
        if (results[2]) {
            results[2] = results[2] && check(width, p, c1, c3, c2, c4, minMax, 2);
        }
        if (results[3]) {
            results[3] = results[3] && check(width, p, c2, c4, c1, c3, minMax, 3);
        }
        if (results[4]) {
            results[4] = results[4] && check(width, p, c1, c4, c2, c3, minMax, 4);
        }
        if (results[5]) {
            results[5] = results[5] && check(width, p, c2, c3, c1, c4, minMax, 5);
        }
        bool a = false;
        for (auto r :results) {
            a = a || r;
        }
        if (!a) {
            return false;
        }
    }
    return true;
}

int calculate(int l, int r, const vector<Point>& plates,
              Point& c1, Point& c2, Point& c3, Point& c4) {
    while (l < r) {
        u_int64_t m = (u_int64_t(l) + r) / 2;
        if (checkWidth(m, plates, c1, c2, c3, c4)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main()
{
    int w = 0;
    int h = 0;
    int n = 0;
    cin >> w >> h >> n;
    int x = 0;
    int y = 0;
    Point c1(0,0);
    Point c2(0,0);
    Point c3(0,0);
    Point c4(0,0);
    bool first = true;
    vector<Point> plates;
    plates.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        Point p(x,y);
        plates.push_back(p);
        if (first) {
            c1 = p;
            c2 = p;
            c3 = p;
            c4 = p;
            first = false;
        } else {
//            if (p.x < c1.x || (p.x == c1.x && p.y < c1.y)) {
//                c1 = p;
//            }
//            if (p.y > c2.y || (p.y == c2.y && p.x < c2.x)) {
//                c2 = p;
//            }
//            if (p.x > c3.x || (p.x == c3.x && p.y < c3.y)) {
//                c3 = p;
//            }
//            if (p.y < c4.y || (p.y == c4.y && p.x > c4.x)) {
//                c4 = p;
//            }
            if (sqrDistance(Point(1, 1), p) < sqrDistance(Point(1, 1), c1)) {
                c1 = p;
            }
            if (sqrDistance(Point(1, h), p) < sqrDistance(Point(1, h), c2)) {
                c2 = p;
            }
            if (sqrDistance(Point(w, 1), p) < sqrDistance(Point(w, 1), c3)) {
                c3 = p;
            }
            if (sqrDistance(Point(w, h), p) < sqrDistance(Point(w, h), c4)) {
                c4 = p;
            }
        }
    }


    auto result= calculate(1, min(w, h), plates, c1, c2, c3, c4);

    cout << result;
    return 0;
}



*/
