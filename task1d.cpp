#include "task1d.h"

using namespace std;

Task1D::Task1D()
{

}

void Task1D::doTask()
{
    auto data = readData();
    auto bishops = getFigures(data, 'B');
    auto rooks = getFigures(data, 'R');
    processBishops(data, bishops);
    processRooks(data, rooks);
//    printData(data);
    int result = processResult(data);
    cout << result;
}

std::vector<std::vector<char> > Task1D::readData()
{
    auto data = vector<vector<char>>(SIZE, vector<char>(SIZE));
    for (int i = 0 ; i < SIZE; ++i) {
        string s;
        getline(cin, s);
        stringstream stream(s);
        for (int j = 0; j < SIZE; ++j) {
            stream >> data[i][j];
        }
    }
    return data;
}

void Task1D::printData(const std::vector<std::vector<char> > &data)
{
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            cout << data[i][j];
        }
        cout << "\n";
    }
}

std::vector<std::pair<int, int> > Task1D::getFigures(const std::vector<std::vector<char> > &data, char name)
{
    vector<pair<int, int>> result;
    for (int i = 0; i < (int)data.size(); ++i) {
        for (int j = 0; j < (int)data[i].size(); ++j) {
            if (data[i][j] != name) continue;
            result.push_back(make_pair(i, j));
        }
    }
    return result;
}

bool Task1D::inBounds(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool Task1D::isEmpty(const std::vector<std::vector<char> > &data, int x, int y)
{
    return data.at(x).at(y) == '*' || data.at(x).at(y) == ' ';
}

void Task1D::processFigure(std::vector<std::vector<char> > &data, int x, int y,
                           int (*opX)(int), int (*opY)(int))
{
    x = opX(x);
    y = opY(y);

    while(inBounds(x, y) && isEmpty(data, x, y)) {
        data[x][y] = ' ';
        x = opX(x);
        y = opY(y);
    }
}

void Task1D::processBishops(std::vector<std::vector<char> > &data, const std::vector<std::pair<int, int> > &bishops)
{
    for (size_t i = 0; i < bishops.size(); ++i) {
        processFigure(data, bishops.at(i).first, bishops.at(i).second,
                         [](int x){return x + 1;},
                         [](int y){return y + 1;}
        );
        processFigure(data, bishops.at(i).first, bishops.at(i).second,
                         [](int x){return x - 1;},
                         [](int y){return y + 1;}
        );
        processFigure(data, bishops.at(i).first, bishops.at(i).second,
                         [](int x){return x + 1;},
                         [](int y){return y - 1;}
        );
        processFigure(data, bishops.at(i).first, bishops.at(i).second,
                         [](int x){return x - 1;},
                         [](int y){return y - 1;}
        );
    }
}

void Task1D::processRooks(std::vector<std::vector<char> > &data, const std::vector<std::pair<int, int> > &rooks)
{
    for (size_t i = 0; i < rooks.size(); ++i) {
        processFigure(data, rooks.at(i).first, rooks.at(i).second,
                         [](int x){return x;},
                         [](int y){return y + 1;}
        );
        processFigure(data, rooks.at(i).first, rooks.at(i).second,
                         [](int x){return x;},
                         [](int y){return y - 1;}
        );
        processFigure(data, rooks.at(i).first, rooks.at(i).second,
                         [](int x){return x + 1;},
                         [](int y){return y;}
        );
        processFigure(data, rooks.at(i).first, rooks.at(i).second,
                         [](int x){return x - 1;},
                         [](int y){return y;}
        );
    }
}

int Task1D::processResult(const std::vector<std::vector<char> > &data)
{
    int result = 0;
    for (int i = 0; i < (int)data.size(); ++i) {
        for (int j = 0; j < (int)data[i].size(); ++j) {
            if (data[i][j] == '*') {
                ++result;
            }
        }
    }
    return result;
}
