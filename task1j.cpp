#include "task1j.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

Task1J::Task1J() {}

enum class ImageType {
    Embedded = 0,
    Surrounded = 1,
    Floating = 2
};

map<string, ImageType> stringToImageType {
    {"embedded", ImageType::Embedded},
    {"surrounded", ImageType::Surrounded},
    {"floating", ImageType::Floating},
};

struct Image {
    size_t width;
    size_t height;
    ImageType layout;
    int dx;
    int dy;
    int beginX;
    int beginY;
};

struct Word {
    int letterCount;
};

enum class ElementType {
    Word = 0,
    Image = 1,
};

struct Element {
    ElementType type;
    Word word;
    Image image;
};

struct Paragraph {
    vector<Element> elements;
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

void parseImageParameter(Image& image, const string& text) {
    stringstream stream(text);
    string name, valueString;
    getline(stream, name, '=');
    getline(stream, valueString);
    if (name == "width") {
        int value = stoi(valueString);
        image.width = value;
    } else if (name == "height") {
        int value = stoi(valueString);
        image.height = value;
    } else if (name == "layout") {
        image.layout = stringToImageType[valueString];
    } else if (name == "dx") {
        int value = stoi(valueString);
        image.dx = value;
    } else if (name == "dy") {
        int value = stoi(valueString);
        image.dy = value;
    }
}

void readDocument(Document& document, istream& inputStream) {
    string line;
    Paragraph paragraph;
    bool isImage = false;
    while (getline(inputStream, line)) {
        if (line.find_first_not_of(' ') == string::npos || line.empty()) { // empty line -> new paragraph
            document.paragraphs.push_back(paragraph);
            paragraph = Paragraph();
            continue;
        }
        string text;
        stringstream stream(line);
        Image image;
        Word word;
        while(getline(stream, text, ' ')) {
            if (!isImage) {
                if (text == "(image") {
                    isImage = true;
                    image = Image();
                } else {
                    word.letterCount = text.size();
                    Element element;
                    element.type = ElementType::Word;
                    element.word = word;
                    paragraph.elements.push_back(element);
                    word = Word();
                }
            } else {
                if (isImage && text.back() == ')') {
                    isImage = false;
                    text.pop_back();
                }
                parseImageParameter(image, text);

                if (!isImage) {
                    Element element;
                    element.type = ElementType::Image;
                    element.image = image;
                    paragraph.elements.push_back(element);
                    image = Image();
                }
            }
        }
    }
    document.paragraphs.push_back(paragraph);
}

void Task1J::doTask()
{
    size_t w, h, c;
    cin >> w >> h >> c;
    Document document(w, h, c);
    // readDocument(document, cin);
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

    cout << "DONE";
}
