// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>

template<typename T>
double measureTime(T&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1000.0;
}
void printPerm(const std::vector<char>& perm) {
    for (char c : perm) {
        std::cout << c;
    }
}
int main() {
    std::vector<char> experiment = {'1', '2', '3'};
    PMTree tree(experiment);
    std::cout << std::endl;
    auto allPerms = getAllPerms(tree);
    for (size_t i = 0; i < allPerms.size(); ++i) {
        std::cout << "Permutation " << (i + 1) << ": ";
        printPerm(allPerms[i]);
        std::cout << std::endl;
    }
    auto perm1 = getPerm1(tree, 1);
    auto perm2 = getPerm2(tree, 2);
    std::cout << "getPerm1=";
    printPerm(perm1);
    std::cout << ", getPerm2=";
    printPerm(perm2);
    std::cout << std::endl;    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << std::endl;
    std::cout << "\t\t\t" << std::endl;
    for (int n = 1; n <= 11; ++n) {
        std::vector<char> alphabet;
        for (int i = 0; i < n; ++i) {
            alphabet.push_back('A' + i);
        }
        PMTree testTree(alphabet);
        int totalPerms = 1;
        for (int i = 1; i <= n; ++i) {
            totalPerms *= i;
        }        double timeAll = 0, time1 = 0, time2 = 0;
        if (n > 0) {
            int randomPerm = (time(0) % totalPerms) + 1;
            timeAll = measureTime([&]() {
                getAllPerms(testTree);
            });
            time1 = measureTime([&]() {
                getPerm1(testTree, randomPerm);
            });
            time2 = measureTime([&]() {
                getPerm2(testTree, randomPerm);
            });
        }
        std::cout << n << "\t" << std::fixed << std::setprecision(3)
                  << timeAll << "\t\t" << time1 << "\t\t" << time2 << std::endl;
    }
    return 0;
}
