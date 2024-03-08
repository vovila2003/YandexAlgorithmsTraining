#include "task2c.h"

#include <iostream>

using namespace std;

Task2C::Task2C() {}

void Task2C::doTask()
{
    int n;
    cin >> n;
    bool first = true;
    int sum = 0;
    int maximum = 0;
    for (int i = 0; i < n; ++i) {
        int current;
        cin >> current;
        if (first) {
            sum = current;
            maximum = current;
            first = false;
        } else {
            sum += current;
            maximum = max(maximum, current);
        }
    }
    int result;
    if (2 * maximum > sum) {
        result = 2 * maximum - sum;
    } else {
        result = sum;
    }
    cout << result;
}
