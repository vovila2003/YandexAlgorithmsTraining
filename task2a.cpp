#include "task2a.h"
#include <iostream>

using namespace std;

Task2A::Task2A() {}



void Task2A::doTask()
{
    int k;
    cin >> k;
    int minX, maxX, minY, maxY, x, y;
    bool isFirst = true;
    for (int i = 0; i < k; ++i) {
        cin >> x >> y;
        if (isFirst) {
            minX = x;
            maxX = x;
            minY = y;
            maxY = y;
            isFirst = false;
        } else {
            maxX = max(x, maxX);
            minX = min(x, minX);
            maxY = max(y, maxY);
            minY = min(y, minY);
        }
    }
    cout << minX << " " << minY << " " << maxX << " " << maxY;
}
