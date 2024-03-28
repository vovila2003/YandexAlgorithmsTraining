#include "task4g.h"

#include <iostream>
#include <vector>

Task4G::Task4G() {}

using namespace std;

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

u_int64_t getSum(int lx, int ly, int rx, int ry, const vector<vector<u_int64_t>>& presum) {
    return presum[rx][ry] - presum[lx][ry] - presum[rx][ly] + presum [lx][ly];
}

int countInCrest(int x, int y, int k, const vector<vector<u_int64_t>>& vec) {
    auto center = getSum(x, y + k, x + 3 * k, y + 2* k, vec);
    auto left = getSum(x + k, y, x + 2 * k, y + k, vec);
    auto right = getSum(x + k, y + 2 * k, x + 2 * k, y + 3 * k, vec);
    auto result = center + left + right;
    return result;
}

bool check(int k, const vector<vector<u_int64_t>>& vec, int n, int m) {
    for (int x = 0; x <= n - 3 * k; ++x) {
        for (int y = 0; y <= m - 3 * k; ++y) {
            if (countInCrest(x, y, k, vec) == 5 * k * k) {
                return true;
            }
        }
    }
    return false;
}

int binarySearch(int l, int r,
                 const vector<vector<u_int64_t>>& vec,
                 bool (*fun)(int, const vector<vector<u_int64_t>>&, int, int), int n, int m) {
    while (l < r) {
        u_int64_t med = (l + r + 1) / 2;
        if (fun(med, vec, n, m)) {
            l = med;
        } else {
            r = med - 1;
        }
    }
    return l;
}

vector<vector<u_int64_t>> getPresum(const vector<vector<int>>& data) {
    size_t rows = data.size();
    size_t columns = data[0].size();
    vector<vector<u_int64_t>> b = vector<vector<u_int64_t>>(rows + 1, vector<u_int64_t>(columns + 1, 0));
    for (size_t j = 0; j < columns; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            b[i + 1][j + 1] = b[i][j + 1] + b[i + 1][j] - b[i][j] + data[i][j];
        }
    }
    return b;
}

void Task4G::doTask()
{
    int n = 0;
    int m = 0;
    cin >> n >> m;

    vector<vector<int>> data = vector<vector<int>> (n, vector<int>(m, 0));
    string str;
    for (int i = 0; i < n; ++i) {
        cin >> str;
        for(int j = 0; j < m; ++j) {
            if (str[j] == '#') {
                data[i][j] = 1;
            }
        }
    }
    print(data);

    auto presum = getPresum(data);
    print(presum);
    auto result = binarySearch(1, min(n, m) / 3, presum, &check, n, m);

    cout << result;
}
