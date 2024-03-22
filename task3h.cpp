#include "task3h.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

Task3H::Task3H()
{

}



const int Q = 73;

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
        size_t hash = p.x;
        hash *= Q;
        hash += p.y;
        return hash;
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

    size_t hash;

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
        size_t h = startPoint.x;
        h *= Q;
        h += startPoint.y;
        h *= Q;
        h += vector.x;
        h *= Q;
        h += vector.y;
        hash = h;
    }

    Segment(const Segment& other) : vector(other.vector), startPoint(other.startPoint), hash(other.hash) {}

    Segment& operator=(const Segment& other) {
        vector = other.vector;
        startPoint = other.startPoint;
        hash = other.hash;
        return *this;
    }

    bool operator==(const Segment& other) const {
        return hash == other.hash;
    }

    bool operator<(const Segment& other) const {
        return hash < other.hash;
    }
};

struct SegmentsDiff {
    Vector2 vector1;
    Vector2 vector2;
    size_t hash;

    SegmentsDiff(Segment segment1, Segment segment2) {
        vector1 = segment2.startPoint - segment1.startPoint;
        vector2 = segment2.startPoint + segment2.vector - (segment1.startPoint + segment1.vector);
        size_t h = vector1.x;
        h *= Q;
        h += vector1.y;
        h *= Q;
        h += vector2.x;
        h *= Q;
        h += vector2.y;
        hash = h;
    }

    SegmentsDiff(const SegmentsDiff& other) : vector1 (other.vector1), vector2 (other.vector2), hash(other.hash) {}

    SegmentsDiff& operator=(const SegmentsDiff& other) {
        vector1 = other.vector1;
        vector2 = other.vector2;
        hash = other.hash;
        return *this;
    }

    bool operator<(const SegmentsDiff& other) const {
        return hash < other.hash;
    }

    bool operator== (const SegmentsDiff& other) const {
        return hash == other.hash;
    }
};

struct SegmentsDiffHash
{
    size_t operator()(const SegmentsDiff& s) const noexcept
    {
        return s.hash;
    }
};

vector<Segment> readSegments(int n) {
    int x1, y1, x2, y2;
    vector<Segment> segments;
    segments.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Vector2 point1(x1, y1);
        Vector2 point2(x2, y2);
        Segment segment(point1, point2);
        segments.push_back(std::move(segment));
    }
    return segments;
}

set<Vector2> makeVectorsSet(const vector<Segment>& segments) {
     set<Vector2> result;
     for (size_t i = 0; i < segments.size(); ++i) {
         Vector2 vec = segments[i].vector;
         result.insert(vec);
     }
     return result;
}

int main1()
{
    int n = 0;
    cin >> n;

    vector<Segment> segmentsA = readSegments(n);
    set<Vector2> vectorSetA = makeVectorsSet(segmentsA);

    vector<Segment> segmentsB = readSegments(n);
    set<Vector2> vectorSetB = makeVectorsSet(segmentsB);

    set<Vector2> commonVectors;
    set_intersection(vectorSetA.begin(), vectorSetA.end(), vectorSetB.begin(), vectorSetB.end(),
                     inserter(commonVectors, commonVectors.end()));
    int result = 0;
    if (!commonVectors.empty()) {
        int maxCount = 0;
        unordered_map<SegmentsDiff, int, SegmentsDiffHash> distances;
        for (const Segment& segmentA : segmentsA) {
            for (const Segment& segmentB : segmentsB) {
                auto diff = SegmentsDiff(segmentA, segmentB);
                ++distances[diff];
            }
        }

        for (auto& [d, c] : distances) {
            maxCount = max(c, maxCount);
        }

        result = n - maxCount;
    } else {
        result = n;
    }

    cout << result;
    return 0;
}

void Task3H::doTask()
{
    main1();
}

