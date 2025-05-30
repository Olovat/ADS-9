// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <vector>
#include  <utility>
#include  <memory>
#include  <numeric>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& input) : alphabet(input) {
    std::sort(alphabet.begin(), alphabet.end());
    for (char c : alphabet) {
        auto root = std::make_unique<TreeNode>(c);
        std::vector<char> remaining;
        for (char other : alphabet) {
            if (other != c) {
                remaining.push_back(other);
            }
        }
        buildTree(root.get(), remaining);
        roots.push_back(std::move(root));
    }
}
void PMTree::buildTree(TreeNode* node, std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }
    for (char c : remaining) {
        auto child = std::make_unique<TreeNode>(c);
        std::vector<char> newRemaining;
        for (char other : remaining) {
            if (other != c) {
                newRemaining.push_back(other);
            }
        }
        buildTree(child.get(), newRemaining);
        node->children.push_back(std::move(child));
    }
}
void PMTree::traverse(TreeNode* node, std::vector<char>& current,
                     std::vector<std::vector<char>>& result) {
    current.push_back(node->value);
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            traverse(child.get(), current, result);
        }
    }
    current.pop_back();
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    for (const auto& root : tree.getRoots()) {
        const_cast<PMTree&>(tree).traverse(root.get(), current, result);
    }
    return result;
}
std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num <= 0) {
        return {};
    }
    auto allPerms = getAllPerms(tree);
    if (num > static_cast<int>(allPerms.size())) {
        return {};
    }
    return allPerms[num - 1];
}
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num <= 0) {
        return {};
    }
    const auto& alphabet = tree.getAlphabet();
    int n = static_cast<int>(alphabet.size());
    int totalPerms = factorial(n);
    if (num > totalPerms) {
        return {};
    }
    std::vector<char> result;
    std::vector<char> remaining = alphabet;
    int currentNum = num - 1;
    for (int level = 0; level < n; level++) {
        int permsPerBranch = factorial(n - level - 1);
        int branchIndex = currentNum / permsPerBranch;
        result.push_back(remaining[branchIndex]);
        remaining.erase(remaining.begin() + branchIndex);
        currentNum %= permsPerBranch;
    }
    return result;
}
