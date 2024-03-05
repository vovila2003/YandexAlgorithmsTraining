#include "task1e.h"
#include <iostream>

using namespace std;

Task1E::Task1E()
{

}

void Task1E::doTask()
{
    int n, k, d;
    cin >> n >> k >> d;
    int64_t result = n;
    result = findNext(result, k);
    cout << result;
    if (result != -1) {
        cout << string(d - 1, '0');
    }
}

int64_t Task1E::findNext(int64_t current, int k)
{
    current *=10;
    for (int i = 0; i < 10; ++i) {
        if ((current + i) % k == 0) {
            return current + i;
        }
    }
    return -1;
}
