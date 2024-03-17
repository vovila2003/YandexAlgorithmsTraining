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
    int x = 0;
    int y = 0;

    Vector2(int x, int y) : x(x), y(y) {}

    Vector2(const Vector2& other) : x(other.x), y(other.y) {}

    Vector2() {}

    Vector2& operator=(const Vector2& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    bool operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2 &other) const {
        return !(*this == other);
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

    bool operator==(const Segment& other) const {
        return vector == other.vector && startPoint == other.startPoint;
    }

    bool operator<(const Segment& other) const {
        if (vector != other.vector) {
            return vector < other.vector;
        }
        return startPoint < other.startPoint;
    }
};


struct SegmentHash
{
    size_t operator()(const Segment& s) const noexcept
    {
        size_t h1 = Vector2Hash{}(s.vector);
        size_t h2 = Vector2Hash{}(s.startPoint);
        return h1 ^ (h2 << 1);
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

    unordered_map<Vector2, vector<Segment>, Vector2Hash> vectorsSegmentsA;
    unordered_map<Vector2, vector<Segment>, Vector2Hash> vectorsSegmentsB;

    for (size_t i = 0; i < segmentsA.size(); ++i) {
        auto& segment = segmentsA.at(i);
        if (commonVectors.count(segment.vector) == 0) {
            continue;
        }
        vectorsSegmentsA[segment.vector].push_back(segment);
    }


    for (size_t i = 0; i < segmentsB.size(); ++i) {
        auto& segment = segmentsB.at(i);
        if (commonVectors.count(segment.vector) == 0) {
            continue;
        }
        vectorsSegmentsB[segment.vector].push_back(segment);
    }

    set<Segment> setA;
    for (auto& [v, vec] : vectorsSegmentsA) {
        for(auto& ss : vec) {
            setA.insert(ss);
        }
    }
    int maxCount = 0;
    for (auto& [vec, segA] : vectorsSegmentsA) {
        for (Segment& base : segA) {
            for (Segment& other : vectorsSegmentsB[vec]) {

                Vector2 shift = base.startPoint - other.startPoint;

                set<Segment> setB;
                for (auto& [v, vec] : vectorsSegmentsB) {
                    for(auto ss : vec) {
                        ss.startPoint = ss.startPoint + shift;
                        setB.insert(ss);
                    }
                }

                set<Segment> common;
                set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                                 inserter(common, common.begin()));

                int count = common.size();
                maxCount = max(count, maxCount);
            }
        }
    }
    cout << n - maxCount;
}
