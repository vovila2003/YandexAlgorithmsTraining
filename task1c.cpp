#include "task1c.h"

using namespace std;

Task1C::Task1C()
{

}

void Task1C::doTask()
{
    int n;
    cin >> n;
    int64_t result = 0;
    for (int i = 0; i < n; ++i) {
        int spaceCount;
        cin >> spaceCount;
        result += calculateSpace(spaceCount);
    }
    cout << result;
}

int Task1C::calculateSpace(int count)
{
    int result = count / 4; // количество целых табов
    count %= 4; // остаток
    if (count != 0) {
        if (count == 1) {
            ++result;
        } else {
            result += 2;
        }
    }
    return result;
}
