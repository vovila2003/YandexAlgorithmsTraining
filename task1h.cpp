#include "task1h.h"
#include <iostream>
#include <set>

using namespace std;

Task1H::Task1H()
{

}

void Task1H::doTask()
{
    double l, stK, vK, stA, vA;
    cin >> l >> stK >> vK >> stA >> vA;

    auto result = calculate(l, stK, vK, stA, vA);

    if (result.first) {
        cout << "YES" << "\n";
        cout.precision(10);
        cout << result.second;
    } else {
        cout << "NO";
    }
}

void Task1H::test()
{
    printAnswer(calculate(6, 3, 1, 1, 1), 1.0);
    printAnswer(calculate(12, 8, 10, 5, 20), 0.3);
    printAnswer(calculate(5, 0, 0, 1, 2), 2);
    printAnswer(calculate(10, 7, -3, 1, 4), 0.8571428571);
    printAnswer(calculate(762899414, 556082848, -539099316, 556082848, -582799403), 0);
    printAnswer(calculate(94, 76, 0, 76, 0), 0);
}

pair<bool , double> Task1H::calculate(double l, double stK, double vK, double stA, double vA)
{
    if (stK + stA == l || stK == stA) {
        return make_pair(true, 0);
    }

    if (vK == 0 && vA == 0){
        return make_pair(false, 0);
    }

    int n = 0;
    set<double> currentAnswers;
    set<double> answers;
    while(true) {
        currentAnswers.clear();
        double t;
        if (vK != vA) {
            t = (stA - stK + l * n) / (vK - vA);
            if (t >= 0) {
                currentAnswers.insert(t);
            }
            t = (stA - stK - l * n) / (vK - vA);
            if (t >= 0) {
                currentAnswers.insert(t);
            }
        }

        if (vK != -vA) {
            t = (-stA - stK + l * n) / (vK + vA);
            if (t >= 0) {
                currentAnswers.insert(t);
            }
            t = (-stA - stK - l * n) / (vK + vA);
            if (t >= 0) {
                currentAnswers.insert(t);
            }
        }

        if (!currentAnswers.empty()) {
            answers.insert(*currentAnswers.begin());
            if (answers.size() >= 2) {
                break;
            }
        }
        n++;
    }
    return make_pair(true, *answers.begin());
}

void Task1H::printAnswer(std::pair<bool, double> result, double rightAnswer)
{
    if (result.first) {
        cout << "YES" << "\n";
        cout.precision(10);
        cout << result.second << " = " << rightAnswer;
    } else {
        cout << "NO";
    }
    cout << "\n\n";
}
