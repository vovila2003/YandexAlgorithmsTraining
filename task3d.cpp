#include "task3d.h"

#include <iostream>
#include <queue>
#include <set>

using namespace std;

Task3D::Task3D()
{

}

void Task3D::doTask()
{
    int n = 0;
    int k = 0;
    cin >> n >> k;
    queue<int> window;
    set<int> valuesSet;
    int value;
    bool result = false;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        if (result) continue;

        if (valuesSet.count(value) != 0) {
            result = true;
            continue;
        }

        if ((int)window.size() >= k) {
            int front = window.front();
            window.pop();
            valuesSet.erase(front);
        }

        window.push(value);
        valuesSet.insert(value);
    }
    if (result) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
