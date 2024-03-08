#include "task2e.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

Task2E::Task2E() {}

void Task2E::doTask()
{
    int n;
    cin >> n;
    int a, b;
    map<int, map<int, int>> deltas;
    for(int i = 0; i < n; ++i) {
        cin >> a >> b;
        int delta = a - b;
        if (delta < 0) {
            delta = -1;
        }
        if (deltas.count(delta) == 0) {
            deltas[delta] = map<int, int>();
        }
        deltas[delta][a] = i;
    }
    int64_t current = 0;
    int64_t maxValue = 0;
    vector<int> order;
    order.reserve(n);
    for (auto it = deltas.rbegin(); it != deltas.rend(); ++it) {
        const auto& indexes = it->second;
        for (auto it2 = indexes.rbegin(); it2 != indexes.rend(); ++it2) {
            if (maxValue < current + it2->first) {
                maxValue = current + it2->first;
            }
            current += it->first;
            order.push_back(it2->second);
        }
    }
    cout << maxValue << endl;
    for(int ind : order) {
        cout << (ind + 1) << " ";
    }
}
