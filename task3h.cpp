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

    Segment(const Segment& other) : vector(other.vector), startPoint(other.startPoint) {}

    Segment& operator=(const Segment& other) {
        vector = other.vector;
        startPoint = other.startPoint;
        return *this;
    }

    bool operator==(const Segment& other) const {
        return vector == other.vector && startPoint == other.startPoint;
    }

    bool operator<(const Segment& other) const {
        if (startPoint == other.startPoint) {
            return vector < other.vector;
        }
        return startPoint < other.startPoint;
    }
};


struct SegmentHash
{
    size_t operator()(const Segment& s) const noexcept
    {
        size_t h1 = Vector2Hash{}(s.startPoint);
        size_t h2 = Vector2Hash{}(s.vector);
        return h1 ^ (h2 << 1);
    }
};

struct SegmentsDiff {
    Vector2 vector1;
    Vector2 vector2;

    SegmentsDiff(Segment segment1, Segment segment2) {
        vector1 = segment2.startPoint - segment1.startPoint;
        vector2 = segment2.startPoint + segment2.vector - (segment1.startPoint + segment1.vector);
    }

    Vector2 sum() const {
        Vector2 result = Vector2(0, 0);
        result = result + vector1;
        result = result + vector2;
        return result;
    }

    SegmentsDiff(const SegmentsDiff& other) : vector1 (other.vector1), vector2(other.vector2){}

    SegmentsDiff& operator=(const SegmentsDiff& other) {
        vector1 = other.vector1;
        vector2 = other.vector2;
        return *this;
    }

    bool operator<(const SegmentsDiff& other) const {
        return sum() < other.sum();
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

 map<Segment, vector<SegmentsDiff>> makeDeltas(const vector<Segment>& segments) {
     map<Segment, vector<SegmentsDiff>> delta;
    for (size_t i = 0; i < segments.size(); ++i) {
        auto& segment1 = segments[i];
        for (size_t j = 0; j < segments.size(); ++j) {
            if (i == j) continue;
            auto& segment2 = segments[j];
            SegmentsDiff diff = SegmentsDiff(segment1, segment2);
            delta[segment1].push_back(std::move(diff));
        }
    }
    return delta;
}

 map<Vector2, vector<Segment>> makeVectorToSegment(const vector<Segment>& segments) {
     map<Vector2, vector<Segment>> result;
     for (size_t i = 0; i < segments.size(); ++i) {
         Segment seg = segments[i];
         result[segments[i].vector].push_back(std::move(seg));
     }
     return result;
 }

set<Vector2> makeVectorsSet(const vector<Segment>& segments) {
     set<Vector2> result;
     for (size_t i = 0; i < segments.size(); ++i) {
         Vector2 vec = segments[i].vector;
         result.insert(std::move(vec));
     }
     return result;
}

int intersect(const vector<SegmentsDiff>& set1, const vector<SegmentsDiff>& set2) {
    map<SegmentsDiff, int> common;
    for (auto& diff: set1) {
        ++common[diff];
    }
    for (auto& diff: set2) {
        ++common[diff];
    }
    int result = 0;
    for (auto& [diff, c] : common) {
        if (c == 2) {
            ++result;
        }
    }
    return result;
}

void Task3H::doTask()
{
    int n = 0;
    cin >> n;

    vector<Segment> segmentsA = readSegments(n);
    map<Segment, vector<SegmentsDiff>> deltaA = makeDeltas(segmentsA);
    map<Vector2, vector<Segment>> vectorToSegmentA = makeVectorToSegment(segmentsA);
    set<Vector2> vectorSetA = makeVectorsSet(segmentsA);

    vector<Segment> segmentsB = readSegments(n);
    map<Segment, vector<SegmentsDiff>> deltaB = makeDeltas(segmentsB);
    map<Vector2, vector<Segment>> vectorToSegmentB = makeVectorToSegment(segmentsB);
    set<Vector2> vectorSetB = makeVectorsSet(segmentsB);

    set<Vector2> commonVectors;
    set_intersection(vectorSetA.begin(), vectorSetA.end(), vectorSetB.begin(), vectorSetB.end(), inserter(commonVectors, commonVectors.end()));

    if (commonVectors.empty()) {
        cout << 0;
        return;
    }

    int maxCount = 0;
    for (auto& commonVector : commonVectors) {
        for (auto& segmentA : vectorToSegmentA[commonVector]) {
            for (auto& segmentB : vectorToSegmentB[commonVector]) {
                auto& setA = deltaA[segmentA];
                auto& setB = deltaB[segmentB];
                int count = intersect(setA, setB);
                cout << count << endl;
                maxCount = max(maxCount, count);
            }
        }
    }

    cout << endl << (n - maxCount) << endl;
}
