#ifndef TASK1E_H
#define TASK1E_H

#include <cstdint>

class Task1E
{
public:
    Task1E();
    void doTask();
private:
    int64_t findNext(int64_t current, int k);
};

#endif // TASK1E_H
