/**
 * Michael Cho
 * Tim D
 * 
 * CSS342
 *
 * */

#include <iostream>
#include <vector>
#include "threadedBST.h"

using namespace std;

ThreadedBST::ThreadedBST() : root{nullptr}, count{0} {}

ThreadedBST::ThreadedBST(int n) : root{nullptr}, count{0} {
    int counter = 1;
    int mid = n / 2 +1;
    add(mid);
    if(n % 2 == 1) {
        mid++;
    }
    vector<int> firstHalf;
    vector<int> secondHalf;
    while (counter < (n / 2)) {
        firstHalf.push_back(counter);
        // cout << counter << ", ";
        secondHalf.push_back(++mid);
        // cout << mid << ", ";
        counter++;
    }
    if(n % 2 == 1) {
        firstHalf.push_back(counter);
        // cout << counter << ", ";
    }

    cout << endl << endl;
    balancedAdd(firstHalf);
    balancedAdd(secondHalf);
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
     if(contains(data)) {
         return false;
     }
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

void ThreadedBST::balancedAdd(vector<int> vect) {
    if(vect.size() != 0) {
        add(vect[vect.size() / 2]);
        vect.erase(vect.begin() + (vect.size() / 2));
        balancedAdd(vect);
    }
}

bool ThreadedBST::remove(int data) {
     if(!contains(data)) {
         return false;
     }
    TreeNode *node = root;
    while(data != node->data) {
        if(data < node->data) {
            node = node->left;
        } else if (data > node->data) {
            node = node->right;
        }
    }
    cout << endl << "Found " << node->data;
    delete node;
    node = nullptr;
    cout << endl << "Deleted.";
    return true;
}

bool ThreadedBST::retrieve(const TreeNode &node1, TreeNode node2) {
return true;
}

void ThreadedBST::clear() 
{

}

bool ThreadedBST::contains(const TreeNode* Node, int target)
{

    if (Node == nullptr || (Node->left == nullptr && Node->right == nullptr))
        return false;

    if (Node->data == target)
        return true;

    if (Node->data < target)
        contains(Node->right, target);

    if (Node->data > target)
        contains(Node->left, target);

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
