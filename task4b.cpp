#include "task4b.h"

#include <iostream>
#include <algorithm>
#include <stdint.h>

using namespace std;


Task4B::Task4B()
{

}

u_int64_t calculate(u_int64_t k) {
    if (k == 0) return 0;
    long double x = k;
    long double tmp = x * (x + 1) * (x + 2) / 6 + (1 + x) * x / 2 - 1;
    auto limit = UINT64_MAX;
    if (tmp >= limit) {
        return limit;
    }
    u_int64_t result = 0;
    if ((k * (k+1)) % 6 == 0) {
        result = k * (k + 1) / 6 * (k + 2);
    } else if ((k * (k + 2)) % 6 == 0) {
        result = k * (k + 2) / 6 * (k + 1);
    } else {
        result = (k + 1) * (k + 2) / 6 * k;
    }
    result += (1 + k) * k / 2 - 1;
    return result;
}

bool check(u_int64_t n, u_int64_t k) {
    auto calc = calculate(k);
    return calc <= n;
}

u_int64_t binarySearch(u_int64_t l, u_int64_t r, u_int64_t n) {
    while (l < r) {
        u_int64_t m = (l + r + 1) / 2;
        if (check(n, m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

bool test(u_int64_t n, u_int64_t ans) {
    auto result = binarySearch(0, n, n);
    cout << "n = " << n << "; result = " << result;
    if (result == ans) {
         cout << " OK" << endl;
         return true;
    }
    cout << " FAIL!!! " << "   answer = " << ans <<  endl;
    return false;
}

void Task4B::doTask()
{
    bool res = true;
    res &= test(1, 1);
    res &= test(5, 1);
    res &= test(7, 2);
    res &= test(1000000000000000000, 1817118);
    res &= test(117055765888857794, 888887);
    res &= test(973622521965965999, 1800999);

    if (res) {
        cout << endl << "ALL OK" << endl;
    } else {
        cout << endl << "FAIL" << endl;

    }

//    u_int64_t n = 0;
    //cin >> n;
    //auto result = binarySearch(0, n, n);
    //cout << result;
}
