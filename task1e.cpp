#include "task1e.h"

using namespace std;

Task1E::Task1E()
{

}

void Task1E::doTask()
{
    int n, k, d;
    cin >> n >> k >> d;
    int64_t result = n;
    result = findNext(result, k);
    cout << result;
    if (result != -1) {
        cout << string(d - 1, '0');
    }
}

int64_t Task1E::findNext(int64_t current, int k)
{
    current *=10;
    for (int i = 0; i < 10; ++i) {
        if ((current + i) % k == 0) {
            return current + i;
        }
    }
    return -1;
}

//struct Node {
//    deque<unique_ptr<Node>> children;
//    Node* parent;
//    int64_t value;
//    int depth;
//};

//Node* findChildrenAndGetFirst(Node* parent, int k) {
//    auto value = parent->value * 10;
//    for (int i = 0; i < 10; ++i) {
//        if ((value + i) % k == 0) {
//            auto child = make_unique<Node>();
//            child->parent = parent;
//            child->value = value + i;
//            child->depth = parent->depth + 1;
//            parent->children.push_back(std::move(child));
//        }
//    }
//    if (parent->children.empty()) {
//        return nullptr;
//    }
//    return parent->children.front().get();
//}

//Node* next(Node* node) {
//    if (node->parent == nullptr) { // root
//        return nullptr; // нет решения
//    }
//    Node* parent = node->parent;
//    parent->children.front().reset();
//    parent->children.pop_front();
//    if (parent->children.empty()) {
//        return next(parent);
//    }
//    return parent->children.front().get();
//}

//void task1E() {
//    int n, k, d;
//    cin >> n >> k >> d;
//    auto root = make_unique<Node>();
//    root->value = n;
//    root->parent = nullptr;
//    root->depth = 0;
//    Node* parentNode = root.get();
//    while (parentNode && (parentNode->depth < d)) {
//        auto nextNode = findChildrenAndGetFirst(parentNode, k);
//        if (nextNode == nullptr) {
//            nextNode = next(parentNode);
//        }
//        parentNode = nextNode;
//    }
//    int64_t result = parentNode? parentNode->value : -1;
//    cout << result;
//}
