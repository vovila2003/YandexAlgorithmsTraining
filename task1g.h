#ifndef TASK1G_H
#define TASK1G_H

#include <memory>

struct Node ;

class Task1G
{
public:
    Task1G();
    void doTask();
    void test();
private:
    int calculate(int x, int y, int p);
    std::shared_ptr<Node> processSoldiersAttack(Node* parent, int p);
    std::shared_ptr<Node> processBarrackAttack(Node* parent, int p);
    void process(std::shared_ptr<Node> root, int p);
};

#endif // TASK1G_H
