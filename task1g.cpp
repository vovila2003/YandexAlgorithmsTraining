#include "task1g.h"
#include <memory>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

struct Node {
    Node* parent;
    int x;
    int y;
    int soldiers;
    int round;
    bool done;
};

Task1G::Task1G()
{

}

void Task1G::doTask()
{
    int x, y, p;
    cin >> x >> y >> p;
    int round = calculate(x, y, p);
    cout << round;
}

void Task1G::test()
{
    cout << calculate(10, 11, 15) << " = 4" << "\n";
    cout << calculate(1, 2, 1) << " = -1" << "\n";
    cout << calculate(1, 1, 1) << " = 1" << "\n";
    cout << calculate(25, 200, 10) << " = 13" << "\n";
    cout << calculate(250, 500, 187) << " = 4" << "\n";
    cout << calculate(250, 500, 225) << " = 7" << "\n";
    cout << calculate(300, 301, 484) << " = 6" << "\n";
    cout << calculate(250, 500, 230) << " = 8" << "\n";
    cout << calculate(250, 500, 249) << " = 101" << "\n";
    cout << calculate(25, 100, 10) << " = 6" << "\n";
    cout << calculate(250, 500, 218) << " = 6" << "\n";
    cout << calculate(9, 427, 1) << " = 54" << "\n";
}

int Task1G::calculate(int x, int y, int p)
{
    minRound_ = std::numeric_limits<int>::max();
    auto rootNode = make_shared<Node>();
    rootNode->x = x;
    rootNode->y = y;
    rootNode->soldiers = 0;
    rootNode->round = 0;
    rootNode->done = false;

    process(rootNode, p);

    if (minRound_ == std::numeric_limits<int>::max()) {
        return -1;
    }
    return minRound_;
}

shared_ptr<Node> Task1G::processSoldiersAttack(Node* parent, int p)
{
    auto result = make_shared<Node>();
    result->parent = parent;
    result->done = false;

    if (parent->round >= minRound_) {
        result->done = true;
        return result;
    }

    int x = parent->x;
    int y = parent->y;
    int soldiers = parent->soldiers;
    int round = parent->round;

    int damage = x > soldiers ? soldiers : x;
    soldiers -= damage;
    y -= x - damage;

    x -= soldiers;
    if (y > 0) {
        soldiers += p;
    }
    round++;
    result->x = x;
    result->y = y;
    result->soldiers = soldiers;
    result->round = round;

    if (y <= 0 && soldiers <= 0) {
        result->done = true;
        if (minRound_ > round) {
            minRound_ = round;
        }
    }

    if (x <= 0 || (x == parent->x && y == parent->y && soldiers == parent->soldiers)) {
        result->done = true;
    }
    return result;
}

std::shared_ptr<Node> Task1G::processBarrackAttack(Node *parent, int p)
{
    auto result = make_shared<Node>();
    result->parent = parent;
    result->done = false;

    if (parent->round >= minRound_) {
        result->done = true;
        return result;
    }

    int x = parent->x;
    int y = parent->y;
    int soldiers = parent->soldiers;
    int round = parent->round;

    int damage = x > y ? y : x;
    y -= damage;
    soldiers -= x - damage;

    x -= soldiers;
    if (y > 0) {
        soldiers += p;
    }
    round++;
    result->x = x;
    result->y = y;
    result->soldiers = soldiers;
    result->round = round;

    if (y <= 0 && soldiers <= 0) {
        result->done = true;
        if (minRound_ > round) {
            minRound_ = round;
        }
    }

    if (x <= 0 || (x == parent->x && y == parent->y && soldiers == parent->soldiers)) {
        result->done = true;
    }
    return result;
}

void Task1G::process(shared_ptr<Node> root, int p)
{
    queue<shared_ptr<Node>> queue;
    queue.push(root);

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        auto attackSoldierNode = processSoldiersAttack(node.get(), p);
        if (!attackSoldierNode->done) {
            queue.push(std::move(attackSoldierNode));
        }
        double k = (node->y + p) * 1.0 / node->x;
        if (k < 2) {
            auto attackBarrackNode = processBarrackAttack(node.get(), p);
            if (!attackBarrackNode->done) {
                queue.push(std::move(attackBarrackNode));
            }
        }
    }
}
