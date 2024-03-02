#include "task1a.h"

using namespace std;

Task1A::Task1A()
{

}

bool Task1A::isIntersect(int p, int v, int q, int m)
{
    return abs(p - q) <= v + m;
}

void Task1A::doTask()
{
    int p, v, q, m, result;
    cin >> p >> v >> q >> m;
    if (isIntersect(p, v, q, m))
    {
        result = max(p + v, q + m) - min(p - v, q - m) + 1;
    }
    else
    {
        result = 2 * (v + m + 1);
    }

    cout << result;
}
