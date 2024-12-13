#include "binary_node.h"

template<typename Key, typename Value>
void BinaryTree<Key, Value>::clear(Node<Key, Value>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::saveToFile(Node<Key, Value>* node, ofstream& file) const {
        if (node) {
            file << node->key << " " << node->value << endl;
            saveToFile(node->left, file);
            saveToFile(node->right, file);
        }
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::loadFromFile(ifstream& file) {
        Key k;
        Value v;
        while (file >> k >> v) {
            insert(k, v);
        }
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::inOrderTraversal(Node<Key, Value>* node, ostream& os) const {
        if (node) {
            inOrderTraversal(node->left, os);
            os << node->value << endl;
            inOrderTraversal(node->right, os);
        }
    }

template<typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::copyTree(Node<Key, Value>* otherNode) {
        if (!otherNode) return nullptr;
        Node<Key, Value>* newNode = new Node<Key, Value>(otherNode->key, otherNode->value);
        newNode->left = copyTree(otherNode->left);
        newNode->right = copyTree(otherNode->right);
        return newNode;
    }

template<typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::findMin(Node<Key, Value>* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

template<typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::remove(Node<Key, Value>* node, const Key& k) {
        if (!node) return nullptr;
        if (k < node->key) {
            node->left = remove(node->left, k);
        } else if (k > node->key) {
            node->right = remove(node->right, k);
        } else {
            size --;
            if (!node->left) {
                Node<Key, Value>* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                Node<Key, Value>* leftChild = node->left;
                delete node;
                return leftChild;
            }
            Node<Key, Value>* minNode = findMin(node->right);
            node->key = minNode->key;
            node->value = minNode->value;
            node->right = remove(node->right, minNode->key);
        }
        return node;
    }

template<typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree& other) : root(nullptr), size(0) {
        root = copyTree(other.root);
        size = other.size;
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::saveToFile(const string& filePath) const {
        ofstream file(filePath);
        if (file.is_open()) {
            saveToFile(root, file);
            file.close();
        }
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::loadFromFile(const string& filePath) {
        ifstream file(filePath);
        if (file.is_open()) {
            clear();
            loadFromFile(file);
            file.close();
        }
    }

template<typename Key, typename Value>
bool BinaryTree<Key, Value>::operator==(const BinaryTree& other) const {
        ostringstream oss1, oss2;
        inOrderTraversal(root, oss1);
        inOrderTraversal(other.root, oss2);
        return oss1.str() == oss2.str();
    }

template<typename Key, typename Value>
bool BinaryTree<Key, Value>::operator[](const Key& k) {
        Node<Key, Value>* current = root;
        while (current) {
            if (k == current->key) return true;
            if (k < current->key) current = current->left;
            else current = current->right;
        }
        // throw runtime_error("Key not found");
        return false;
    }

template<typename Key, typename Value>
BinaryTree<Key, Value> BinaryTree<Key, Value>::operator&&(const BinaryTree& other) const {
        BinaryTree<Key, Value> result;
        function<void(Node<Key, Value>*)> intersect = [&](Node<Key, Value>* node) {
            if (!node) return;
            if (other.contains(node->key)) {
                result.insert(node->key, node->value);
            }
            intersect(node->left);
            intersect(node->right);
        };
        intersect(root);
        return result;
    }

template<typename Key, typename Value>
void BinaryTree<Key, Value>::insert(const Key& k, const Value& v) {
        Node<Key, Value>** current = &root;
        while (*current) {
            if (k < (*current)->key) {
                current = &((*current)->left);
            } else if (k > (*current)->key) {
                current = &((*current)->right);
            } else {
                (*current)->value = v;
                return;
            }
        }
        *current = new Node<Key, Value>(k, v);
        ++size;
    }

template<typename Key, typename Value>
bool BinaryTree<Key, Value>::contains(const Key& k) const {
        Node<Key, Value>* current = root;
        while (current) {
            if (k == current->key) return true;
            if (k < current->key) current = current->left;
            else current = current->right;
        }
        return false;
    }