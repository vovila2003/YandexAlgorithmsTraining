#ifndef TASK2I_H
#define TASK2I_H

#include <istream>
#include <vector>


class Task2I
{
public:
    Task2I();
    void doTask();
    void runTests();

private:
    int64_t calculate(std::istream& stream);
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
    void test8();
    void test9();
    void test15();
};


#endif // TASK2I_H
