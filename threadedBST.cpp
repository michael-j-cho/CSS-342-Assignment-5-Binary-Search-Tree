/**
 * Michael Cho
 * Tim D
 *
 * CSS342
 * **************ADD DESCRIPTION***********
 * */

#include "threadedBST.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/** Constructor: Default constructor
Precondition: None
Postcondition: Creates an empty ThreadedBST tree obj*/
ThreadedBST::ThreadedBST() : root{nullptr}, count{0} {}

/** Constructor: Constructor that takes an integer n as input and
creates a tree with n nodes
Precondition: None
Postcondition: Creates a ThreadedBST tree obj with n nodes*/
ThreadedBST::ThreadedBST(int n) : root{nullptr}, count{0} {
  vector<int> vect1;
  vector<int> vect2;
  if (n % 2 == 1) {
    if (root == nullptr) {
      int mid = n / 2 + 1;
      add(mid);
    }
    for (int i = 1; i <= n / 2 + 1; i++) {
      vect1.push_back(i);
    }
    for (int i = 1; i <= n / 2; i++) {
      vect2.push_back(i + ((n / 2) + 1));
    }
  } else {
    if (root == nullptr) {
      int mid = n / 2;
      add(mid);
    }
    for (int i = 1; i <= n / 2; i++) {
      vect1.push_back(i);
    }
    for (int i = 1; i <= n / 2; i++) {
      vect2.push_back(i + (n / 2));
    }
  }
  balancedAdd(vect1);
  balancedAdd(vect2);
}

/** Constructor: Constructor copy
Precondition: None
Postcondition: Creates a copy of a Threaded BST tree*/
ThreadedBST::ThreadedBST(const ThreadedBST &tree) : root{nullptr}, count{0} {
  if (tree.root == nullptr) {
    root = nullptr;
  } else {
    copy(tree.root);
  }
}

/** Destructor: Calls the clear method
Precondition: ThreadedBST tree object must exist
Postcondition: Deletes the ThreadedBST tree object with the clear method*/
ThreadedBST::~ThreadedBST() { clear(root); }

/** Clear: Deletes each dynamically created TreeNode in the ThreadedBST
tree object and sets each one to nullptr
Precondition: ThreadedBST tree object must exist
Postcondition: Deletes all TreeNodes*/
void ThreadedBST::clear(TreeNode *&Node) {
  if (Node->left != nullptr)
    clear(Node->left);

  if (Node->right != nullptr)
    clear(Node->right);

  delete Node;
  Node = nullptr;
}

/** Insert: ************
Precondition: ThreadedBST tree object must exist
Postcondition:*********** */
void ThreadedBST::insert(TreeNode *node, TreeNode *newNode) {
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

/** Add: ************
Precondition: ThreadedBST tree object must exist
Postcondition: Returns true add is successful*/
bool ThreadedBST::add(int data) {
  if (contains(data)) {
    return false;
  }
  if (root == nullptr) {
    root = new TreeNode(data);
  } else {
    TreeNode *newNode = new TreeNode(data);
    insert(root, newNode);
  }
  count++;
  cout << data << ", ";
  return true;
}

/** Balanced Add: ************
Precondition: ThreadedBST tree object must exist
Postcondition: *************/
void ThreadedBST::balancedAdd(vector<int> vect) {
  if (vect.size() > 0) {
    add(vect.at(vect.size() / 2));
    vect.erase(vect.begin() + vect.size() / 2);

    vector<int> splitLow(vect.begin(), vect.begin() + vect.size() / 2);
    vector<int> splitHigh(vect.begin() + vect.size() / 2, vect.end());

    balancedAdd(splitLow);
    balancedAdd(splitHigh);
  }
}

/** Remove: ************
Precondition: ThreadedBST tree object must exist
Postcondition: Returns true removed successfully*/
bool ThreadedBST::remove(int data) {
  if (!contains(data)) {
    return false;
  }
  TreeNode *prevPtr = root;
  TreeNode *delPtr;
  if (data < root->data)
    delPtr = root->left;
  else if (data > root->data)
    delPtr = root->right;
  else
    delPtr = root;

  while (data != delPtr->data) {
    if (data < delPtr->data) {
      prevPtr = delPtr;
      delPtr = delPtr->left;
    } else if (data > delPtr->data) {
      prevPtr = delPtr;
      delPtr = delPtr->right;
    }
  }

  if (delPtr->left == nullptr && delPtr->right == nullptr) {
    if (delPtr->data < prevPtr->data)
      prevPtr->left = nullptr;
    else
      prevPtr->right = nullptr;
    delete delPtr;
    delPtr = nullptr;
  } else if (delPtr->left != nullptr && delPtr->right != nullptr) {
    TreeNode *inorderPointer = delPtr->right;
    TreeNode *prevInorderPointer = nullptr;
    while (inorderPointer->left != nullptr) {
      prevInorderPointer = inorderPointer;
      inorderPointer = inorderPointer->left;
    }

    removeTwoChild(prevPtr, inorderPointer, delPtr, prevInorderPointer);
  } else {
    removeOneChild(prevPtr, delPtr);
  }
  count--;
  return true;
}

/** Copy: ************
Precondition: ThreadedBST tree object must exist
Postcondition: *************/
void ThreadedBST::copy(TreeNode *node) {
  add(node->data);
  if (node->left != nullptr) {
    copy(node->left);
  }
  if (node->right != nullptr) {
    copy(node->right);
  }
}

/** Remove Even: ************
Precondition: ThreadedBST tree object must exist
Postcondition: *************/
void ThreadedBST::removeEven() {
    removeEvenHelper(this->root);
}

/** Remove Even Helper: ************
Precondition: ThreadedBST tree object must exist
Postcondition: *************/
void ThreadedBST::removeEvenHelper(TreeNode *node) {
  if (node->left != nullptr) {
    removeEvenHelper(node->left);
  }
  if (node->right != nullptr) {
    removeEvenHelper(node->right);
  }

  if (node->data % 2 == 0) {
    remove(node->data);
    cout << endl << "Deleting " << node->data;
  }
}

/** Remove One Child: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::removeOneChild(TreeNode *prevPtr, TreeNode *delPtr) {
  if (prevPtr->data < delPtr->data) {
    if (delPtr->left != nullptr)
      prevPtr->right = delPtr->left;

    else if (delPtr->right != nullptr)
      prevPtr->right = delPtr->right;
  } else if (prevPtr->data > delPtr->data) {
    if (delPtr->left != nullptr)
      prevPtr->left = delPtr->left;

    else if (delPtr->right != nullptr)
      prevPtr->left = delPtr->right;
  }

  delete delPtr;
  delPtr = nullptr;
}

/** Remove Two Child: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::removeTwoChild(TreeNode *prevPtr, TreeNode *inorderPtr,
                                 TreeNode *delPtr,
                                 TreeNode *prevInorderPointer) {
  if (prevInorderPointer ==
      nullptr) // Used for if there is no pointer left after moving right once
               // (right once is inorder)
  {
    inorderPtr->left = delPtr->left;

    if (inorderPtr->data < prevPtr->data)
      prevPtr->left = inorderPtr;

    else if (inorderPtr->data > prevPtr->data)
      prevPtr->right = inorderPtr;

    delete delPtr;
    delPtr = nullptr;
  }

  else if (delPtr == root) {
    if (inorderPtr->right != nullptr)
      prevInorderPointer->left = inorderPtr->right;
    else
      prevInorderPointer->left = nullptr;

    inorderPtr->left = delPtr->left;
    inorderPtr->right = delPtr->right;

    delete delPtr;
    delPtr = nullptr;

    root = inorderPtr;

  }

  else {
    if (inorderPtr->right != nullptr)
      prevInorderPointer->left = inorderPtr->right;
    else
      prevInorderPointer->left = nullptr;

    inorderPtr->left = delPtr->left;
    inorderPtr->right = delPtr->right;

    if (inorderPtr->data < prevPtr->data)
      prevPtr->left = inorderPtr;

    else if (inorderPtr->data > prevPtr->data)
      prevPtr->right = inorderPtr;

    delete delPtr;
    delPtr = nullptr;
  }
}

/** Contains: Boolean method that checks whether a particular value exists
within the ThreadedBST tree
Precondition: ThreadedBST tree object must exist
Postcondition: Returns true if the value is found*/
bool ThreadedBST::contains(int target) {
  if (root == nullptr)
    return false;

  TreeNode *curPtr = root;

  while (curPtr->data != target) {

    if (target < curPtr->data) {
      if (curPtr->left == nullptr)
        return false;
      else
        curPtr = curPtr->left;
    }

    else if (target > curPtr->data) {
      if (curPtr->right == nullptr)
        return false;
      else
        curPtr = curPtr->right;
    }
  }

  return true;
}

/** Thread: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::thread() {
  TreeNode *threadTarget = root;
  TreeNode *threader = nullptr;
  threadRecurRight(root, threader);
  threadRecurLeft(root, threader);
}

/** Thread Recursion: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::threadRecurRight(TreeNode *threadTarget, TreeNode *threader) {

  while (threadTarget->right != nullptr) {
    if (threadTarget->left != nullptr)
      threader = threadTarget->left;

    if (threader->left != nullptr)
      threadRecurRight(threadTarget->left, threader);

    while (threader != nullptr) {
      if (threader->right == nullptr) {
        threader->rightThread = threadTarget;
        break;
      }
      if (threader->left != nullptr)
        threadRecurRight(threader, threader);
      threader = threader->right;
    }
    threadTarget = threadTarget->right;
  }
}

void ThreadedBST::threadRecurLeft(TreeNode *threadTarget, TreeNode *threader) {
  while (threadTarget->left != nullptr) {
    if (threadTarget->right != nullptr)
      threader = threadTarget->right;

    if (threader->right != nullptr)
      threadRecurLeft(threadTarget->right, threader);

    while (threader != nullptr) {
      if (threader->left == nullptr) {
        threader->leftThread = threadTarget;
        break;
      }
      if (threader->right != nullptr)
        threadRecurLeft(threader, threader);
      threader = threader->left;
    }
    threadTarget = threadTarget->left;
  }
}

/** In Order: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::inorder() const {}

/** Get Height: Calls the height helper method and returns the height
Precondition:ThreadedBST tree object must exist
Postcondition: Returns the height of the tree*/
int ThreadedBST::getHeight() { return heightHelper(root); }

/** Height Helper: Recursive method that traverses through the tree and
tallys up the height of the tree
Precondition:ThreadedBST tree object must exist
Postcondition: Returns the height of the tree*/
int ThreadedBST::heightHelper(TreeNode *node) const {
  if (node == nullptr) {
    return 0;
  } else {
    return 1 + max(heightHelper(node->left), heightHelper(node->right));
  }
}

/** Get Count: Returns the TreeNode count of the ThreadedBST tree
Precondition:ThreadedBST tree object must exist
Postcondition: Returns int count*/
int ThreadedBST::getCount() const { return count; }