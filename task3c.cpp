#include "task3c.h"

#include <iostream>
#include <map>

using namespace std;

Task3C::Task3C()
{

}

void Task3C::doTask()
{
    int n = 0;
    cin >> n;
    map<int, int> digits;
    int digit;
    for (int i = 0; i < n; ++i) {
        cin >> digit;
        ++digits[digit];
    }

    int maxCountValue = digits.begin()->first;
    int maxCount = digits.begin()->second;
    for (auto [value, count] : digits) {
        if (digits.count(value + 1) != 0) {
            count += digits[value + 1];
        }
        if (count > maxCount) {
            maxCount = count;
            maxCountValue = value;
        }
    }

    int result = 0;
    for (auto [value, count] : digits) {
        if (value - maxCountValue == 1 || value == maxCountValue) {
            continue;
        }
        result += count;
    }

    cout << result;
}
