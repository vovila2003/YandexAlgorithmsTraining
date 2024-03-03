#include "task1g.h"
#include <cmath>

using namespace std;

Task1G::Task1G()
{

}

void Task1G::doTask()
{
    int x, y, p;
    cin >> x >> y >> p;
    int round = calculateRounds(x, y, p);
    cout << round;
}

void Task1G::test()
{
    cout << calculateRounds(10, 11, 15) << " = 4" << "\n";
    cout << calculateRounds(1, 2, 1) << " = -1" << "\n";
    cout << calculateRounds(1, 1, 1) << " = 1" << "\n";
    cout << calculateRounds(25, 200, 10) << " = 13" << "\n";
    cout << calculateRounds(250, 500, 187) << " = 4" << "\n";
    cout << calculateRounds(250, 500, 225) << " = 7" << "\n";
}

int Task1G::calculateRounds(int x, int y, int p)
{
    int round = 1;
    int soldiers = 0;
    double k = (1 + sqrt(5.0)) / 2.0;
    int prevX = x;
    int prevY = y;
    int prevSoldiers = 0;
    while (x > 0) {
        if (((y + p) * 1.0 / x) <= k) {
            int damage = x > y ? y : x;
            y -= damage;
            soldiers -= x - damage;
        } else {
            if (y < x && 2 * x - soldiers - y >= soldiers + y - x) {
                int damage = x > y ? y : x;
                y -= damage;
                soldiers -= x - damage;
            } else {
                int damage = x > soldiers ? soldiers : x;
                soldiers -= damage;
                y -= x - damage;
            }
        }
        if (y <= 0 && soldiers <= 0) {
            break;
        }
        x -= soldiers;
        if (y > 0) {
            soldiers += p;
        }
        round++;
        if (x == prevX && y == prevY && soldiers == prevSoldiers) return -1;
        prevSoldiers = soldiers;
        prevX = x;
        prevY = y;
    }
    return x <= 0 ? -1 : round;
}
