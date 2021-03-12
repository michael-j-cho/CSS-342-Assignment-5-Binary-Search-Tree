/** 
 * Michael Cho
 * Tim D
 * 
 * CSS342
 * 
 * SkipList class header file 
 * */

#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <vector>

using namespace std;

class ThreadedBST {

private:
  // Struct for TreeNode data type.
  struct TreeNode {
    explicit TreeNode(int data) : left(nullptr), right(nullptr), data(data){};
    TreeNode *left;
    TreeNode *right;
    int data;
    bool leftThread = false;
    bool rightThread = false;
  };

  TreeNode *root;
  int count = 0;

  /** Thread Recursion: Helper methods for threading each side from root
  Precondition: thread must be called somewhere else
  Postcondition: Threads each side of the tree from root*/
  void threadLeftSideRecur(TreeNode *threadTarget, TreeNode *threader,
                           TreeNode *prevThreader);

  /** Thread Recursion: Helper methods for threading each side from root
  Precondition: thread must be called somewhere else
  Postcondition: Threads each side of the tree from root*/
  void threadRightSideRecur(TreeNode *threadTarget, TreeNode *threader,
                            TreeNode *prevThreader);

public:
  /** Constructor: Default constructor.
  Precondition: None
  Postcondition: Creates an empty ThreadedBST tree obj*/
  explicit ThreadedBST();

  /** Constructor: Constructor that takes an integer n as input and
  creates a tree with n nodes.
  Precondition: None
  Postcondition: Creates a ThreadedBST tree obj with n nodes*/
  explicit ThreadedBST(int n);

  /** Constructor: Constructor copy
  Precondition: None
  Postcondition: Creates a copy of a Threaded BST tree*/
  explicit ThreadedBST(const ThreadedBST &tree);

  /** Destructor: Calls the clear method
  Precondition: ThreadedBST tree object must exist
  Postcondition: Deletes the ThreadedBST tree object with the clear method*/
  ~ThreadedBST();

  /** Clear: Deletes each dynamically created TreeNode in the ThreadedBST
  tree object and sets each one to nullptr
  Precondition: ThreadedBST tree object must exist
  Postcondition: Deletes all TreeNodes*/
  void clear();



  /** Insert: Inserts nodes according to the rules of a Binary
  search tree.
  Precondition: ThreadedBST tree object must exist
  Postcondition: Places node in tree*/
  void insert(TreeNode *node, TreeNode *newNode);

  /** Add: Adds a specific integer into the tree. Checks for
  duplicates using contains. Calls insert to place nodes into
  tree.
  Precondition: ThreadedBST tree object must exist
  Postcondition: Returns true if add is successful*/
  bool add(int data);

  /** Balanced Add: Used in conjunction with the constructor.
  Upon initializtion of a new ThreadedBST tree, balances the nodes
  inserted throughout the tree by recursively adding the middle of
  each vector one at a time. Base case when vector is empty.
  Precondition: ThreadedBST tree object must exist
  Postcondition: ThreadedBST tree with balanced nodes*/
  void balancedAdd(vector<int> vect);

  /** Remove: Remove function that deletes nodes and rethreads based on cases
  Precondition: ThreadedBST tree object must exist
  Postcondition: Returns true removed successfully*/
  bool remove(int data);

  /** Copy: Copies a tree object to current tree. Adds first node
  which is root. Then, recursively adds each left and right node
  until the bottom each branch is reached (end of branch is has
  nullptr or is a left or right thread).
  Precondition: ThreadedBST tree object must exist
  Postcondition: Tree copied to current tree.*/
  void copy(TreeNode *node);

  /** Remove Even: Calls the removeEvenHelper method with the root
  node of current tree.
  Precondition: ThreadedBST tree object must exist
  Postcondition: Calls removeEvenHelper*/
  void removeEven();

  /** Remove Even Helper: Recursive method that removes even nodes in
  the tree. Stops when the end of a branch is reached (end of branch is
  has nullptr or is a left or right thread).
  Precondition: ThreadedBST tree object must exist
  Postcondition: Removes even nodes*/
  void removeEvenHelper(TreeNode *node);

  /** Remove One Child: Helper function that used for cases with zero children
  Precondition: Must be called in remove when it has zero children
  Postcondition: Reconnects other nodes to proper place, and deletes node*/
  void removeZeroChild(TreeNode *delPtr, TreeNode *prevPtr);

  /** Remove One Child: Helper function that used for cases with one child
  Precondition: Must be called in remove when it has one child
  Postcondition: Reconnects other nodes to proper place, and deletes node*/
  void removeOneChild(TreeNode *prevPtr, TreeNode *delPtr);

  /** Remove One Child: Helper function that used for cases with two children
  Precondition: Must be called in remove when it has two children
  Postcondition: Reconnects other nodes to proper place, and deletes node*/
  void removeTwoChild(TreeNode *delPtr, TreeNode *prevPtr, TreeNode *inorderPtr,
                      TreeNode *prevInorderPtr, TreeNode *leftInorderThreader);

  /** Contains: Boolean method that checks whether a particular value exists
  within the ThreadedBST tree.
  Precondition: ThreadedBST tree object must exist
  Postcondition: Returns true if the value is found*/
  bool contains(int target);

  /** Thread: Main method for threading, calling on helpers for each side
  Precondition: Tree must be fully created, as cannot be rethreaded with this
  method Postcondition: returns a fully threaded BST*/
  void thread();

  /** In Order: Iterator that uses threads to print out values of a threaded BST
  Precondition: Tree must be threaded for this to work
  Postcondition: Prints out values in console */
  void inorderPrint() const;

  /** Get Height: Calls the height helper method and returns the height
  Precondition:ThreadedBST tree object must exist.
  Postcondition: Returns the height of the tree*/
  int getHeight();

  /** Height Helper: Recursive method that traverses through the tree and
  tallys up the height of the tree.
  Precondition:ThreadedBST tree object must exist
  Postcondition: Returns the height of the tree*/
  int heightHelper(TreeNode *node) const;

  /** Get Count: Returns the TreeNode count of the ThreadedBST tree
  Precondition:ThreadedBST tree object must exist
  Postcondition: Returns int count*/
  int getCount() const;

  /** Operator=: Overloaded operator used for
  easily creating copy constructors
  Precondition: A tree must already exist for this to*/
  ThreadedBST &operator=(const ThreadedBST &tree);
};

#endif