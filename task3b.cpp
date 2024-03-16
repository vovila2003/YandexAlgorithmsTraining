#include "task3b.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

Task3B::Task3B()
{

}

map<char, int> makeMap(const string& word) {
    map<char, int> result;
    for(char c : word) {
        ++result[c];
    }
    return result;
}

void Task3B::doTask()
{
    string word1;
    string word2;
    cin >> word1 >> word2;
    if (makeMap(word1) == makeMap(word2)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
