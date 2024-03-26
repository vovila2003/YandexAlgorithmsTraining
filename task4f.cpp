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

bool checkDiag(int m, const vector<vector<u_int64_t>>& vec, int row, int column) {
    return vec[m][m] == 0;
}

bool checkHorizontal(int m, const vector<vector<u_int64_t>>& vec, int row, int column) {
    return vec[row][m] == 0;
}

bool checkVertical(int m, const vector<vector<u_int64_t>>& vec, int row, int column) {
    return vec[m][column] == 0;
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

pair<int, int> calculate(const vector<vector<u_int64_t>>& vec) {
    int rows = vec.size();
    int columns = vec[0].size();
    int diag = binarySearch(0, min(rows, columns) - 1, vec, 0, 0, &checkDiag);
    if (diag == 0) {
        return make_pair(0, 0);
    }
    int x = diag;
    int y = diag;
    if (diag < rows - 1 && vec[diag + 1][diag] == 0) {
        x = binarySearch(x, rows - 1, vec, 0, diag, &checkVertical);
    }
    if (diag < columns - 1 && vec[diag][diag + 1] == 0) {
        y = binarySearch(y, columns - 1, vec, diag, 0, &checkHorizontal);
    }
    if (x > y) {
        return make_pair(x, diag);
    }
    return make_pair(diag, y);
}

pair<int, int> getPresumLeftUp(const vector<vector<int>>& plates) {
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
    return calculate(presum2D);
}

pair<int, int> getPresumRightUp(const vector<vector<int>>& plates) {
    size_t rows = plates.size();
    size_t columns = plates[0].size();
    vector<vector<u_int64_t>> presum1D = vector<vector<u_int64_t>>(rows, vector<u_int64_t>(columns + 1, 0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            presum1D[i][j + 1] = presum1D[i][j] + plates[i][columns - j - 1];
        }
    }
    vector<vector<u_int64_t>> presum2D = vector<vector<u_int64_t>>(rows + 1, vector<u_int64_t>(columns + 1, 0));
    for (size_t j = 1; j < columns + 1; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            presum2D[i + 1][j] = presum2D[i][j] + presum1D[i][j];
        }
    }
    return calculate(presum2D);
}

pair<int, int> getPresumLeftDown(const vector<vector<int>>& plates) {
    size_t rows = plates.size();
    size_t columns = plates[0].size();
    vector<vector<u_int64_t>> presum1D = vector<vector<u_int64_t>>(rows, vector<u_int64_t>(columns + 1, 0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            presum1D[i][j + 1] = presum1D[i][j] + plates[rows - i - 1][j];
        }
    }
    vector<vector<u_int64_t>> presum2D = vector<vector<u_int64_t>>(rows + 1, vector<u_int64_t>(columns + 1, 0));
    for (size_t j = 1; j < columns + 1; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            presum2D[i + 1][j] = presum2D[i][j] + presum1D[i][j];
        }
    }
    return calculate(presum2D);
}

pair<int, int> getPresumRightDown(const vector<vector<int>>& plates) {
    size_t rows = plates.size();
    size_t columns = plates[0].size();
    vector<vector<u_int64_t>> presum1D = vector<vector<u_int64_t>>(rows, vector<u_int64_t>(columns + 1, 0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            presum1D[i][j + 1] = presum1D[i][j] + plates[rows - i - 1][columns - j - 1];
        }
    }
    vector<vector<u_int64_t>> presum2D = vector<vector<u_int64_t>>(rows + 1, vector<u_int64_t>(columns + 1, 0));
    for (size_t j = 1; j < columns + 1; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            presum2D[i + 1][j] = presum2D[i][j] + presum1D[i][j];
        }
    }
    return calculate(presum2D);
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

    auto [a1, b1] = getPresumLeftUp(plates);
    auto [a2, b2] = getPresumRightUp(plates);
    auto [a3, b3] = getPresumLeftDown(plates);
    auto [a4, b4] = getPresumRightDown(plates);

    int left = min(b1, b3);
    int right = min(b2, b4);
    int width = w - left - right;

    int up = min(a1, a2);
    int down = min(a3, a4);
    int height = h - up - down;

    int result = 0;
    if (width == w || height == h) {
        result = min(w, h);
    } else {
        result = max(width, height);
    }

    cout << result;
}
