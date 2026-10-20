#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <utility>
#include <vector>

template <typename It>
void insertsort(It first, It last) {
    if (first == last) return;
    for (It i = std::next(first); i != last; ++i) {
        auto key = std::move(*i);
        It j = i;
        while (j != first && key < *std::prev(j)) {
            *j = std::move(*std::prev(j));
            --j;
        }
        *j = std::move(key);
    }
}

template <typename T>
void test(std::vector<T> v) {
    insertsort(v.begin(), v.end());
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
    insertsort(std::begin(arr), std::end(arr));
    assert(std::is_sorted(std::begin(arr), std::end(arr)));

    std::cout << "insertsort: testy OK\n";
    return 0;
}