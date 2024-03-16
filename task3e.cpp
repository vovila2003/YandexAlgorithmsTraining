#include "task3e.h"

#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

Task3E::Task3E()
{

}

void Task3E::doTask()
{
    int n = 0;
    cin >> n;
    set<int> result;
    unordered_set<int> values1;
    int value;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        values1.insert(value);
    }
    cin >> n;
    unordered_set<int> values2;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        values2.insert(value);
        if (values1.count(value) != 0) {
            result.insert(value);
        }
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        if (values1.count(value) != 0 || values2.count(value)!= 0) {
            result.insert(value);
        }
    }
    for (int item : result) {
        cout << item << " ";
    }
}
