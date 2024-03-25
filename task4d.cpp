#include "task4d.h"
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Task4D::Task4D() {}

bool check(int m, const vector<u_int64_t>& vec, int width, int start) {
    u_int64_t symbolsInWords = vec[m] - vec[start];
    int spaces = m - start - 1;
    int resultSymbols = symbolsInWords + spaces;
    return resultSymbols <= width;
}

int binarySearchLines(int l, int r, const vector<u_int64_t>& vec, int width) {
    int start = l;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (check(m, vec, width, start)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int getLines(const vector<u_int64_t>& presum, int width) {
    int result = 0;
    int currentIndex = 0;
    while(true) {
        int nextIndex = binarySearchLines(currentIndex, presum.size() - 1, presum, width);
        if (nextIndex == currentIndex) {
            return -1;
        }
        if (presum[nextIndex] - presum[currentIndex] + nextIndex - currentIndex - 1 <= width) {
            ++result;
            currentIndex = nextIndex;
        }
        if (nextIndex >= presum.size() - 1) {
            break;
        }
    }
    return result;
}

int readData(istream& in, vector<int>& words, vector<u_int64_t>& presum, int n) {
    words.reserve(n);
    presum.reserve(n + 1);
    presum.push_back(0);
    int a = 0;
    int maxA = 0;
    u_int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        in >> a;
        sum += a;
        maxA = max(a, maxA);
        words.push_back(a);
        presum.push_back(sum);
    }
    return maxA;
}

pair<bool, int> targetFun(const vector<u_int64_t>& presum1, const vector<u_int64_t>& presum2, int w, int width) {
    int lines1 = getLines(presum1, w);
    if (lines1 == -1) {
        return make_pair(false, 0);
    }
    int lines2 = getLines(presum2, width - w);
    if (lines2 == -1) {
        return make_pair(false, 0);
    }
    return make_pair(true, abs(lines1 - lines2));
}

bool checkTargetFun(const vector<u_int64_t>& presum1, const vector<u_int64_t>& presum2, int w, int width) {
    auto value1 = targetFun(presum1, presum2, w, width);
    if (!value1.first) {
        return false;
    }
    auto value2 = targetFun(presum1, presum2, w + 1, width);
    if (!value2.first) {
        return false;
    }
    return value2.second < value1.second;
}

int binarySearch(const vector<u_int64_t>& presum1, const vector<u_int64_t>& presum2, int width, int minWidth, int maxWidth) {
    int l = minWidth;
    int r = maxWidth;
    while (l < r) {
        int m = (l + r) / 2;
        if (checkTargetFun(presum1, presum2, m, width)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

void calculate(istream& in, ostream& out) {
    int w = 0;
    int n = 0;
    int m = 0;
    in >> w >> n >> m;
    vector<int> words1;
    vector<u_int64_t> presum1;
    int minWidth1 = readData(in, words1, presum1, n);
    vector<int> words2;
    vector<u_int64_t> presum2;
    int minWidth2 = readData(in, words2, presum2, m);
    int maxWidth = w - minWidth2;
    int result = binarySearch(presum1, presum2, w, minWidth1, maxWidth);
    auto line1 = getLines(presum1, result);
    auto line2 = getLines(presum2, w - result);
    //cout << result << " " << line1 << " " << line2 << endl;
    out << max(line1, line2);
}

void test(istream& in, int answer, const string& name) {
    stringstream sout("");
    calculate(in, sout);
    int result = 0;
    sout >> result;
    cout << name << " ";
    if (answer == result) {
        cout << "OK" << endl;
    } else {
        cout << "FAIL: " << "need = " << answer << "; result = " << result << endl;
    }
}

void test1() {
    stringstream sin("15 6 6\n"
                     "2 2 2 3 2 2\n"
                     "3 3 5 2 4 3\n");
    int answer = 3;
    test(sin, answer, "test1");
}

void test2() {
    stringstream sin("10 10 10\n"
                     "4 1 2 2 3 2 5 2 2 1\n"
                     "4 1 4 1 5 5 1 2 2 3\n");
    int answer = 9;
    test(sin, answer, "test2");
}

void test11() {
    stringstream sin("1000 1 1000\n"
                     "744\n"
                     "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n");
    int answer = 8;
    test(sin, answer, "test11");
}

void test16() {
    stringstream sin("10 5 5\n"
                     "1 1 1 1 1\n"
                     "5 2 3 3 4\n");
    int answer = 4;
    test(sin, answer, "test16");
}


void tests() {
    test1();
    test2();
    test11();
    test16();
}

void Task4D::doTask()
{
    //calculate(cin, cout);
    tests();
}


