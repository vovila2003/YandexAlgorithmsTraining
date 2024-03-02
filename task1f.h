#ifndef TASK1F_H
#define TASK1F_H

#include <algorithm>
#include <iostream>
#include <vector>

class Task1F
{
public:
    Task1F();
    void doTask();
    void test();
private:
    std::vector<char> process(std::vector<int>& numbers);
    int64_t calculate(const std::vector<int>& numbers, const std::vector<char>& operations);
    void print(const std::vector<int>& numbers,
               const std::vector<char>& operations, int64_t result);
};

#endif // TASK1F_H
