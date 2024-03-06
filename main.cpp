//#include "task1a.h"
//#include "task1b.h"
//#include "task1c.h"
//#include "task1d.h"
//#include "task1e.h"
//#include "task1f.h"
// #include "task1g.h"
//#include "task1h.h"
//#include "task1i.h"
#include "task1j.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


void test() {
    string input(
        "start (image layout=embedded width=12 height=5)\n"
                "(image layout=surrounded width=25 height=58)\n"
                "and word is \n"
                "(image layout=floating dx=18 dy=-15 width=25 height=20)\n"
                "here new \n"
                "(image layout=embedded width=20 height=22)\n"
                "another\n"
                "(image layout=embedded width=40 height=19)\n"
                "longword\n"
                "\n"
                "new paragraph\n"
                "(image layout=surrounded width=5 height=30)\n"
                "(image layout=floating width=20 height=35 dx=50 dy=-16)"
        );
    stringstream stream(input);
    string line;
    while (getline(stream, line)) {
        if (line.empty()) {
            cout << "EMPTY LINE";
        } else {
            string word;
            stringstream lineStream(line);
            while(getline(lineStream, word, ' ')) {
                cout << word << " <-> ";
            }
        }
        cout << endl;
    }

}

int main()
{
    // test();

//    Task1A task1a;
//    task1a.doTask();

//    Task1B task1b;
//    task1b.doTask();

//    Task1C task1c;
//    task1c.doTask();

//    Task1D task1d;
//    task1d.doTask();

//    Task1E task1e;
//    task1e.doTask();

//    Task1F task1f;
//    task1f.test();
//    task1f.doTask();

    // Task1G task1g;
//    task1g.doTask();
    // task1g.test();

//    Task1H task1h;
//    task1h.doTask();
//    task1h.test();

//    Task1I task1i;
//    task1i.test();
//    task1i.doTask();

    Task1J task1j;
    // task1j.test();
    task1j.doTask();

    return 0;
}
