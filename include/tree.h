// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

struct TreeNode {
    char value;
    std::vector<std::unique_ptr<TreeNode>> children;
    explicit TreeNode(char val) : value(val) {}
};
class PMTree {
 private:
    std::vector<std::unique_ptr<TreeNode>> roots;
    std::vector<char> alphabet;
    void buildTree(TreeNode* node, std::vector<char> remaining);
    bool getPermByNumber(TreeNode* node, int& num, std::vector<char>& current,
                        std::vector<char>& result, int depth);

 public:
    explicit PMTree(const std::vector<char>& input);
    ~PMTree() = default;
    void traverse(TreeNode* node, std::vector<char>& current,
                  std::vector<std::vector<char>>& result);
    const std::vector<std::unique_ptr<TreeNode>>& getRoots() const {
        return roots;
    }
    const std::vector<char>& getAlphabet() const { return alphabet; }
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
