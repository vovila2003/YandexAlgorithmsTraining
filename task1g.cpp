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
    cout << calculateRounds(300, 301, 484) << " = 6" << "\n";
    cout << calculateRounds(250, 500, 230) << " = 8" << "\n";
    cout << calculateRounds(250, 500, 249) << " = 101" << "\n";
    cout << calculateRounds(25, 100, 10) << " = 8" << "\n";
    cout << calculateRounds(250, 500, 218) << " = 6" << "\n";
}

int Task1G::calculateRounds(int x, int y, int p)
{
    int round = 1;
    int soldiers = 0;
    double k = (1 + sqrt(5.0)) / 2.0;
    int prevX = x;
    int prevY = y;
    int prevSoldiers = 0;
    cout << "round = 0; x = " << x
         << "; y = " << y << "; soldiers = " << soldiers << "\n";
    int yy, xx, ss, rr;
    bool save = true;
    while (x > 0) {

        double koef = (y + soldiers) * 1.0 / x;
        if (y > x) {
            koef = (y + soldiers + p) * 1.0 / x;
        }
        if ( koef <= k) {
            if (save) {
                yy = y;
                xx = x;
                ss = soldiers;
                rr = round;
                save = false;
            }
            int damage = x > y ? y : x;
            y -= damage;
            soldiers -= x - damage;
            cout << "attack barrack; ";
        } else {
            if (3 * x >= 2 * (soldiers + y)) {
                int damage = x > y ? y : x;
                y -= damage;
                soldiers -= x - damage;
                cout << "attack barrack; ";
            } else {
                int damage = x > soldiers ? soldiers : x;
                soldiers -= damage;
                y -= x - damage;
                cout << "attack soldiers; ";
            }
        }



        x -= soldiers;
        if (y > 0) {
            soldiers += p;
        }
        cout.precision(4);
        cout << "round = " << round << "; koef = "  << koef << "; x = " << x
             << "; y = " << y << "; soldiers = " << soldiers << "\n";
        if (y <= 0 && soldiers <= 0) {
            break;
        }

        round++;
        if (x == prevX && y == prevY && soldiers == prevSoldiers) {
            round = -1;
            break;
        }
        prevSoldiers = soldiers;
        prevX = x;
        prevY = y;
    }
    int firstAnswer = x < 0 ? -1 : round;
    x = xx;
    y = yy;
    soldiers = ss;
    round = rr;
    prevSoldiers = soldiers;
    prevX = x;
    prevY = y;
    bool attackSoldiersFirst = true;
    while (x > 0) {

        double koef = (y + soldiers) * 1.0 / x;
        if (y > x) {
            koef = (y + soldiers + p) * 1.0 / x;
        }
        if (attackSoldiersFirst) {
            int damage = x > soldiers ? soldiers : x;
            soldiers -= damage;
            y -= x - damage;
            cout << "attack soldiers; ";
            attackSoldiersFirst = false;
        }
        else if ( koef <= k) {
            int damage = x > y ? y : x;
            y -= damage;
            soldiers -= x - damage;
            cout << "attack barrack; ";
        } else {
            if (3 * x >= 2 * (soldiers + y)) {
                int damage = x > y ? y : x;
                y -= damage;
                soldiers -= x - damage;
                cout << "attack barrack; ";
            } else {
                int damage = x > soldiers ? soldiers : x;
                soldiers -= damage;
                y -= x - damage;
                cout << "attack soldiers; ";
            }
        }



        x -= soldiers;
        if (y > 0) {
            soldiers += p;
        }
        cout.precision(4);
        cout << "round = " << round << "; koef = "  << koef << "; x = " << x
             << "; y = " << y << "; soldiers = " << soldiers << "\n";
        if (y <= 0 && soldiers <= 0) {
            break;
        }

        round++;
        if (x == prevX && y == prevY && soldiers == prevSoldiers) {
            round = -1;
            break;
        }
        prevSoldiers = soldiers;
        prevX = x;
        prevY = y;
    }
    int secondAnswer = x < 0 ? -1 : round;
    if (firstAnswer == secondAnswer) return firstAnswer;
    if (firstAnswer == -1 && secondAnswer != -1) return secondAnswer;
    if (firstAnswer != -1 && secondAnswer == -1) return firstAnswer;
    return min(firstAnswer, secondAnswer);
}
