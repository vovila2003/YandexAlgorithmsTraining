#include "task4c.h"

#include <sys/types.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Task4C::Task4C()
{

}

bool check(u_int64_t m, const vector<u_int64_t>& vec, u_int64_t value, uint delta) {
    if (m + delta >= vec.size()) {
        return false;
    }
    return vec[m + delta] - vec[m] <= value;
}

u_int64_t binarySearch(u_int64_t l, u_int64_t r, const vector<u_int64_t>& vec,
                       u_int64_t value, uint delta) {
    while (l < r) {
        u_int64_t m = (l + r + 1) / 2;
        if (check(m, vec, value, delta)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int calculate(const vector<u_int64_t>& presum, uint l, u_int64_t s) {
    if (presum.size() < 1) {
        return -1;
    }

    auto ans = binarySearch(0, presum.size() - 1, presum, s, l);
    if (presum[ans + l] - presum[ans] == s) {
        return ans + 1;
    }
    return -1;
}

void Task4C::doTask()
{
    uint n = 0;
    uint m = 0;
    cin >> n >> m;
    uint a = 0;
    vector<u_int64_t> orks;
    orks.reserve(n);
    vector<u_int64_t> presum;
    presum.reserve(n + 1);
    presum.push_back(0);
    u_int64_t sum = 0;
    for (uint i = 0 ; i < n; ++i) {
        cin >> a;
        orks.push_back(a);
        sum += a;
        presum.push_back(sum);
    }

    uint l = 0;
    u_int64_t s = 0;
    vector<int> results;
    results.reserve(m);
    for (uint i = 0; i < m; ++i) {
        cin >> l >> s;
        results.push_back(calculate(presum, l, s));
    }
    stringstream ss("");
    bool first = true;
    for (auto v : results) {
        if (first) {
            ss << v;
            first = false;
        } else {
            ss << "\n" << v;
        }
    }
    cout << ss.str();
}
