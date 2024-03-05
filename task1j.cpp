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

void readDocument(Document& document) {
    string line;
    Paragraph paragraph;
    while (getline(cin, line)) {
        if (line.find_first_not_of(' ') == string::npos) { // empty line -> new paragraph
            document.paragraphs.push_back(paragraph);
            paragraph.elements.clear();
            continue;
        }
        stringstream stream(line);
        string word;
        stream >> word;


    }
}

void Task1J::doTask()
{
    size_t w, h, c;
    cin >> w >> h >> c;
    Document document(w, h,c);
    readDocument(document);
}
