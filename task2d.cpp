#include "task2d.h"

#include <vector>
#include <iostream>

using namespace std;


Task2D::Task2D() {}

void Task2D::doTask()
{
    vector<vector<int>> board;
    int size = 10;
    for (int i = 0; i < size; ++i) {
        board.push_back(vector<int>(size, -1));
    }
    int n, x , y;
    cin >> n;
    vector<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        board[x][y] = 0;
        points.push_back(make_pair(x,y));
    }

    vector<int> dx {0, 1, 0, -1};
    vector<int> dy {1, 0, -1, 0};

    int perimeter = 0;
    for(auto xy: points) {
        x = xy.first;
        y = xy.second;
        for (size_t i = 0; i < dx.size(); ++i) {
            if (board[x + dx[i]][y + dy[i]] == -1) {
                ++perimeter;
            }
        }
    }
    cout << perimeter;
}
