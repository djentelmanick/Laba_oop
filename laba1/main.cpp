#include <iostream>
#include <vector>
#include <clocale>
#include "builder.h"
#include <string>
#include <assert.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Часть1
    // Проверка конструктора по умолчанию
    Element elem;
    vector<vector<int>> surface(5, vector<int>(7, 0));

    assert(elem.getConnectors().empty());
    assert(elem.getOtherSockets().empty());
    assert(elem.getSurface() == surface);


    // Проверка конструктора инициализации
    vector<pair<int, int>> connectors1 = {{1, 2}, {1, 4}};
    vector<pair<int, int>> other_sockets1 = {{2, 2}, {2, 4}};
    Element elem1(connectors1, other_sockets1);
    vector<vector<int>> surface1(5, vector<int>(7, 0));
    for (const pair<int, int>& connector: connectors1)
        surface1[connector.first][connector.second] = 2;
    for (const pair<int, int>& socket: other_sockets1)
        surface1[socket.first][socket.second] = 1;

    cout << "elem1";
    elem1.printSurface();

    assert(elem1.getSurface() == surface1);
    assert(elem1.getConnectors() == connectors1);
    assert(elem1.getOtherSockets() == other_sockets1);


    // Проверка конструктора копирования
    Element elem1_copy(elem1);

    cout << "elem1_copy";
    elem1_copy.printSurface();

    assert(elem1_copy.getSurface() == surface1);
    assert(elem1_copy.getConnectors() == connectors1);
    assert(elem1_copy.getOtherSockets() == other_sockets1);


    // Проверка могут ли гнезда передаваемого объекта подключиться к соединителям текущего объекта
    vector<pair<int, int>> connectors2 = {{1, 2}, {1, 4}, {2, 2}, {2, 4}};
    vector<pair<int, int>> other_sockets2 = {};
    Element elem2(connectors2, other_sockets2);

    vector<pair<int, int>> connectors3 = {};
    vector<pair<int, int>> other_sockets3 = {{2, 6}, {2, 0}, {1, 0}, {1, 6}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}};
    Element elem3(connectors3, other_sockets3);

    cout << "elem2";
    elem2.printSurface();
    cout << "elem3";
    elem3.printSurface();

    assert(elem2.canConnect(elem1));
    assert(!elem1.canConnect(elem3));
    assert(elem2.canConnect(elem3));
    assert(!elem3.canConnect(elem2));


    // Часть2
    // Проверка конструктора по умолчанию
    SmartElement s_elem;

    assert(s_elem.getSurface() == surface);
    assert(s_elem.getConnectors().empty());
    assert(s_elem.getOtherSockets().empty());
    assert(s_elem.getFunctional() == "Unknown");


    // Проверка конструктора инициализации
    vector<pair<int, int>> connectors4 = {{2, 6}, {3, 6}};
    vector<pair<int, int>> other_sockets4 = {{1, 6}};
    vector<vector<int>> surface4(5, vector<int>(7, 0));
    for (const pair<int, int>& connector: connectors4)
        surface4[connector.first][connector.second] = 2;
    for (const pair<int, int>& socket: other_sockets4)
        surface4[socket.first][socket.second] = 1;

    SmartElement s_elem4("squeaker", connectors4, other_sockets4);

    cout << "\ns_elem4";
    s_elem4.printSurface();

    assert(s_elem4.getSurface() == surface4);
    assert(s_elem4.getConnectors() == connectors4);
    assert(s_elem4.getOtherSockets() == other_sockets4);
    assert(s_elem4.getFunctional() == "squeaker");


    // Проверка конструктора копирования
    SmartElement s_elem4_copy(s_elem4);

    cout << "s_elem4_copy";
    s_elem4_copy.printSurface();

    assert(s_elem4_copy.getSurface() == surface4);
    assert(s_elem4_copy.getConnectors() == connectors4);
    assert(s_elem4_copy.getOtherSockets() == other_sockets4);
    assert(s_elem4_copy.getFunctional() == "squeaker");


    SmartElement s_elem1_copy(elem1, "feet");

    cout << "s_elem1_copy";
    s_elem1_copy.printSurface();

    assert(s_elem1_copy.getSurface() == surface1);
    assert(s_elem1_copy.getConnectors() == connectors1);
    assert(s_elem1_copy.getOtherSockets() == other_sockets1);
    assert(s_elem1_copy.getFunctional() == "feet");


    SmartElement s_elem2_copy(elem2);
    vector<vector<int>> surface2(5, vector<int>(7, 0));
    for (const pair<int, int>& connector: connectors2)
        surface2[connector.first][connector.second] = 2;
    for (const pair<int, int>& socket: other_sockets2)
        surface2[socket.first][socket.second] = 1;

    cout << "s_elem2_copy";
    s_elem2_copy.printSurface();

    assert(s_elem2_copy.getSurface() == surface2);
    assert(s_elem2_copy.getConnectors() == connectors2);
    assert(s_elem2_copy.getOtherSockets() == other_sockets2);
    assert(s_elem2_copy.getFunctional() == "Unknown");


    // Проверка соединения
    assert(s_elem2_copy.canConnect(s_elem1_copy));
    assert(!s_elem2_copy.canConnect(s_elem4));
    assert(s_elem2_copy.canConnect(elem3));
    assert(!s_elem1_copy.canConnect(elem3));
    assert(!elem3.canConnect(s_elem4));
    assert(elem2.canConnect(s_elem1_copy));


    // Проверка идентификации элемента
    cout << '\n';
    assert(!elem.isSmart());
    assert(s_elem4.isSmart());
    assert(s_elem1_copy.isSmart());
    assert(s_elem2_copy.isSmart());

    cout << "\nВсе тесты успешно пройдены!\n";
    return 0;
}
