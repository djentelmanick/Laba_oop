#ifndef BINARY_H // Защита от многократного включения
#define BINARY_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

// Структура для узла дерева
template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node* left;
    Node* right;

    Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Шаблонный класс бинарного дерева
template <typename Key, typename Value>
class BinaryTree {
private:
    Node<Key, Value>* root;
    size_t size;

    void clear(Node<Key, Value>* node);
    void saveToFile(Node<Key, Value>* node, ofstream& file) const;
    void loadFromFile(ifstream& file);
    void inOrderTraversal(Node<Key, Value>* node, ostream& os) const;

    Node<Key, Value>* copyTree(Node<Key, Value>* otherNode);
    Node<Key, Value>* findMin(Node<Key, Value>* node) const;
    Node<Key, Value>* remove(Node<Key, Value>* node, const Key& k);

public:
    BinaryTree() : root(nullptr), size(0) {};
    BinaryTree(const BinaryTree& other);

    ~BinaryTree() {clear(root);}
    void clear();

    size_t getSize() const {return size;}
    void saveToFile(const string& filePath) const;
    void loadFromFile(const string& filePath);

    bool operator==(const BinaryTree& other) const;
    bool operator[](const Key& k);
    BinaryTree<Key, Value> operator&&(const BinaryTree& other) const;

    void insert(const Key& k, const Value& v);
    void remove(const Key& k) {root = remove(root, k);}
    bool contains(const Key& k) const;
    void printInOrder(ostream& os = cout) const {inOrderTraversal(root, os);}
};

template class BinaryTree<int, string>;

#endif
