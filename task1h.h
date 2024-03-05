#ifndef TASK1H_H
#define TASK1H_H

#include <utility>

class Task1H
{
public:
    Task1H();
    void doTask();
    void test();
private:
    std::pair<bool, double> calculate(double l, double stK, double vK, double stA, double vA);
    void printAnswer(std::pair<bool, double> result, double rightAnswer);
};

#endif // TASK1H_H
