#include "task3h.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>

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
    Vector2 point1;
    Vector2 point2;

    Segment(Vector2 point1, Vector2 point2) : point1(point1), point2(point2) {}

    int64_t sqrLength() {
        Vector2 v = point2 - point1;
        return int64_t(v.x) * int64_t(v.x) + int64_t(v.y) * int64_t(v.y);
    }

    int64_t key() {
        int64_t tg = int64_t(1000000 * (double(point2.y) - double(point1.y)) / (double(point2.x) - double(point1.x)));
        size_t h1 = hash<int64_t>{}(tg);
        size_t h2 = hash<int64_t>{}(this->sqrLength());
        return h1 ^ (h2 << 1);
    }

    bool operator==(const Segment& other) const {
        return (point1 == other.point1 && point2 == other.point2) ||
               (point2 == other.point1 && point1 == other.point2);
    }
};

Segment operator+(const Segment& s, const Vector2& v) {
    return Segment(s.point1 + v, s.point2 + v);
}

struct SegmentHash
{
    size_t operator()(const Segment& s) const noexcept
    {
        size_t h1 = Vector2Hash{}(s.point1);
        size_t h2 = Vector2Hash{}(s.point2);
        return h1 ^ (h2 << 1);
    }
};

void Task3H::doTask()
{
    int n = 0;
    cin >> n;
    int x1, y1, x2, y2;
    unordered_map<int64_t, vector<Segment>> segmentsA; // key ->Segments
    unordered_map<int64_t, vector<Segment>> segmentsB;
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Vector2 point1(x1, y1);
        Vector2 point2(x2, y2);
        Segment segment(point1, point2);
        auto key = segment.key();
        segmentsA[key].push_back(segment);
    }
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Vector2 point1(x1, y1);
        Vector2 point2(x2, y2);
        Segment segment(point1, point2);
        auto key = segment.key();
        segmentsB[key].push_back(segment);
    }

    vector<Vector2> vectors;
    vectors.reserve(4 * n);
    for (auto& [key, vecA] : segmentsA) {
        if (segmentsB.count(key) == 0) {
            continue;
        }
        for (auto& segmentA : vecA) {
            for (auto& segmentB : segmentsB.at(key)) {
                vectors.push_back(segmentB.point1 - segmentA.point1);
                vectors.push_back(segmentB.point2 - segmentA.point1);
                vectors.push_back(segmentB.point1 - segmentA.point2);
                vectors.push_back(segmentB.point2 - segmentA.point2);
            }
        }
    }
    int maxCount = 0;
    for (auto& shift : vectors) {
        int count = 0;
        for (auto& [key, vecA] : segmentsA) {
            if (segmentsB.count(key) == 0) {
                continue;
            }
            for (auto& segmentA : vecA) {
                for (auto& segmentB : segmentsB.at(key)) {
                    if (segmentA + shift == segmentB) {
                        ++count;
                    }
                    maxCount = max(maxCount, count);
                }
            }
        }
    }

    cout << (n - maxCount);
}
