#include "builder.h"
#include <vector>
#include <iostream>
using namespace std;

// Инициализация статической переменной
vector<vector<vector<int>>> Element::assembly;


// Конструктор по умолчанию
Element::Element() : surface(ROW, vector<int>(COL, 0)), connectors{}, other_sockets{} {}


// Конструктор инициализации
Element::Element(const vector<pair<int, int>>& c, const vector<pair<int, int>>& s) 
    : surface(ROW, vector<int>(COL, 0)), connectors(c), other_sockets(s) {
    // Инициализация гнезд и соединителей на поверхности 
    for (const pair<int, int>& connector : connectors) {
        surface[connector.first][connector.second] = 2;  // обозначаем наличие соединителя и гнезда как 2
    }
    for (const pair<int, int>& other_socket : other_sockets) {
        surface[other_socket.first][other_socket.second] = 1;  // обозначаем деталь с генздом без верхнего соединителя
    }
    // assembly.push_back(surface);
}


// Конструктор копирования
Element::Element(const Element& el) {
    surface = el.surface;
    connectors = el.connectors;
    other_sockets = el.other_sockets;
}


// Метод для проверки, могут ли гнезда передаваемого объекта подключиться к соединителям текущего объекта
bool Element::canConnect(const Element& checked_el) const {
    if (connectors.size() == 0) {
        cout << "Невозможно занять ни один соединитель текущего элемента, так как у него их нет!\n";
        return false;
    }

    bool all_connectors = true;
    bool one_connector = false;
    for (const pair<int, int>& connector : connectors) {
        if (checked_el.surface[connector.first][connector.second] == 0)
            all_connectors = false;
        else
            one_connector = true;
    }

    if (all_connectors) {
        cout << "Возможно занять все соединители текущего элемента передаваемым элементом\n";
        return true;
    }
    if (one_connector) {
        cout << "Возможно занять часть соединителей текущего элемента передаваемым элементом\n";
        return true;
    }
    cout << "Невозможно занять ни один соединитель текущего элемента передаваемым элементом, проверьте индексы!\n";
    return false;
}


// Метод для отображения поверхности
void Element::printSurface() const {
    cout << '\n';
    for (const vector<int>& row : surface) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << '\n';
}


bool Element::isSmart() const {
    cout << "Эта деталь обычная\n";
    return false;
} 


void Element::printMatrices() {
    for (size_t i = 0; i < assembly.size(); ++i) {
        cout << "Matrix " << i + 1 << ":\n";
        for (const vector<int>& row : assembly[i]) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}


SmartElement::SmartElement() : Element(), functional("Unknown") {}


SmartElement::SmartElement(const string& func, const vector<pair<int, int>>& c, const vector<pair<int, int>>& s)
    : Element(c, s), functional(func) {}


SmartElement::SmartElement(const SmartElement& se) : Element(se), functional(se.functional) {}
SmartElement::SmartElement(const Element& e, const string& func) : Element(e), functional(func) {}
SmartElement::SmartElement(const Element& e) : SmartElement(e, "Unknown") {}


bool SmartElement::isSmart() const {
    cout << "Эта детеаль умная. Её функциональность: " << functional << "\n";
    return true;
}
