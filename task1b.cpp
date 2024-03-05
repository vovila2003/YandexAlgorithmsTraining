#include "task1b.h"

#include <iostream>

using namespace std;

Task1B::Task1B()
{

}

void Task1B::doTask()
{
    int g1, g2, q1, q2, m, result;
    char c;
    cin >> g1 >> c >> g2 >> q1 >> c >> q2 >> m;
    result = g2 + q2 - g1 - q1;
    if (result < 0) {
        result = 0;
    } else {
        if ((m == 1 && g2 >= q1 + result) ||
            (m == 2 && q2 >= g1)) {
            result++;
        }
    }
    cout << result;
}
