#include "task2h.h"

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

Task2H::Task2H() {}

tuple<int, size_t, size_t> findMax(const vector<vector<int>>& forces,
                                   int rowExclude, int columnExclude) {
    bool first = true;
    int maxValue;
    int maxRow, maxColumn;
    for (size_t i = 0; i < forces.size(); ++i) {
        if ((int)i == rowExclude) continue;
        for (size_t j = 0; j <forces.at(i).size(); ++j) {
            if ((int)j == columnExclude) continue;
            if (first){
                maxValue = forces.at(i).at(j);
                maxRow = i;
                maxColumn = j;
                first = false;
            } else if (maxValue < forces.at(i).at(j)) {
                maxValue = forces.at(i).at(j);
                maxRow = i;
                maxColumn = j;
            }
        }
    }
    return make_tuple(maxValue, maxRow, maxColumn);
}

void Task2H::doTask()
{
    int n, m;
    cin >> n >> m;
    int maxForceGlobal = 0;
    int iMaxForce = 0;
    int jMaxForce = 0;
    bool first = true;
    int force;
    vector<vector<int>> forces = vector<vector<int>>(n, vector<int>(m, 0));
    for (int i = 0 ; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> force;
            if (first) {
                maxForceGlobal = force;
                iMaxForce = i;
                jMaxForce = j;
                first = false;
            } else if (force > maxForceGlobal) {
                    maxForceGlobal = force;
                    iMaxForce = i;
                    jMaxForce = j;
                }
            forces[i][j] = force;
        }
    }

    //strategy Row->Column
    int maxValueWithoutRow;
    int i, j;
    int row1 = iMaxForce;
    tie(maxValueWithoutRow, i, j) = findMax(forces, row1, -1);
    int column1 = j;
    int maxValueWithoutRowColumn;
    tie(maxValueWithoutRowColumn, i, j) = findMax(forces, row1, column1);

    //strategy Row->Column
    int maxValueWithoutColumn;
    int column2 = jMaxForce;
    tie(maxValueWithoutColumn, i, j) = findMax(forces, -1, column2);
    int row2 = i;
    int maxValueWithoutColumnRow;
    tie(maxValueWithoutColumnRow, i, j) = findMax(forces, row2, column2);

    int resultRow, resultColumn;

    if (maxValueWithoutRowColumn < maxValueWithoutColumnRow) {
        resultRow = row1;
        resultColumn = column1;
    } else {
        resultRow = row2;
        resultColumn = column2;
    }

    cout << (resultRow + 1) << " " << (resultColumn + 1);
}
