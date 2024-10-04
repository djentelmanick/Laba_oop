#include "builder.h"
#include <vector>
#include <iostream>
using namespace std;

// ������������� ����������� ����������
vector<vector<vector<int>>> Element::assembly;


// ����������� �� ���������
Element::Element() : surface(ROW, vector<int>(COL, 0)), connectors{}, other_sockets{} {}


// ����������� �������������
Element::Element(const vector<pair<int, int>>& c, const vector<pair<int, int>>& s) 
    : surface(ROW, vector<int>(COL, 0)), connectors(c), other_sockets(s) {
    // ������������� ����� � ������������ �� ����������� 
    for (const pair<int, int>& connector : connectors) {
        surface[connector.first][connector.second] = 2;  // ���������� ������� ����������� � ������ ��� 2
    }
    for (const pair<int, int>& other_socket : other_sockets) {
        surface[other_socket.first][other_socket.second] = 1;  // ���������� ������ � ������� ��� �������� �����������
    }
    // assembly.push_back(surface);
}


// ����������� �����������
Element::Element(const Element& el) {
    surface = el.surface;
    connectors = el.connectors;
    other_sockets = el.other_sockets;
}


// ����� ��� ��������, ����� �� ������ ������������� ������� ������������ � ������������ �������� �������
bool Element::canConnect(const Element& checked_el) const {
    if (connectors.size() == 0) {
        cout << "���������� ������ �� ���� ����������� �������� ��������, ��� ��� � ���� �� ���!\n";
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
        cout << "�������� ������ ��� ����������� �������� �������� ������������ ���������\n";
        return true;
    }
    if (one_connector) {
        cout << "�������� ������ ����� ������������ �������� �������� ������������ ���������\n";
        return true;
    }
    cout << "���������� ������ �� ���� ����������� �������� �������� ������������ ���������, ��������� �������!\n";
    return false;
}


// ����� ��� ����������� �����������
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
    cout << "��� ������ �������\n";
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
    cout << "��� ������� �����. Ÿ ����������������: " << functional << "\n";
    return true;
}
