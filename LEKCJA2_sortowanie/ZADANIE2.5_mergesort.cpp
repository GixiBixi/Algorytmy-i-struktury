#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

template <typename It>
void mergesort(It first, It last) {
    auto n = std::distance(first, last);
    if (n < 2) return;
    It mid = std::next(first, n / 2);
    mergesort(first, mid);
    mergesort(mid, last);
    std::inplace_merge(first, mid, last);
}

template <typename T>
void test(std::vector<T> v) {
    mergesort(v.begin(), v.end());
    assert(std::is_sorted(v.begin(), v.end()));
}

int main() {
    test(std::vector<int>{});
    test(std::vector<int>{5});
    test(std::vector<int>{1, 2, 3, 4, 5});
    test(std::vector<int>{5, 4, 3, 2, 1});
    test(std::vector<int>{3, 1, 3, 2, 1, 2});

    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(-1000, 1000);
    std::vector<int> r(1000);
    for (auto& x : r) x = dist(gen);
    test(r);

    test(std::vector<std::string>{"kot", "pies", "ala", "zebra", "mysz"});

    int arr[] = {4, 2, 9, 1, 7};
    mergesort(std::begin(arr), std::end(arr));
    assert(std::is_sorted(std::begin(arr), std::end(arr)));

    std::cout << "mergesort: testy OK\n";
    return 0;
}