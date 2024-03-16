#include "task3f.h"

#include <iostream>
#include <map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Task3F::Task3F()
{

}

void Task3F::doTask()
{
    string line;
    getline(cin, line);
    stringstream ss(line);
    string word;
    map<size_t, unordered_set<string>> dict;
    vector<string> result;
    while (ss >> word) {
        dict[word.size()].emplace(std::move(word));
    }
    getline(cin, line);
    stringstream ss2(line);
    while(ss2 >> word) {
        bool find = false;
        for (size_t s = 1; s < word.size(); ++s) {
            string str = word.substr(0, s);
            if (dict[s].count(str) != 0) {
                result.push_back(std::move(str));
                find = true;
                break;
            }
        }
        if (find) {
            continue;
        }
        result.push_back(std::move(word));
    }

    for (auto& s : result) {
        cout << s << " ";
    }
}
