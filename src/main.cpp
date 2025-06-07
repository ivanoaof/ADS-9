// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>

void printVector(const std::vector<char>& vec) {
    for (char c : vec) {
        std::cout << c;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    std::cout << "All permutations of 1, 2, 3:\n";
    auto perms = getAllPerms(tree);
    for (const auto& perm : perms) {
        printVector(perm);
    }
    std::cout << "\nGetting individual permutations:\n";
    for (int i = 1; i <= 6; ++i) {
        std::cout << "Permutation #" << i << " (getPerm1): ";
        printVector(getPerm1(tree, i));
        std::cout << "Permutation #" << i << " (getPerm2): ";
        printVector(getPerm2(tree, i));
    }
    std::vector<char> empty;
    PMTree empty_tree(empty);
    std::cout << "\nEmpty tree permutations count: " 
              << empty_tree.getPermutationsCount() << std::endl;
    std::vector<char> single = {'A'};
    PMTree single_tree(single);
    std::cout << "\nSingle element tree permutations:\n";
    auto single_perms = getAllPerms(single_tree);
    for (const auto& perm : single_perms) {
        printVector(perm);
    }
    std::cout << "\nTesting non-existent permutations:\n";
    auto invalid1 = getPerm1(tree, 7);
    std::cout << "Permutation #7 (should be empty): ";
    printVector(invalid1);
    auto invalid2 = getPerm2(tree, 0);
    std::cout << "Permutation #0 (should be empty): ";
    printVector(invalid2);
    return 0;
}
