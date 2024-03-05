#ifndef TASK1D_H
#define TASK1D_H

#include <vector>

class Task1D
{
public:
    Task1D();
    void doTask();

private:
    const int SIZE = 8;
    std::vector<std::vector<char>> readData();
    void printData(const std::vector<std::vector<char>>& data);
    std::vector<std::pair<int, int>> getFigures(const std::vector<std::vector<char>>& data,
                                                char name);
    bool inBounds(int x, int y);
    bool isEmpty(const std::vector<std::vector<char>>& data, int x, int y);
    void processFigure(std::vector<std::vector<char>>& data, int x, int y,
                       int (*opX)(int), int (*opY)(int));
    void processBishops(std::vector<std::vector<char>>& data,
                        const std::vector<std::pair<int, int>>& bishops);
    void processRooks(std::vector<std::vector<char>>& data,
                      const std::vector<std::pair<int, int>>& rooks);
    int processResult(const std::vector<std::vector<char>>& data);

};

#endif // TASK1D_H
