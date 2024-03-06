#include "task1j.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

using namespace std;

Task1J::Task1J() {}

struct Rect {
    size_t x;
    size_t y;
    size_t width;
    size_t height;

    Rect(const Rect& other) :
        x(other.x),
        y(other.y),
        width(other.width),
        height(other.height)
    {}

    Rect(size_t x, size_t y, size_t width, size_t height) :
        x(x),
        y(y),
        width(width),
        height(height)
    {}
};

set<Rect> surroundedSet;

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
    bool empty;

    Fragment() :
        x(0),
        y(0),
        width(0),
        height(0),
        empty(true)
    {}

    static Fragment fragmentOnNewLine(const Fragment& prevFragment, size_t h) {
        Fragment fragment;
        fragment.x = 0;
        fragment.y = prevFragment.y + prevFragment.height;
        fragment.width = 0;
        fragment.height = h;
        return fragment;
    }

    static Fragment fragmentOnSameLine(const Fragment& prevFragment) {
        Fragment fragment;
        fragment.x = prevFragment.x + prevFragment.width;
        fragment.y = prevFragment.y;
        fragment.width = 0;
        fragment.height = prevFragment.height;
        return fragment;
    }
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

pair<bool, size_t> tryInsert(const Fragment& fragment, size_t pageWidth, size_t elementWidth, size_t c) {
    size_t width = fragment.x + fragment.width + elementWidth;
    if (!fragment.empty) {
        width += c;
    }
    return make_pair(width <= pageWidth, width);
}

pair<bool, size_t> tryInsertSurrounded(const Fragment& fragment, size_t pageWidth, size_t elementWidth) {
    size_t width = fragment.x + fragment.width + elementWidth;
    return make_pair(width <= pageWidth, width);
}

void updateImage(Image& image, const Fragment& fragment) {
    image.beginX = fragment.x + fragment.width - image.width;
    image.beginY = fragment.y;
}

void updateFragment(Fragment& fragment, size_t width, size_t height, size_t h) {
    fragment.width = width;
    if (height > h) {
        fragment.height = height;
    }
}

void insertFragmentOnNewLine(Document& document, Fragment& fragment, Fragment& prevFragment, size_t h) {
    document.fragments.push_back(fragment);
    prevFragment = fragment;
    fragment = Fragment::fragmentOnNewLine(prevFragment, h);
}

void processWord(Element& element, Fragment& fragment, size_t w, size_t h, size_t c,
                 Document& document, Fragment& prevFragment) {
    int wordWidth = element.word.letterCount * c;
    auto result = tryInsert(fragment, w, wordWidth, c);
    if (result.first) { // can
        fragment.width = result.second;
    } else { // can not
        insertFragmentOnNewLine(document, fragment, prevFragment, h);
        fragment.width = wordWidth;
    }
    fragment.empty = false;
}

void processEmbeddedImage(Image& image, Fragment& fragment, size_t w, size_t h, size_t c,
                          Document& document, Fragment& prevFragment) {
    auto result = tryInsert(fragment, w, image.width, c);
    size_t width;
    if (result.first) { // can
        width = result.second;
    } else { // can not
        insertFragmentOnNewLine(document, fragment, prevFragment, h);
        width = image.width;
    }
    updateFragment(fragment, width, image.height, h);
    updateImage(image, fragment);
    fragment.empty = false;
}

void processSurroundedImage(Image& image, Fragment& fragment, size_t w, size_t h, size_t c,
                          Document& document, Fragment& prevFragment) {

    auto result = tryInsertSurrounded(fragment, w, image.width);
    if (result.first) { // can
        surroundedSet.insert(Rect(fragment.x + fragment.width, fragment.y, image.width, image.height));
        fragment.width = result.second;
        updateImage(image, fragment);
    } else { // can not
        insertFragmentOnNewLine(document, fragment, prevFragment, h);
        // вставить проверку на то, что новый фрагмент сможет вместить с учетом surroundedSet. Там же смотреть по этим rectб при необходимости удалять

    }
}

void processFloatingImage(Image& image, Fragment& fragment, size_t w, size_t h, size_t c,
                            Document& document, Fragment& prevFragment) {

}

void processElement(Element& element, Fragment& fragment, size_t w, size_t h, size_t c,
                    Document& document, Fragment& prevFragment) {
    if (element.type == ElementType::Word) {
        processWord(element, fragment, w, h, c, document, prevFragment);
    } else if (element.type == ElementType::Image) {
        Image& image = element.image;
        if (image.layout == ImageType::Embedded) {
            processEmbeddedImage(image, fragment, w, h, c, document, prevFragment);
        } else if (image.layout == ImageType::Surrounded) {
            processSurroundedImage(image, fragment, w, h, c, document, prevFragment);
        } else if (image.layout == ImageType::Floating) {
            processFloatingImage(image, fragment, w, h, c, document, prevFragment);
        }
    }
}

void processFragments(Document& document) {
    size_t w = document.pageWidth;
    size_t h = document.lineHeight;
    size_t c = document.letterWidth;
    Fragment prevFragment;
    Fragment fragment = Fragment::fragmentOnNewLine(prevFragment, h);
    for (size_t i = 0; i < document.paragraphs.size(); ++i) {
        fragment = Fragment::fragmentOnNewLine(prevFragment, h);
        Paragraph& paragraph = document.paragraphs[i];
        for (size_t j = 0; j < paragraph.elements.size(); ++j) {
            processElement(paragraph.elements[j], fragment, w, h, c,
                           document, prevFragment);
        }
        document.fragments.push_back(fragment);
        prevFragment = fragment;
        fragment = Fragment::fragmentOnNewLine(prevFragment, h);
        prevFragment = fragment;
        document.fragments.push_back(fragment);
    }
}

void printResult(const Document& document, ostream& output) {
    for (size_t i = 0; i < document.paragraphs.size(); ++i) {
        for (size_t j = 0; j < document.paragraphs.at(i).elements.size(); ++j) {
            const Element& element = document.paragraphs.at(i).elements.at(j);
            if (element.type != ElementType::Image) continue;

            output << element.image.beginX << " " << element.image.beginY << endl;
        }
    }
}

void Task1J::doTask()
{
    size_t w, h, c;
    cin >> w >> h >> c;
    Document document(w, h, c);
    readDocument(document, cin);
    processFragments(document);
    printResult(document, cout);
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

    // string input(
    //     "one two three\n"
    //     "\n"
    //     "four five six\n"
    //     "seven eight nine\n"
    //     "\n"
    //     "ten\n"
    //     );
    stringstream stream(input);
    Document document(120, 10, 8);
    readDocument(document, stream);
    processFragments(document);
    printResult(document, cout);
}
