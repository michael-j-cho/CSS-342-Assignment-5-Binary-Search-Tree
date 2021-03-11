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
  thread();
}

/** Constructor: Constructor copy
Precondition: None
Postcondition: Creates a copy of a Threaded BST tree*/
ThreadedBST::ThreadedBST(const ThreadedBST &tree) : root{nullptr}, count{0} {
  if (tree.root == nullptr) {
    root = nullptr;
  } else {
    copy(tree.root);
    thread();
  }
}

/** Destructor: Calls the clear method
Precondition: ThreadedBST tree object must exist
Postcondition: Deletes the ThreadedBST tree object with the clear method*/
ThreadedBST::~ThreadedBST() { clear(); }

/** Clear: Deletes each dynamically created TreeNode in the ThreadedBST
tree object and sets each one to nullptr
Precondition: ThreadedBST tree object must exist
Postcondition: Deletes all TreeNodes*/
void ThreadedBST::clear() {
  TreeNode *curPtr = root;
  TreeNode *delPtr;

  while (curPtr->left != nullptr)
    curPtr = curPtr->left;
  delPtr = curPtr;

  while (curPtr != root) {
    curPtr = curPtr->right;
    delete delPtr;
    delPtr = nullptr;
    delPtr = curPtr;
  }

  while (curPtr->right != nullptr)
    curPtr = curPtr->right;
  delPtr = curPtr;

  while (curPtr != root) {
    curPtr = curPtr->left;
    delete delPtr;
    delPtr = nullptr;
    delPtr = curPtr;
  }

  delete delPtr;
  delPtr = nullptr;
  curPtr = nullptr;
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
  cerr << data << ", ";
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

  if (delPtr->leftThread == true && delPtr->rightThread == true) // Removing node with no real connections
  {

    removeZeroChild(delPtr, prevPtr);
  }

  else if (delPtr->left == nullptr) // Removing left edge
  {
    prevPtr->left = delPtr->right;
    delPtr->right->left = nullptr;
    delPtr->right->leftThread = false;

    delete delPtr;
    delPtr = nullptr;
  }

  else if (delPtr->right == nullptr) // Removing Right Edge
  {
    prevPtr->right = delPtr->left;
    delPtr->left->right = nullptr;
    delPtr->left->rightThread = false;

    delete delPtr;
    delPtr = nullptr;
  }

  else if (delPtr->leftThread == false && delPtr->rightThread == false) // Removing node with two real connections
  {
    TreeNode *inorderPtr = delPtr->right;
    TreeNode *leftInorderThreader = delPtr->left;
    TreeNode *prevInorderPtr = nullptr;

    removeTwoChild(delPtr, prevPtr, inorderPtr, prevInorderPtr,
                   leftInorderThreader);

  }

  else if (delPtr->leftThread == false || delPtr->rightThread == false) { // Removing node with one real connection
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
  if (!node->leftThread && node->left != nullptr) {
    copy(node->left);
  }
  if (!node->rightThread && node->right != nullptr) {
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
  if (node->leftThread == false && node->left != nullptr) {
    removeEvenHelper(node->left);
  }
  if (node->rightThread == false && node->right != nullptr) {
    removeEvenHelper(node->right);
  }

  if (node->data % 2 == 0) {
    remove(node->data);
  }
}

void ThreadedBST::removeZeroChild(TreeNode *delPtr, TreeNode *prevPtr) {
  if (prevPtr->leftThread == true || prevPtr->rightThread ==true) // Checks if previous has a thread for threading reasons
  {
    if (delPtr->data > prevPtr->data) {
      prevPtr->right = delPtr->right;
      prevPtr->rightThread = true;
    }
    if (delPtr->data < prevPtr->data) {
      prevPtr->left = delPtr->left;
      prevPtr->leftThread = true;
    }
    delete delPtr;
    delPtr = nullptr;
  }

  if (prevPtr->leftThread == false && prevPtr->rightThread ==
          false) // Checks if it does not have a thread for threading reasons
  {
    if (prevPtr->right == delPtr) {
      prevPtr->right = delPtr->right;
      prevPtr->rightThread = true;
    } else if (prevPtr->left == delPtr) {
      prevPtr->left = delPtr->left;
      prevPtr->leftThread = true;
    }

    delete delPtr;
    delPtr = nullptr;
  }
}

/** Remove One Child: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::removeOneChild(TreeNode *prevPtr, TreeNode *delPtr) {
  if (delPtr->data > prevPtr->data) {
    prevPtr->right = delPtr->right;
    delPtr->right->left = prevPtr;
  }
  if (delPtr->data < prevPtr->data) {
    prevPtr->left = delPtr->left;
    delPtr->left->right = prevPtr;
  }
  delete delPtr;
  delPtr = nullptr;
}

/** Remove Two Child: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::removeTwoChild(TreeNode *delPtr, TreeNode *prevPtr,
                                 TreeNode *inorderPtr, TreeNode *prevInorderPtr,
                                 TreeNode *leftInorderThreader) {
  if (delPtr == root) // Removing root
  {
    while (inorderPtr->leftThread == false) {
      prevInorderPtr = inorderPtr;
      inorderPtr = inorderPtr->left;
    }

    while (leftInorderThreader->rightThread == false)
      leftInorderThreader = leftInorderThreader->right;

    if (prevInorderPtr != nullptr) {
      prevInorderPtr->left = inorderPtr;
      prevInorderPtr->leftThread = true;
    }
    if (inorderPtr->rightThread == false && prevInorderPtr != nullptr) {
      prevInorderPtr->left = inorderPtr->right;
      prevInorderPtr->leftThread = false;
    }

    inorderPtr->left = delPtr->left;
    inorderPtr->leftThread = false;
    inorderPtr->right = delPtr->right;
    inorderPtr->rightThread = false;
    leftInorderThreader->right = inorderPtr;

    delete delPtr;
    delPtr = nullptr;

    root = inorderPtr;
  }

  else {

    
    while (inorderPtr->leftThread == false) {
      prevInorderPtr = inorderPtr;
      inorderPtr = inorderPtr->left;
    }

    while (leftInorderThreader->rightThread == false)
      leftInorderThreader = leftInorderThreader->right;

    inorderPtr->left = delPtr->left;
    inorderPtr->leftThread = false;
    leftInorderThreader->right = inorderPtr;
    if (prevInorderPtr == nullptr)
      inorderPtr->rightThread = true;

    if (prevInorderPtr != nullptr) {
      inorderPtr->rightThread = false;
      prevInorderPtr->left = inorderPtr;
      prevInorderPtr->leftThread = true;
    } else if (inorderPtr->rightThread == false && prevInorderPtr != nullptr) {
      inorderPtr->rightThread = false;
      prevInorderPtr->left = inorderPtr->right;
      prevInorderPtr->leftThread = false;
    }
    if (inorderPtr->data < prevPtr->data)
      prevPtr->left = inorderPtr;
    else
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
  TreeNode *prevThreader;
  threadLeftSideRecur(root, threader, prevThreader);
  threadRightSideRecur(root, threader, prevThreader);
}

/** Thread Recursion: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::threadLeftSideRecur(TreeNode *threadTarget, TreeNode *threader, TreeNode *prevThreader) {

 while (threadTarget != nullptr) // Traversing
  {
    if (threadTarget->data > root->data) // Base case to end traversing left
      break;
    if (threadTarget->left != nullptr) // Checks to see if left side has something to thread, will do for each node
                 
      threader = threadTarget->left;
    else {
      threadTarget = threadTarget->right; // Moves to the right when finished with left-most side
      continue;
    }

    if (threader->left != nullptr) // will thread the left side of the target before going right
      threadLeftSideRecur(threadTarget->left, threader, prevThreader);

    TreeNode *starterThreader = threader; // Threading, used to keep track of what inorder node should thread to
    prevThreader = threader;
    while (threader != nullptr) {

      if (threader->right == nullptr) {
        threader->right = threadTarget; // Threads right
        threader->rightThread = true;   // Lets computer know right is a thread
        break;
      }
      threader = threader->right; // Traversing to next inorder spot

      if (threader->left != nullptr) {
        TreeNode *parent = threader; // Used to bring threader back after threading inorder to the left
        while (threader->left != nullptr)
          threader = threader->left;
        threader->left = starterThreader; // Threading left
        threader->leftThread = true;      // Lets computer know left is a thread
        threader = parent; // Brings threader back to keep traversing
        prevThreader = threader;
      }

      if (threader->left == nullptr) {
        threader->left = prevThreader; // Threads left as it traverses right
        threader->leftThread = true;
        prevThreader = threader;
        continue;
      }
    }
    threadTarget = threadTarget->right;
  }
}

void ThreadedBST::threadRightSideRecur(TreeNode *threadTarget, TreeNode *threader, TreeNode *prevThreader) {
  while (
      threadTarget !=
      nullptr) // Same logic for threadRightSideRecur, but inverted, traversing
  {
    if (threadTarget->data < root->data)
      break;
    if (threadTarget->right != nullptr && threadTarget->rightThread == false)
      threader = threadTarget->right;
    else {
      threadTarget = threadTarget->left;
      continue;
    }

    if (threader->right != nullptr &&
        threader->rightThread == false) // Checking right before moving left
      threadRightSideRecur(threadTarget->right, threader, prevThreader);

    TreeNode *starterThreader = threader; // Threading
    prevThreader = threader;
    while (threader != nullptr) {

      if (threader->left == nullptr) {
        threader->left = threadTarget;
        threader->leftThread = true;
        break;
      }
      threader = threader->left;

      if (threader->right == nullptr) {
        threader->right = prevThreader;
        threader->rightThread = true;
        prevThreader = threader;
        continue;
      }
    }
    if (threadTarget->left != nullptr && threadTarget != root) {
      if (threadTarget->left->rightThread == false) {
        threader = threadTarget->left;
        while (threader->right != nullptr)
          threader = threader->right;
        threader->right = threadTarget;
        threader->rightThread = true;
      }
    }
    threadTarget = threadTarget->left;
  }
  }

/** In Order: ************
Precondition: ************
Postcondition: *************/
void ThreadedBST::inorderPrint() const {
    TreeNode *curr = root;
    while (curr->left != nullptr) {
      curr = curr->left;
    }

    while (curr != nullptr) {
      while (curr->rightThread == false) {
        if (curr->leftThread == false && curr->left != nullptr) {
          curr = curr->left;
          continue;
        }

        cout << curr->data << ", ";
        curr = curr->right;
      }
      if (curr != nullptr) {
        if (curr->right == nullptr) {
          cout << curr->data;
          curr = curr->right;
        } else {
          cout << curr->data << ", ";
          curr = curr->right;
        }
      }

      if (curr != nullptr) {
        if (curr->right == nullptr) {
          cout << curr->data;
          curr = curr->right;
        } else {
          cout << curr->data << ", ";
          curr = curr->right;
        }
      }
    }
  }

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

ThreadedBST& ThreadedBST::operator=(const ThreadedBST& tree) {
  ThreadedBST *treeCopy = new ThreadedBST(tree);
  return *treeCopy;
}