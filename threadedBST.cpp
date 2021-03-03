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

ThreadedBST::ThreadedBST(){}

ThreadedBST::~ThreadedBST(){}

void ThreadedBST::insert(TreeNode *newNode) {
    if(newNode->data < root->data) {
        root->left = newNode;
    }
    // if(root->right == nullptr && newNode->data > root->data) {
    //     root->right = newNode;
    // }
    // if
}

bool ThreadedBST::add(int data) {
    if(root == nullptr) { 
        root = new TreeNode(data);
    } else {
        TreeNode *newNode = new TreeNode(data);
        insert(newNode);
    }
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

void ThreadedBST::display() const {

}

bool ThreadedBST::isEmpty() const {
return true;
}

int ThreadedBST::height() const {
return 0;
}

int ThreadedBST::getCount() const {
return 0;
}