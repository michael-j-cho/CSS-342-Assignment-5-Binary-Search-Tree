#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <vector>

using namespace std;

class ThreadedBST {

private:
    struct TreeNode {
        explicit TreeNode(int data) : left(nullptr), right(nullptr), data(data) {};
        TreeNode* left;
        TreeNode* right;
        int data;
        TreeNode* leftThread;
        TreeNode* rightThread;
    };
    TreeNode* root;
    int count = 0;

    void removeOneChild(TreeNode* prevPtr, TreeNode* delPtr);
    void removeTwoChild(TreeNode* prevPtr, TreeNode* inorderPtr, TreeNode* delPtr, TreeNode* prevInorderPointer);

public:
    ThreadedBST();
    explicit ThreadedBST(int n);
    ~ThreadedBST();

    void insert(TreeNode* node, TreeNode* newNode);
    bool add(int data);
    void balancedAdd(vector<int> vect);
    bool remove(int data);
    void thread();
    void threadRecur(TreeNode* threadTarget, TreeNode* threader);
    bool retrieve(const TreeNode& node1, TreeNode node2);
    void clear(TreeNode*& root);
    bool contains(int target);
    void inorder() const;
    int getHeight();
    int heightHelper(TreeNode* node) const;
    int getCount() const;

};

#endif