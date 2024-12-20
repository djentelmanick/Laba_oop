#include "builder.h"
#include <vector>
#include <string>
#include <stack>
#include <iostream>
using namespace std;


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
bool Element::canConnect(const Element& checked_el, const string& message) const {
    if (connectors.size() == 0) {
        cout << "Невозможно занять ни один соединитель текущего элемента" << message << ", так как у него их нет!\n";
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
        cout << "Возможно занять все соединители текущего элемента" << message << " передаваемым элементом\n";
        return true;
    }
    if (one_connector) {
        cout << "Возможно занять часть соединителей текущего элемента" << message << " передаваемым элементом\n";
        return true;
    }
    cout << "Невозможно занять ни один соединитель текущего элемента" << message << " передаваемым элементом, проверьте индексы!\n";
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


bool Element::isSmart(int print_sent) const {
    if (print_sent)
        cout << "Эта деталь обычная\n";
    return false;
} 


SmartElement::SmartElement() : Element(), functional("Unknown") {}


SmartElement::SmartElement(const string& func, const vector<pair<int, int>>& c, const vector<pair<int, int>>& s)
    : Element(c, s), functional(func) {}


SmartElement::SmartElement(const SmartElement& se) : Element(se), functional(se.functional) {}
SmartElement::SmartElement(const Element& e, const string& func) : Element(e), functional(func) {}
SmartElement::SmartElement(const Element& e) : SmartElement(e, "Unknown") {}


bool SmartElement::isSmart(int print_sent) const {
    if (print_sent)
        cout << "Эта детеаль умная. Её функциональность: " << functional << "\n";
    return true;
}


int Assembly::number_assembly = 0;


Assembly::Assembly() {
    if (!number_assembly)
        name = "Assembly";
    else
        name = "Assembly" + to_string(number_assembly);
    ++number_assembly;
};


Assembly::Assembly(Assembly& assembly) {
    name = assembly.name;

    stack<unique_ptr<Element>> temp_stack_ptr;
    stack<Element> temp_stack;
    while (!assembly.elements.empty()) {
        temp_stack.push(*assembly.elements.top());
        temp_stack_ptr.push(move(assembly.elements.top()));
        assembly.elements.pop();
    }

    while (!temp_stack.empty()) {
        if (temp_stack.top().isSmart(0))
            elements.push(make_unique<SmartElement>(temp_stack.top()));
        else
            elements.push(make_unique<Element>(temp_stack.top()));
        temp_stack.pop();
    }

    while (!temp_stack_ptr.empty()) {
        assembly.elements.push(move(temp_stack_ptr.top()));
        temp_stack_ptr.pop();
    }
}


void Assembly::addElement(unique_ptr<Element> e) {
    string message = " сборки " + name;
    if (elements.empty()) {
        elements.push(move(e));
        cout << "Успешно добавлен первый элемент в сборку " << name;
    }
    else if (elements.top()->canConnect(*e, message)) {
        elements.push(move(e));
        cout << "Поэтому элемент успешно добавлен в сброку " << name;
    }
    else {
        cout << "Поэтому нельзя добавить данный элемент в сборку " << name;
    }
    cout << "\n\n";
}


void Assembly::printTopStack() const {
    if (elements.empty()) {
        cout << "Stack is empty!" << "\n";
        return;
    }
    
    cout << "Stack top:" << "\n";
    for (const vector<int>& row : elements.top()->getSurface()) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


void Assembly::printAssemblyForNRow(const int row){
    stack<unique_ptr<Element>> temp_stack;

    cout << "Assembly for " << row << " row:" << "\n\n";
    while (!elements.empty()) {
        for (int val : elements.top()->getSurface()[row]) {
            if (!val)
                cout << "  ";
            else
                cout << val  << " ";
        }
        cout << "\n";
        temp_stack.push(move(elements.top()));
        elements.pop();
    }
    cout << "\n";

    while (!temp_stack.empty()) {
        elements.push(move(temp_stack.top()));
        temp_stack.pop();
    }
}


void Assembly::printElementsSurface() {
    cout << "\nВсе элементы сборки " << name << ":\n\n";
    stack<unique_ptr<Element>> temp_stack;

    while(!elements.empty()) {
        elements.top()->isSmart();
        elements.top()->printSurface();
        temp_stack.push(move(elements.top()));
        elements.pop();
    }

    while (!temp_stack.empty()) {
        elements.push(move(temp_stack.top()));
        temp_stack.pop();
    }
}


// bool Assembly::stackComparison(const stack<unique_ptr<Element>>& s) const {
    // if (elements.size() != s.size())
    //     return false;

    // stack<unique_ptr<Element>> temp_elements = elements;
    // while (!temp_elements.empty()) {
    //     if (temp_elements.top()->getSurface() != s.top()->getSurface())
    //         return false;
    //     temp_elements.pop();
    //     // s.pop();
    // }
    // return true;
// }