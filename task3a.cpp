#include "task3a.h"

#include <iostream>
#include <set>

using namespace std;

Task3A::Task3A()
{

}

void Task3A::doTask()
{
    int n = 0;
    int k = 0;
    string sing;
    cin >> n;
    bool first = true;
    set<string> result;
    for (int i = 0; i < n; ++i) {
        cin >> k;
        set<string> tmp;
        for (int j = 0; j < k; ++j) {
            cin >> sing;
            if (first) {
                result.insert(sing);
            } else {
                if (result.count(sing) != 0) {
                    tmp.insert(sing);
                }
            }
        }
        result.swap(tmp);
        if (first) {
            first =false;
        }
    }

    cout << result.size() << endl;
    for (auto& s : result) {
        cout << s << " ";
    }
}
