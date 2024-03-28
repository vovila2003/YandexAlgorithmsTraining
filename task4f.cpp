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
}

pair<bool, bool> checkHoriz(int width, const Point& p, const Point& h1, const Point& h2,
           const vector<Point>& sides) {
    int baseHorizWidth = abs(h1.y - h2.y) + 1;
    if (baseHorizWidth > width) {
        return make_pair(false, false);
    }

    int dist1 = abs(p.y - sides[1].y) + 1;
    bool res1 = dist1 <= width;

    int dist2 = abs(p.y - sides[2].y) + 1;
    bool res2 = dist2 <= width;

    return make_pair(res1, res2);
}

pair<bool, bool> checkVert(int width, const Point& p, const Point& v1, const Point& v2,
                           const vector<Point>& sides) {
    int baseVertWidth = abs(v1.x - v2.x) + 1;
    if (baseVertWidth > width) {
        return make_pair(false, false);
    }

    int dist1 = abs(p.x - sides[0].x) + 1;
    bool res1 = dist1 <= width;

    int dist2 = abs(p.x - sides[3].x) + 1;
    bool res2 = dist2 <= width;

    return make_pair(res1, res2);
}

bool checkWidth(int width, const vector<Point>& plates,
                const vector<Point>& coners, const vector<Point>& sides) {
    vector<bool> results(24, true);
    for (auto& p : plates) {
        if (results[0] || results[1]) {
            auto resHoriz = checkHoriz(width, p, coners[0], coners[1], sides);
            results[0] = results[0] && resHoriz.first;
            results[1] = results[0] && resHoriz.second;
        }
        if (results[2] || results[3]) {
            auto resVert = checkVert(width, p, coners[2], coners[3], sides);
            results[2] = results[2] && resVert.first;
            results[3] = results[3] && resVert.second;
        }

        if (results[4] || results[5]) {
            auto resHoriz = checkHoriz(width, p, coners[2], coners[3], sides);
            results[4] = results[4] && resHoriz.first;
            results[5] = results[5] && resHoriz.second;
        }
        if (results[6] || results[7]) {
            auto resVert = checkVert(width, p, coners[0], coners[1], sides);
            results[6] = results[6] && resVert.first;
            results[7] = results[7] && resVert.second;
        }

        if (results[8] || results[9]) {
            auto resHoriz = checkHoriz(width, p, coners[0], coners[2], sides);
            results[8] = results[8] && resHoriz.first;
            results[9] = results[9] && resHoriz.second;
        }
        if (results[10] || results[11]) {
            auto resVert = checkVert(width, p, coners[1], coners[3], sides);
            results[10] = results[10] && resVert.first;
            results[11] = results[11] && resVert.second;
        }

        if (results[12] || results[13]) {
            auto resHoriz = checkHoriz(width, p, coners[1], coners[3], sides);
            results[12] = results[12] && resHoriz.first;
            results[13] = results[13] && resHoriz.second;
        }
        if (results[14] || results[15]) {
            auto resVert = checkVert(width, p, coners[0], coners[2], sides);
            results[14] = results[14] && resVert.first;
            results[15] = results[15] && resVert.second;
        }

        if (results[16] || results[17]) {
            auto resHoriz = checkHoriz(width, p, coners[0], coners[3], sides);
            results[16] = results[16] && resHoriz.first;
            results[17] = results[17] && resHoriz.second;
        }
        if (results[18] || results[19]) {
            auto resVert = checkVert(width, p, coners[1], coners[2], sides);
            results[18] = results[18] && resVert.first;
            results[19] = results[19] && resVert.second;
        }

        if (results[20] || results[21]) {
            auto resHoriz = checkHoriz(width, p, coners[1], coners[2], sides);
            results[20] = results[20] && resHoriz.first;
            results[21] = results[21] && resHoriz.second;
        }
        if (results[22] || results[23]) {
            auto resVert = checkVert(width, p, coners[0], coners[3], sides);
            results[22] = results[22] && resVert.first;
            results[23] = results[23] && resVert.second;
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
              const vector<Point>& coners, const vector<Point>& sides) {
    while (l < r) {
        u_int64_t m = (u_int64_t(l) + r) / 2;
        if (checkWidth(m, plates, coners, sides)) {
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
    vector<Point> coners = vector<Point>(4, Point(0,0));
    vector<Point> sides = vector<Point>(4, Point(0,0));
    bool first = true;
    vector<Point> plates;
    plates.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        Point p(x,y);
        plates.push_back(p);
        if (first) {
            for (int i = 0; i < 4; ++i) {
                coners[i] = p;
                sides[i] = p;
            }
            first = false;
        } else {
            if (p.x < sides[0].x) {
                sides[0] = p;
            }
            if (p.y < sides[1].y) {
                sides[1] = p;
            }
            if (p.y > sides[2].y) {
                sides[2] = p;
            }
            if (p.x > sides[3].x) {
                sides[3] = p;
            }
            if (sqrDistance(Point(1, 1), p) < sqrDistance(Point(1, 1), coners[0])) {
                coners[0] = p;
            }
            if (sqrDistance(Point(1, h), p) < sqrDistance(Point(1, h), coners[1])) {
                coners[1] = p;
            }
            if (sqrDistance(Point(w, 1), p) < sqrDistance(Point(w, 1), coners[2])) {
                coners[2] = p;
            }
            if (sqrDistance(Point(w, h), p) < sqrDistance(Point(w, h), coners[3])) {
                coners[3] = p;
            }


        }
    }


    auto result= calculate(1, min(w, h), plates, coners, sides);

    cout << result;
    return 0;
}




*/
