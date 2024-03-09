#include "task2g.h"

#include <iostream>
#include <vector>

using namespace std;

Task2G::Task2G() {}

void Task2G::doTask()
{
    int t;
    cin >> t;
    for (int tests = 0; tests < t; ++tests) {
        int n;
        cin >> n;
        int count = 0;
        vector<int> segments;
        int currentLenght = 0;
        int maxLenght;
        bool first = true;
        for (int i = 0; i < n; ++i) {
            int value;
            cin >> value;
            if (first) {
                maxLenght = value;
                currentLenght = 1;
                first = false;
            } else {
                if (value < currentLenght + 1) {
                    segments.push_back(currentLenght);
                    ++count;
                    maxLenght = value;
                    currentLenght = 1;
                } else {
                    ++currentLenght;
                    if (maxLenght > value) {
                        maxLenght = value;
                    }
                }
            }
            if (currentLenght >= maxLenght) {
                segments.push_back(currentLenght);
                ++count;
                first = true;
            }
        }

        if (!first && currentLenght >= 1) {
            segments.push_back(currentLenght);
            ++count;
        }
        cout << count << endl;
        for (auto length : segments) {
            cout << length << " ";
        }
        cout << endl;
    }

}
