#include "task4a.h"

#include <algorithm>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

Task4A::Task4A()
{

}

int find(const vector<int>& data, int l, int r) {
    auto itL = lower_bound(data.begin(), data.end(), l);
    auto itR = upper_bound(data.begin(), data.end(), r);
    return itR - itL;
}

void Task4A::doTask()
{
    int n = 0;
    int value = 0;
    cin >> n;
    multiset<int> dataSet;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        dataSet.insert(value);
    }
    vector<int> data(dataSet.begin(), dataSet.end());
    int k = 0;
    cin >> k;
    int l = 0;
    int r = 0;
    for (int i = 0; i < k; ++i) {
        cin >> l >> r;
        cout << find(data, l, r) << " ";
    }
}
