#include "task2c.h"

#include <iostream>

using namespace std;

Task2C::Task2C() {}

void Task2C::doTask()
{
    int n;
    cin >> n;
    bool first = true;
    int sum, maximum;
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
    if (maximum > (sum - maximum)) {
        result = maximum - (sum - maximum);
    } else {
        result = sum;
    }
    cout << result;
}
