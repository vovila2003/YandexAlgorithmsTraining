#include "task3h.h"

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>

using namespace std;

Task3H::Task3H()
{

}

struct Vector2
{
    int x;
    int y;

    Vector2(int x, int y) : x(x), y(y) {}

    bool operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Vector2 other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

struct Vector2Hash
{
    size_t operator()(const Vector2& p) const noexcept
    {
        size_t h1 = hash<int>{}(p.x);
        size_t h2 = hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

Vector2 operator-(const Vector2& left, const Vector2& right)
{
    return Vector2{left.x - right.x, left.y - right.y};
}

Vector2 operator+(const Vector2& left, const Vector2& right)
{
    return Vector2{left.x + right.x, left.y + right.y};
}

struct Segment {
    Vector2 vector;
    Vector2 startPoint;

    Segment(Vector2 point1, Vector2 point2) : vector(0,0), startPoint(0, 0) {
        if (point1.x > point2.x) {
            vector = point1 - point2;
            startPoint = point2;
        } else if (point1.x < point2.x) {
            vector = point2 - point1;
            startPoint = point1;
        } else {
            if (point1.y > point2.y) {
                vector = point1 - point2;
                startPoint = point2;
            } else {
                vector = point2 - point1;
                startPoint = point1;
            }
        }
    }
};

void Task3H::doTask()
{
    int n = 0;
    cin >> n;
    int x1, y1, x2, y2;
    set<Vector2> vectorsA;
    vector<Segment> segmentsA;
    segmentsA.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Vector2 point1(x1, y1);
        Vector2 point2(x2, y2);
        Segment segment(point1, point2);
        segmentsA.push_back(segment);
        vectorsA.insert(segment.vector);
    }
    set<Vector2> vectorsB;
    vector<Segment> segmentsB;
    segmentsB.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Vector2 point1(x1, y1);
        Vector2 point2(x2, y2);
        Segment segment(point1, point2);
        segmentsB.push_back(segment);
        vectorsB.insert(segment.vector);
    }
    set<Vector2> commonVectors;
    set_intersection(vectorsA.begin(), vectorsA.end(), vectorsB.begin(), vectorsB.end(),
                     inserter(commonVectors, commonVectors.begin()));
    unordered_map<Vector2, unordered_map<Vector2, vector<Vector2>, Vector2Hash>, Vector2Hash> matrixA;
    unordered_map<Vector2, unordered_map<Vector2, vector<Vector2>, Vector2Hash>, Vector2Hash> matrixB;
    for (auto& v :commonVectors) {
        matrixA[v][v] = vector<Vector2>();
        matrixB[v][v] = vector<Vector2>();
    }
    for (size_t i = 0; i < segmentsA.size() - 1; ++i) {
        for (size_t j = i + 1; j < segmentsA.size(); ++j) {
            auto& segment1 = segmentsA.at(i);
            auto& segment2 = segmentsA.at(j);
            if (matrixA.count(segment1.vector) == 0 || matrixA.count(segment2.vector) == 0) {
                continue;
            }
            Vector2 delta21 = segment2.startPoint - segment1.startPoint;
            Vector2 delta12 = segment1.startPoint - segment2.startPoint;
            matrixA[segment1.vector][segment2.vector].push_back(delta12);
            matrixA[segment2.vector][segment1.vector].push_back(delta21);
        }
    }

    for (size_t i = 0; i < segmentsB.size() - 1; ++i) {
        for (size_t j = i + 1; j < segmentsB.size(); ++j) {
            auto& segment1 = segmentsB.at(i);
            auto& segment2 = segmentsB.at(j);
            if (matrixB.count(segment1.vector) == 0 || matrixB.count(segment2.vector) == 0) {
                continue;
            }
            Vector2 delta21 = segment2.startPoint - segment1.startPoint;
            Vector2 delta12 = segment1.startPoint - segment2.startPoint;
            matrixB[segment1.vector][segment2.vector].push_back(delta12);
            matrixB[segment2.vector][segment1.vector].push_back(delta21);
        }
    }

    int maxCount = -1;
    for (auto& [key, mapA] : matrixA) {
        auto& mapB = matrixB[key];
        int count = 0;
        for (auto& [key2, vecA] : mapA) {
            vector<Vector2> common;
            auto& vecB = mapB[key2];
            sort(vecA.begin(), vecA.end());
            sort(vecB.begin(), vecB.end());
            set_intersection(vecA.begin(), vecA.end(), vecB.begin(), vecB.end(),
                             back_inserter(common));
            count += common.size();
        }
        maxCount = max(count, maxCount);
    }

    int result = 0;
    if (maxCount == -1) {
        result = n;
    } else {
        result = n - (maxCount + 1);
    }
    cout << endl << result << endl;
}
