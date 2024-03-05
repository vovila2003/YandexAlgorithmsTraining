#ifndef TASK1I_H
#define TASK1I_H

#include <ctime>
#include <map>
#include <vector>

class Task1I
{
public:
    Task1I();
    void doTask();
    void test();
private:
    std::vector<tm> readHolidays(int n, int year);
    std::map<int, int> prepareWeekDayCounts(int year);
    void processHolidays(std::map<int, int>& weekDayCounts, const std::vector<tm>& holidays);
    std::pair<int, int> findMinMax(const std::map<int, int>& weekDayCounts);
};

#endif // TASK1I_H
