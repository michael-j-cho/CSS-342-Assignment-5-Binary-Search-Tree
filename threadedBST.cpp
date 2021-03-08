/**
 * Michael Cho
 * Tim D
 *
 * CSS342
 *
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include "threadedBST.h"

using namespace std;

ThreadedBST::ThreadedBST() : root{ nullptr }, count{ 0 } {}

ThreadedBST::ThreadedBST(int n) : root{ nullptr }, count{ 0 } {
   
    vector<int> vect1;
    vector<int> vect2;
    if(n % 2 == 1) {
        if(root == nullptr) {
            int mid = n/2 + 1;
            add(mid);
        }
        for(int i = 1; i <= n / 2 + 1; i++) {
            vect1.push_back(i);
        }
        for(int i = 1; i <= n / 2; i++) {
            vect2.push_back(i + ((n/2) + 1));
        }        
    } else {
        if(root == nullptr) {
            int mid = n/2;
            add(mid);
        }
        for(int i = 1; i <= n / 2; i++) {
            vect1.push_back(i);
        }
        for(int i = 1; i <= n / 2; i++) {
            vect2.push_back(i + (n/2));
        }
    }

    balancedAdd(vect1);
    balancedAdd(vect2);
}

ThreadedBST::ThreadedBST(const ThreadedBST &tree) : root{nullptr}, count{0} {
    if(tree.root == nullptr) {
        root = nullptr;
    } 
    else {
        copy(tree.root);
    }
    deleteEven(this->root);
}

ThreadedBST::~ThreadedBST()
{
    clear(root);
}

void ThreadedBST::insert(TreeNode* node, TreeNode* newNode) {
    if (newNode->data < node->data && node->left != nullptr) {
        insert(node->left, newNode);
    }
    if (newNode->data > node->data && node->right != nullptr) {
        insert(node->right, newNode);
    }
    if (newNode->data < node->data && node->left == nullptr) {
        node->left = newNode;
    }
    if (newNode->data > node->data && node->right == nullptr) {
        node->right = newNode;
    }
}

bool ThreadedBST::add(int data) {
    if (contains(data)) {
        return false;
    }
    if (root == nullptr) {
        root = new TreeNode(data);
    }
    else {
        TreeNode* newNode = new TreeNode(data);
        insert(root, newNode);
    }
    count++;
    cout << data << ", ";
    return true;
}

void ThreadedBST::balancedAdd(vector<int> vect) {
    if(vect.size() > 0) {
        add(vect.at(vect.size() / 2));
        vect.erase(vect.begin() + vect.size()/2);
        
        vector<int> splitLow(vect.begin(), vect.begin() + vect.size()/2);
        vector<int> splitHigh(vect.begin() + vect.size()/2, vect.end());

        balancedAdd(splitLow);
        balancedAdd(splitHigh);
    }
}

bool ThreadedBST::remove(int data) {
    if (!contains(data)) {
        return false;
    }
    TreeNode* prevPtr = root;
    TreeNode* delPtr;
    if (data < root->data)
        delPtr = root->left;
    else if (data > root->data)
        delPtr = root->right;
    else
        delPtr = root;

    while (data != delPtr->data) {
        if (data < delPtr->data)
        {
            prevPtr = delPtr;
            delPtr = delPtr->left;
        }
        else if (data > delPtr->data)
        {
            prevPtr = delPtr;
            delPtr = delPtr->right;
        }
    }

    if (delPtr->left == nullptr && delPtr->right == nullptr)
    {
        if (delPtr->data < prevPtr->data)
            prevPtr->left = nullptr;
        else
            prevPtr->right = nullptr;
        delete delPtr;
        delPtr = nullptr;
    }
    else if (delPtr->left != nullptr && delPtr->right != nullptr)
    {
        TreeNode* inorderPointer = delPtr->right;
        TreeNode* prevInorderPointer = nullptr;
        while (inorderPointer->left != nullptr)
        {
            prevInorderPointer = inorderPointer;
            inorderPointer = inorderPointer->left;
        }

        removeTwoChild(prevPtr, inorderPointer, delPtr, prevInorderPointer);
    }
    else
    {
        removeOneChild(prevPtr, delPtr);
    }
    count--;
    return true;
}

void ThreadedBST::copy(TreeNode *node) {
    add(node->data);
    if (node->left != nullptr) {
        copy(node->left);
    }
    if (node->right != nullptr) {
        copy(node->right);
    }
}

void ThreadedBST::deleteEven(TreeNode *node) {
    if(node->data % 2 == 0) {
        // remove(node->data);
        cout << "Deleting " << node->data << endl;
    }
    if(node->left != nullptr) {
        deleteEven(node->left);
    }
    if(node->right != nullptr) {
        deleteEven(node->right);
    }
}

void ThreadedBST::removeOneChild(TreeNode* prevPtr, TreeNode* delPtr)
{
    if (prevPtr->data < delPtr->data)
    {
        if (delPtr->left != nullptr)
            prevPtr->right = delPtr->left;

        else if (delPtr->right != nullptr)
            prevPtr->right = delPtr->right;
    }
    else if (prevPtr->data > delPtr->data)
    {
        if (delPtr->left != nullptr)
            prevPtr->left = delPtr->left;

        else if (delPtr->right != nullptr)
            prevPtr->left = delPtr->right;

    }

    delete delPtr;
    delPtr = nullptr;
}

void ThreadedBST::removeTwoChild(TreeNode* prevPtr, TreeNode* inorderPtr, TreeNode* delPtr, TreeNode* prevInorderPointer)
{
    if (prevInorderPointer == nullptr)
    {
        inorderPtr->left = delPtr->left;

        if (inorderPtr->data < prevPtr->data)
            prevPtr->left = inorderPtr;

        else if (inorderPtr->data > prevPtr->data)
            prevPtr->right = inorderPtr;

        delete delPtr;
        delPtr = nullptr;
    }

    else if (delPtr == root)
    {
        inorderPtr->left = delPtr->left;
        inorderPtr->right = delPtr->right;

        delete delPtr;
        delPtr = nullptr;

        root = inorderPtr;
        prevInorderPointer->left = nullptr;
    }

    else
    {
        inorderPtr->left = delPtr->left;
        inorderPtr->right = delPtr->right;

        if (inorderPtr->data < prevPtr->data)
            prevPtr->left = inorderPtr;

        else if (inorderPtr->data > prevPtr->data)
            prevPtr->right = inorderPtr;

        prevInorderPointer->left = nullptr;

        delete delPtr;
        delPtr = nullptr;
    }



}

bool ThreadedBST::retrieve(const TreeNode& node1, TreeNode node2) {
    return true;
}

void ThreadedBST::clear(TreeNode*& Node)
{

    if (Node->left != nullptr)
        clear(Node->left);

    if (Node->right != nullptr)
        clear(Node->right);

    delete Node;
    Node = nullptr;


}

bool ThreadedBST::contains(int target)
{
    if (root == nullptr)
        return false;

    TreeNode* curPtr = root;

    while (curPtr->data != target)
    {

        if (target < curPtr->data)
        {
            if (curPtr->left == nullptr)
                return false;
            else
                curPtr = curPtr->left;
        }

        else if (target > curPtr->data)
        {
            if (curPtr->right == nullptr)
                return false;
            else
                curPtr = curPtr->right;
        }
    }

    return true;

}

void ThreadedBST::thread()
{
    TreeNode* threadTarget = root;
    TreeNode* threader;
}

void ThreadedBST::threadRecur(TreeNode* threadTarget, TreeNode* threader)
{
    threader = threadTarget->left;
    while (threader->right != nullptr)
    {
        if (threader->left != nullptr)
        {
            threadTarget = threader;
            threadRecur(threadTarget, threader);
        }

    }

    threader->rightThread = threadTarget;
}

void ThreadedBST::inorder() const {

}

int ThreadedBST::getHeight() {
    return heightHelper(root);
}

int ThreadedBST::heightHelper(TreeNode *node) const {
    if(node == nullptr) {
        return 0;
    } else {
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }
}

int ThreadedBST::getCount() const {
    return count;
}