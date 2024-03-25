#include "task4d.h"
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Task4D::Task4D() {}

bool check(int m, const vector<u_int64_t>& vec, u_int64_t width, u_int64_t start) {
    u_int64_t symbolsInWords = vec[m] - vec[start];
    u_int64_t spaces = m - start - 1;
    u_int64_t resultSymbols = symbolsInWords + spaces;
    return resultSymbols <= width;
}

u_int64_t binarySearchLines(u_int64_t l, u_int64_t r, const vector<u_int64_t>& vec, u_int64_t width) {
    u_int64_t start = l;
    while (l < r) {
        u_int64_t m = (l + r + 1) / 2;
        if (check(m, vec, width, start)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

u_int64_t getLines(const vector<u_int64_t>& presum, int width) {
    u_int64_t result = 0;
    u_int64_t currentIndex = 0;
    while(true) {
        int nextIndex = binarySearchLines(currentIndex, presum.size() - 1, presum, width);
        if (nextIndex == currentIndex) {
            return -1;
        }
        auto sumR = presum[nextIndex];
        auto sumL = presum[currentIndex];
        auto symbols = sumR - sumL;
        auto spaces = nextIndex - currentIndex - 1;
        auto resultSymbols = symbols + spaces;
        if (resultSymbols <= width) {
            ++result;
            currentIndex = nextIndex;
        }
        if (nextIndex >= presum.size() - 1) {
            break;
        }
    }
    return result;
}

u_int64_t readData(istream& in, vector<u_int64_t>& presum, int n) {
    presum.reserve(n + 1);
    presum.push_back(0);
    int a = 0;
    int maxA = 0;
    u_int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        in >> a;
        sum += a;
        maxA = max(a, maxA);
        presum.push_back(sum);
    }
    return maxA;
}

u_int64_t binarySearch(const vector<u_int64_t>& presum1, const vector<u_int64_t>& presum2,
                 u_int64_t width, u_int64_t minWidth, u_int64_t maxWidth) {
    u_int64_t l = minWidth;
    u_int64_t r = maxWidth;
    u_int64_t l1 = getLines(presum1, l);
    u_int64_t l2 = getLines(presum2, width - r);
    while (l < r) {
        if (r - l == 1) {
            l1 = getLines(presum1, l);
            l2 = getLines(presum2, width - l);
            u_int64_t resL = max(l1, l2);
            l1 = getLines(presum1, r);
            l2 = getLines(presum2, width - r);
            u_int64_t resR = max(l1, l2);
            if (resL <= resR) {
                return resL;
            }
            return resR;
        }

        u_int64_t m = (l + r) / 2;
        l1 = getLines(presum1, m);
        l2 = getLines(presum2, width - m);
        if (l1 > l2) {
            l = m;
        } else {
            r = m;
        }
    }
    return max(l1, l2);
}

void calculate(istream& in, ostream& out) {

    int w = 0;
    int n = 0;
    int m = 0;
    in >> w >> n >> m;
    vector<u_int64_t> presum1;
    presum1.reserve(n);
    u_int64_t minWidth1 = readData(in, presum1, n);
    vector<u_int64_t> presum2;
    presum2.reserve(m);
    u_int64_t minWidth2 = readData(in, presum2, m);
    u_int64_t maxWidth = w - minWidth2;
    u_int64_t result = binarySearch(presum1, presum2, w, minWidth1, maxWidth);
    out << result;
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

void test9() {
    stringstream sin("1000 1000 1\n"
                     "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n"
                     "438\n");
    int answer = 4;
    test(sin, answer, "test9");
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
    test9();
    test11();
    test16();
}

void Task4D::doTask()
{
    //calculate(cin, cout);
    tests();
}


