#include "task4f.h"

#include <iostream>
#include <vector>

using namespace std;

Task4F::Task4F() {}

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

bool check(int m, const vector<vector<u_int64_t>>& vec, int row, int column) {
    return vec[m][m] == 0;
}

int binarySearch(int l, int r,
                 const vector<vector<u_int64_t>>& vec, int row, int column,
                 bool (*fun)(int, const vector<vector<u_int64_t>>&, int, int)) {
    while (l < r) {
        u_int64_t m = (l + r + 1) / 2;
        if (fun(m, vec, row, column)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

vector<vector<u_int64_t>> getPresum(const vector<vector<int>>& plates) {
    size_t rows = plates.size();
    size_t columns = plates[0].size();
    vector<vector<u_int64_t>> presum1D = vector<vector<u_int64_t>>(rows, vector<u_int64_t>(columns + 1, 0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            presum1D[i][j + 1] = presum1D[i][j] + plates[i][j];
        }
    }
    vector<vector<u_int64_t>> presum2D = vector<vector<u_int64_t>>(rows + 1, vector<u_int64_t>(columns + 1, 0));
    for (size_t j = 1; j < columns + 1; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            presum2D[i + 1][j] = presum2D[i][j] + presum1D[i][j];
        }
    }
    return presum2D;
}

u_int64_t getSum(int lx, int ly, int rx, int ry, const vector<vector<u_int64_t>>& presum) {
    return presum[rx][ry] - presum[lx][ry] - presum[rx][ly] + presum [lx][ly];
}

void Task4F::doTask()
{
    int w = 0;
    int h = 0;
    int n = 0;
    cin >> w >> h >> n;
    int x = 0;
    int y = 0;
    vector<vector<int>> plates = vector<vector<int>>(h, vector<int>(w, 0));
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        plates[y - 1][x - 1] = 1;
    }

    auto presum = getPresum(plates);
    print(presum);
    auto result = getSum(4, 1, 6, 5, presum);

    cout << result;
}
