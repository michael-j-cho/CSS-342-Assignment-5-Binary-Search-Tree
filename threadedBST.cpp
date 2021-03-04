/**
 * Michael Cho
 * Tim D
 * 
 * CSS342
 *
 * */

#include <iostream>
#include "threadedBST.h"

using namespace std;

ThreadedBST::ThreadedBST() : root{nullptr}, count{0} {}

ThreadedBST::ThreadedBST(int n) : root{nullptr}, count{0} {
    int front = 1;
    int mid = n / 2;
    int nodesToAdd = n;
    add(mid);
    while(nodesToAdd != 0) {
        add(--mid);
        add(front++);
        nodesToAdd--;
    }
}

ThreadedBST::~ThreadedBST(){}

void ThreadedBST::insert(TreeNode *node, TreeNode *newNode) {
    if(newNode->data < node->data && node->left != nullptr) {
        insert(node->left, newNode);
    }
    if(newNode->data > node->data && node->right != nullptr) {
        insert(node->right, newNode);
    }
    if(newNode->data < node->data && node->left == nullptr) {
        node->left = newNode;
    }
    if(newNode->data > node->data && node->right == nullptr) {
        node->right = newNode;
    }
}

bool ThreadedBST::add(int data) {
    // if(contains(data)) {
    //     return false;
    // }
    if(root == nullptr) { 
        root = new TreeNode(data);
    } else {
        TreeNode *newNode = new TreeNode(data);
        insert(root, newNode);
    }
    count++;
    cout << data << ", ";
    return true;
}

bool ThreadedBST::remove(const TreeNode *nodeToRemove) {
return true;
}

bool ThreadedBST::retrieve(const TreeNode &node1, TreeNode node2) {
return true;
}

void ThreadedBST::clear() {

}

bool ThreadedBST::contains(const TreeNode &node) {
return true;
}

void ThreadedBST::inorder() const {

}

bool ThreadedBST::isEmpty() const {
return count == 0;
}

int ThreadedBST::height() const {
return 0;
}

int ThreadedBST::getCount() const {
return count;
}
