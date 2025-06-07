// Copyright 2022 NNTU-CS
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root = nullptr;
        total_permutations = 0;
        return;
    }
    total_permutations = 1;
    for (size_t i = 1; i <= elements.size(); ++i) {
        total_permutations *= i;
    }
    root = std::make_shared<Node>('\0'); // Dummy root
    buildTree(root, elements);
}
void PMTree::buildTree(std::shared_ptr<Node> parent, 
const std::vector<char>& remaining) {
    if (remaining.empty()) {
        return;
    }
    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        parent->children.push_back(child);
        std::vector<char> new_remaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) {
                new_remaining.push_back(remaining[j]);
            }
        }
        buildTree(child, new_remaining);
    }
}
void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, current, result);
        }
    }
    if (node->value != '\0') {
        current.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.getRoot()) {
        return result;
    }
    std::vector<char> current;
    collectPermutations(tree.getRoot(), current, result);
    return result;
}
std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1 || static_cast<size_t>(num) > tree.getPermutationsCount()) {
        return {};
    }
    auto all_perms = getAllPerms(tree);
    return all_perms[num - 1];
}
std::vector<char> getPerm2Helper(
const std::shared_ptr<PMTree::Node>& node, int& remaining) {
    if (node->children.empty()) {
        if (--remaining == 0) {
            return {node->value};
        }
        return {};
    }
    for (const auto& child : node->children) {
        auto result = getPerm2Helper(child, remaining);
        if (!result.empty()) {
            if (node->value != '\0') {
                result.insert(result.begin(), node->value);
            }
            return result;
        }
    }
    return {};
}
std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1 || static_cast<size_t>(num) > tree.getPermutationsCount()) {
        return {};
    }
    int remaining = num;
    auto result = getPerm2Helper(tree.getRoot(), remaining);
    // Remove the dummy root value if present
    if (!result.empty() && result[0] == '\0') {
        result.erase(result.begin());
    }
    return result;
}

