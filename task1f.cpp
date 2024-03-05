#include "task1f.h"
#include <algorithm>
#include <iostream>

using namespace std;

Task1F::Task1F()
{

}

void Task1F::doTask()
{
    int n;
    cin >> n;
    vector<int> numbers;
    numbers.reserve(n);
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        numbers.push_back(value);
    }
    vector<char> operations = process(numbers);
    for (size_t i = 0; i < operations.size(); ++i) {
        cout << operations[i];
    }
}

void Task1F::test()
{
    int start = 2;
    int end = 6;
    for (int i = 0; i < 100; i++) {
        int size = rand() % (end - start + 1) + start;
        vector<int> numbers;
        numbers.reserve(size);
        bool allEven = true;
        for (int i = 0; i < size; ++i) {
            int value = rand() / 10000000;
            allEven &= value % 2 == 0;
            numbers.push_back(value);
        }
        if (allEven) continue;
        vector<int> copy(numbers);
        vector<char> operations = process(numbers);
        auto result = calculate(copy, operations);

        print(copy, operations, result);
        if (result % 2 == 0) {
            return;
        }
    }
    cout << "DONE!";
}

std::vector<char> Task1F::process(std::vector<int> &numbers)
{
    vector<char> operations;
    operations.reserve(numbers.size() - 1);
    int next = numbers.back();
    numbers.pop_back();
    while(next % 2 == 0) {
        operations.push_back('+');
        next = numbers.back();
        numbers.pop_back();
    }

    while (!numbers.empty()) {
        int prev = numbers.back();
        if (prev % 2 == 0) {
            operations.push_back('+');
        } else {
            operations.push_back('x');
        }
        numbers.pop_back();
    }
    reverse(operations.begin(), operations.end());
    return operations;

}

int64_t Task1F::calculate(const std::vector<int> &numbers, const std::vector<char> &operations)
{
    int64_t result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (operations.at(i - 1) == 'x') {
            result *= numbers.at(i);
        } else {
            result += numbers.at(i);
        }
    }
    return result;
}

void Task1F::print(const std::vector<int> &numbers, const std::vector<char> &operations, int64_t result)
{
    cout << numbers.at(0);
    for (size_t i = 1; i < numbers.size(); ++i) {
        cout << " " << operations.at(i - 1) << " " << numbers.at(i);
    }
    cout << " = " << result << "\n\n";
}
