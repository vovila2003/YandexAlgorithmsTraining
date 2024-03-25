#include "task4e.h"
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

Task4E::Task4E()
{

}

u_int64_t getDiag(u_int64_t n) {
    long double diag = (sqrt(1 + 8 * (long double)n) - 1) / 2;
    u_int64_t round = diag;
    if (diag > round) {
        ++round;
    }
    return round;
}

void Task4E::doTask()
{
    u_int64_t n;
    cin >> n;
    u_int64_t diag = getDiag(n);
    bool fromDownToUp = diag % 2 == 0;
    u_int64_t prevSum = diag * (diag - 1) / 2;
    u_int64_t delta = n - prevSum;
    u_int64_t row = 0;
    u_int64_t column = 0;
    if (fromDownToUp) {
        row = diag - delta + 1;
        column = delta;
    } else {
        row = delta;
        column = diag - delta + 1;
    }

    cout << row << "/" << column;

}
