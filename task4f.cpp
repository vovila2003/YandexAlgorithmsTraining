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

//bool check(int m, const vector<vector<u_int64_t>>& vec, int row, int column) {
//    return vec[m][m] == 0;
//}

//int binarySearch(int l, int r,
//                 const vector<vector<u_int64_t>>& vec, int row, int column,
//                 bool (*fun)(int, const vector<vector<u_int64_t>>&, int, int)) {
//    while (l < r) {
//        u_int64_t m = (l + r + 1) / 2;
//        if (fun(m, vec, row, column)) {
//            l = m;
//        } else {
//            r = m - 1;
//        }
//    }
//    return l;
//}

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



bool checkWidth(int width, const vector<vector<u_int64_t>>& presum, int w, int h) {
    int x = 0;
    u_int64_t lu = 0;
    u_int64_t ld = 0;
    u_int64_t ru = 0;
    u_int64_t rd = 0;
    while(x <= h - width) {
        int y = 0;
        while(y <= w - width) {
            lu = getSum(0, 0, x, y, presum);
            if (lu != 0) {
                break;
            }
            ld = getSum(x + width, 0, h, y, presum);
            ru = getSum(0, y + width, x, w, presum);
            rd = getSum(x + width, y + width, h, w, presum);
            if (ld == 0 && ru == 0 && rd == 0) {
                return true;
            }
            ++y;
        }
        ++x;
        if (getSum(0, 0, x, 1, presum) != 0) {
            break;
        }
    }
    return false;
}

int calculate(int l, int r, const vector<vector<u_int64_t>>& presum, int w, int h) {
    while (l < r) {
        u_int64_t m = (l + r) / 2;
        if (checkWidth(m, presum, w, h)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
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
        cin >> y >> x;
        plates[x - 1][y - 1] = 1;
    }

    auto presum = getPresum(plates);
    auto result= calculate(1, min(w, h), presum, w, h);

    cout << result;
}
