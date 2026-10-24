#include <cassert>
#include <iostream>
#include <stdexcept>
#include "arraylist.hpp"

int main() {
    ArrayList<int> a(1);
    assert(a.empty() && a.capacity() == 1);
    a.push_back(10);
    assert(a.capacity() == 1);
    a.push_back(20);
    assert(a.capacity() == 2);
    a.push_back(30);
    assert(a.capacity() == 4);
    a.push_back(40);
    a.push_back(50);
    assert(a.capacity() == 8 && a.size() == 5);

    a.insert(2, 99);
    assert(a.size() == 6 && a[2] == 99 && a[3] == 30 && a[5] == 50);

    a.erase(2);
    assert(a.size() == 5 && a[2] == 30);

    a.erase(0);
    a.erase(0);
    a.erase(0);
    assert(a.size() == 2 && a.capacity() == 4);

    bool thrown = false;
    try { a.at(5); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    ArrayList<int> b(4);
    for (int i = 0; i < 1000; ++i) b.push_back(i);
    assert(b.size() == 1000 && b.capacity() == 1024);
    for (int i = 0; i < 1000; ++i) assert(b[i] == i);

    while (!b.empty()) b.pop_back();
    assert(b.capacity() == 4);

    ArrayList<int> c(2);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    ArrayList<int> d = c;
    d[0] = 100;
    assert(c[0] == 1 && d[0] == 100 && d.size() == 3);
    c = d;
    assert(c[0] == 100);

    std::cout << "Wszystkie testy OK\n";
    return 0;
}