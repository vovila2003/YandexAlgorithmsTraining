#include "task1j.h"

#include <iostream>
#include <vector>
#include <any>
#include <sstream>

using namespace std;

Task1J::Task1J() {}

enum class ImageType {
    Embedded = 0,
    Surrounded = 1,
    Floating = 2
};

struct Image {
    size_t width;
    size_t height;
    ImageType type;
    int dx;
    int dy;
    int beginX;
    int beginY;
};

struct Word {
    int letterCount;
};

struct Paragraph {
    vector<any> elements;
};

struct Fragment {
    size_t x;
    size_t y;
    size_t width;
    size_t height;
};

struct Document {
    vector<Paragraph> paragraphs;
    vector<Fragment> fragments;
    const size_t pageWidth;
    const size_t lineHeight;
    const size_t letterWidth;

    Document(size_t w, size_t h, size_t c) : pageWidth(w), lineHeight(h), letterWidth(c) {}
};

void readDocument(Document& document, istream& inputStream) {
    string line;
    Paragraph paragraph;
    bool isImage = false;
    while (getline(inputStream, line)) {
        if (line.find_first_not_of(' ') == string::npos || line.empty()) { // empty line -> new paragraph
            document.paragraphs.push_back(paragraph);
            paragraph.elements.clear();
            cout << "EMPTY LINE\n";
            continue;
        }
        string text;
        stringstream stream(line);
        // Image image;
        // Word word;
        while(getline(stream, text, ' ')) {
            if (!isImage) { // WORD
                if (text == "(image") { //
                    isImage = true;
                    cout << "BEGIN IMAGE" << endl;
                } else {
                    cout << "READ WORD: ";
                    cout << text << endl;
                }
            } else { //IMAGE
                if (isImage && text.back() == ')') {
                    isImage = false;
                    text.pop_back();
                }
                cout << "READ IMAGE PARAMETER: ";
                cout << text << endl;
                if (!isImage) {
                    cout << "END IMAGE" << endl;
                }
            }
        }
    }
}

void Task1J::doTask()
{
    size_t w, h, c;
    cin >> w >> h >> c;
    Document document(w, h, c);
    // readDocument(document);
}

void Task1J::test()
{
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
    Document document(100, 10, 10);
    readDocument(document, stream);
}
