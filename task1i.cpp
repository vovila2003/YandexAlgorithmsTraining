#include "task1i.h"

#include <iostream>
#include <vector>

using namespace std;

Task1I::Task1I()
{

}

map<string, int> monthStringToInt {
    {"January", 0},
    {"February", 1},
    {"March", 2},
    {"April", 3},
    {"May", 4},
    {"June", 5},
    {"July", 6},
    {"August", 7},
    {"September", 8},
    {"October", 9},
    {"November", 10},
    {"December", 11}
};

map<int, string> weekdayIntToString {
    {0, "Sunday"},
    {1, "Monday"},
    {2, "Tuesday"},
    {3, "Wednesday"},
    {4, "Thursday"},
    {5, "Friday"},
    {6, "Saturday"},
};

void Task1I::doTask()
{
    int n, year;
    cin >> n >> year;
    std::vector<tm> holidays = readHolidays(n, year);

    string dayOfWeek;
    cin >> dayOfWeek;

    map<int, int> weekDayCounts = prepareWeekDayCounts(year);
    processHolidays(weekDayCounts, holidays);

    pair<int, int> result = findMinMax(weekDayCounts);

    cout << weekdayIntToString[result.second] << " " << weekdayIntToString[result.first];
}

void Task1I::test()
{

}

std::vector<tm> Task1I::readHolidays(int n, int year)
{
    vector<tm> holidays;
    for (int i = 0; i < n; ++i) {
        int day;
        string month;
        cin >> day >> month;
        tm holiday{};
        holiday.tm_year = year - 1900;
        holiday.tm_mon = monthStringToInt[month];
        holiday.tm_mday = day;
        mktime(&holiday);
        holidays.push_back(holiday);
    }
    return holidays;
}

std::map<int, int> Task1I::prepareWeekDayCounts(int year)
{
    map<int, int> weekDayCounts;
    tm day{};
    day.tm_year = year - 1900;
    day.tm_mon = 0;
    day.tm_mday = 1;
    mktime(&day);
    while (day.tm_year == year - 1900) {
        weekDayCounts[day.tm_wday]++;
        day.tm_mday++;
        mktime(&day);
    }
    return weekDayCounts;
}

void Task1I::processHolidays(std::map<int, int> &weekDayCounts, const std::vector<tm> &holidays)
{
    for (size_t i = 0; i < holidays.size(); ++i) {
        weekDayCounts[holidays[i].tm_wday]--;
    }
}

std::pair<int, int> Task1I::findMinMax(const std::map<int, int> &weekDayCounts)
{
    int maxIndex = 0;
    int max = weekDayCounts.at(maxIndex);

    int minIndex = 0;
    int min = weekDayCounts.at(minIndex);

    for (int i = 1; i < 7; ++i) {
        int value = weekDayCounts.at(i);
        if (value > max) {
            max = value;
            maxIndex = i;
        }
        if (value < min) {
            min = value;
            minIndex = i;
        }
    }
    return make_pair(minIndex, maxIndex);
}
