#include "task2i.h"

#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

Task2I::Task2I() {}

void Task2I::doTask()
{
    int n;
    cin >> n;
    vector<int64_t> distances = vector<int64_t>(n, 0);
    distances.reserve(n);
    int row, column;
    map<int, int> rowToCount;
    for (int i = 0; i < n; ++i) {
        cin >> row >> column;
        for (int j = 0; j < n; ++j) {
            distances[j] += abs(j + 1 - column);
        }
        rowToCount[row]++;
    }

    int minColumnIndex = 0;
    int minColumn = distances[0];
    for (int i = 1;  i < n; ++i) {
        if (minColumn > distances.at(i)) {
            minColumn = distances.at(i);
            minColumnIndex = i;
        }
    }
    int64_t horizontalSteps = distances[minColumnIndex];

    vector<int> orderedRows;
    orderedRows.reserve(n);
    for (auto p : rowToCount) {
        row = p.first;
        for (int i = 0; i < p.second; ++i) {
            orderedRows.push_back(row);
        }
    }

    int64_t verticalSteps = 0;
    for (int i = 0; i < (int)orderedRows.size(); ++i) {
        verticalSteps += abs(orderedRows.at(i) - (i + 1));
    }

    cout << (horizontalSteps + verticalSteps);
}

void Task2I::runTests()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test15();
    cout << "OK" << endl;
}


int64_t Task2I::calculate(istream &stream)
{
    int n;
    stream >> n;
    vector<int64_t> distances = vector<int64_t>(n, 0);
    distances.reserve(n);
    int row, column;
    map<int, int> rowToCount;
    for (int i = 0; i < n; ++i) {
        stream >> row >> column;
        for (int j = 0; j < n; ++j) {
            distances[j] += abs(j + 1 - column);
        }
        rowToCount[row]++;
    }

    int minColumnIndex = 0;
    int minColumn = distances[0];
    for (int i = 1;  i < n; ++i) {
        if (minColumn > distances.at(i)) {
            minColumn = distances.at(i);
            minColumnIndex = i;
        }
    }
    int64_t horizontalSteps = distances[minColumnIndex];

    vector<int> orderedRows;
    orderedRows.reserve(n);
    for (auto p : rowToCount) {
        row = p.first;
        for (int i = 0; i < p.second; ++i) {
            orderedRows.push_back(row);
        }
    }

    int64_t verticalSteps = 0;
    for (int i = 0; i < (int)orderedRows.size(); ++i) {
        verticalSteps += abs(orderedRows.at(i) - (i + 1));
    }

    return (horizontalSteps + verticalSteps);
}

void Task2I::test1()
{
    stringstream ss(
        "5 "
        "1 1 "
        "2 2 "
        "3 3 "
        "4 4 "
        "5 5 "
        );
    auto result = calculate(ss);
    assert(result == 6);
}

void Task2I::test2()
{
    stringstream ss(
        "10 "
        "3 7 "
        "7 10 "
        "4 9 "
        "2 2 "
        "5 9 "
        "8 2 "
        "5 5 "
        "10 4 "
        "2 10 "
        "6 5 "
        );
    auto result = calculate(ss);
    assert(result == 32);
}

void Task2I::test3()
{
    stringstream ss(
        "10 "
        "3 7 "
        "7 10 "
        "4 9 "
        "2 2 "
        "5 9 "
        "8 2 "
        "5 5 "
        "10 4 "
        "2 10 "
        "6 5 "
        );
    auto result = calculate(ss);
    assert(result == 32);
}

void Task2I::test4()
{
    stringstream ss(
        "1 "
        "1 1 "
        );
    auto result = calculate(ss);
    assert(result == 0);
}

void Task2I::test5()
{
    stringstream ss(
        "3 "
        "1 1 "
        "1 2 "
        "1 3 "
        );
    auto result = calculate(ss);
    assert(result == 5);
}

void Task2I::test6()
{
    stringstream ss(
        "3 "
        "1 1 "
        "2 2 "
        "1 3 "
        );
    auto result = calculate(ss);
    assert(result == 4);
}

void Task2I::test7()
{
    stringstream ss(
        "3 "
        "1 1 "
        "2 1 "
        "3 1 "
        );
    auto result = calculate(ss);
    assert(result == 0);
}

void Task2I::test8()
{
    stringstream ss(
        "3 "
        "1 1 "
        "2 2 "
        "3 3 "
        );
    auto result = calculate(ss);
    assert(result == 2);
}

void Task2I::test9()
{
    stringstream ss(
        "3 "
        "1 2 "
        "2 2 "
        "3 3 "
        );
    auto result = calculate(ss);
    assert(result == 1);
}

void Task2I::test15()
{
    stringstream ss(
        "10 "
        "4 4 "
        "10 2 "
        "5 5 "
        "5 1 "
        "1 8 "
        "9 3 "
        "9 6 "
        "8 5 "
        "1 9 "
        "4 5 "
        );
    auto result = calculate(ss);
    assert(result == 23);
}
