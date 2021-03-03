/**
 * Michael Cho
 * Tim D
 * 
 * CSS342
 *
 * */

#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <iostream>

using namespace std;

class ThreadedBST{

private:
    struct TreeNode {
        explicit TreeNode(int data) : left(nullptr), right(nullptr), data(data) {};
        TreeNode *left;
        TreeNode *right;
        int data;
    };
    TreeNode *root;

public:
    ThreadedBST();
    explicit ThreadedBST(int data);
    ~ThreadedBST();

    void insert(TreeNode *node, TreeNode *newNode);
    bool add(int data);
    bool remove(const TreeNode *nodeToRemove);
    bool retrieve(const TreeNode &node1, TreeNode node2);
    void clear();
    bool contains(const TreeNode &node);
    void display() const;
    bool isEmpty() const;
    int height() const;
    int getCount() const;

};

#endif