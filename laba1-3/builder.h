#ifndef BUILDER_H // Защита от многократного включения
#define BUILDER_H

#include <vector>
#include <string>
using namespace std;

class Element {
private:
    static const int ROW = 5;
    static const int COL = 7;
    static vector<vector<vector<int>>> assembly;  // трехмерная сборка  
    vector<vector<int>> surface;  // рабочая поверхность
    vector<pair<int, int>> connectors;  // индексы гнезд и соединителей
    vector<pair<int, int>> other_sockets; // индексы остальной конструкции (в ней обязаны быть гнезда)
public:
    // Конструктор по умолчанию
    Element();

    // Конструктор инициализации
    Element(const vector<pair<int, int>>& c, const vector<pair<int, int>>& s);

    // Конструктор копирования
    Element(const Element& el);

    // Метод для проверки, могут ли гнезда передаваемого объекта подключиться к соединителям текущего объекта
    bool canConnect (const Element& checked_el) const;

    // Метод для отображения поверхности
    void printSurface() const;

    // Метод (идентификатор) для проверки, является ли элемент умным
    virtual bool isSmart() const;

    // Геттеры
    vector<vector<int>> getSurface() const {return surface;}
    vector<pair<int, int>> getConnectors() const {return connectors;}
    vector<pair<int, int>> getOtherSockets() const {return other_sockets;}

    static void printMatrices();
};


class SmartElement : public Element {
private:
    string functional; 
public:
    // Конструкторы
    SmartElement();
    SmartElement(const string& func, const vector<pair<int, int>>& c, const vector<pair<int, int>>& s);
    SmartElement(const SmartElement& se);
    SmartElement(const Element& e, const string& func);
    SmartElement(const Element& e);

    // Перегруженный метод (идентификатор) для проверки функциональности
    bool isSmart() const override;

    // Геттер
    string getFunctional() const {return functional;}
};

#endif