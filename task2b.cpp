#include "task2b.h"
#include <iostream>
#include <vector>

using namespace std;

Task2B::Task2B() {}

void Task2B::doTask()
{
    int days, goodFishDays, price;
    cin >> days >> goodFishDays;
    vector<int> prices;
    for (int i = 0; i < days; ++i) {
        cin >> price;
        prices.push_back(price);
    }
    prices.push_back(-1);
    int result = 0;
    int today = 0;
    while(true) {
        int buyPrice = prices.at(today);
        if (buyPrice == -1) {
            break;
        }
        int offset = 1;
        while(offset <= goodFishDays) {
            int soldPrice = prices.at(today + offset);
            if (soldPrice == -1) {
                break;
            }
            int candidate = soldPrice - buyPrice;
            if (candidate > result) {
                result = candidate;
            }
            ++offset;
        }
        ++today;
    }
    cout << result;
}
