#include "binary_node.h"


int main() {
    BinaryTree<int, string> tree;

    // Тест 1: Конструктор по умолчанию
    assert(tree.getSize() == 0);
    tree.remove(1);
    assert(tree.getSize() == 0);

    // Тест 2: Добавление элементов
    tree.insert(20231212, "Alice");
    tree.insert(20231213, "Bob");
    assert(tree.getSize() == 2);

    // Тест 3: Удаление элементов
    tree.remove(20231212);
    assert(tree.getSize() == 1);

    // Тест 4: Проверка сохранения и загрузки
    tree.saveToFile("tree.txt");
    BinaryTree<int, string> tree2;
    tree2.loadFromFile("tree.txt");
    assert(tree == tree2);

    // Тест 5: Оператор &&
    BinaryTree<int, string> tree3;
    tree3.insert(20231213, "Bob");
    tree3.insert(20231214, "Charlie");
    BinaryTree<int, string> intersected = tree && tree3;
    assert(intersected.getSize() == 1);
    assert(intersected.contains(20231213));

    // Тест 6: Проверка [] оператора
    assert(tree[20231213]);
    assert(!tree[0]);

    // Тест 7: Проверка вывода по дням
    tree3.insert(20231120, "Jack");
    tree3.insert(20220115, "Peter");
    tree3.printInOrder();

    cout << "All tests passed successfully!" << endl;
    
    return 0;
}
