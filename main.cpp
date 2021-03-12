/**
 * Michael Cho
 * Tim D
 *
 * CSS342
 *
 * This is the main driver file that is running the tests.
 * */

#include "threadedBST.h"
#include <cassert>
#include <iostream>

using namespace std;

// Testing constuctors, inorderPrint, and removeEven.
void test1() {
  cout << "\n****Begin Tests for Constuctor****\n";
  cout << "\nCreating ThreadedBST tree1 (n = 20):\n";
  ThreadedBST tree1(20);
  tree1.inorderPrint();

  cout << "\n\n****Testing Copy Constructor****\n";
  cout << "\nCopying tree1 into tree2:\n";
  ThreadedBST tree2(tree1);
  tree2.inorderPrint();
  cout << "\n\nDeleting even nodes:\n";
  tree2.removeEven();
  tree2.inorderPrint();

  cout << "\n\n****Testing Overloaded = Operator****\n";
  ThreadedBST tree3;
  cerr << endl << "Copying tree1 into tree3:\n";
  tree3 = tree1;
  tree3.inorderPrint();
  cout << "\n\nDeleting even nodes:\n";
  tree1.removeEven();
  tree1.inorderPrint();
  cout << endl;
}

// Testing copy constuctor
void test2() {
  ThreadedBST tree2(20);
  cout << endl << endl;
  ThreadedBST tree3(tree2);
}

void removetest() {

  ThreadedBST tree1(20);
  tree1.remove(5);
  tree1.remove(14);
  tree1.remove(10);
}

void threadtest() {
  ThreadedBST tree1;
  tree1.add(6);
  tree1.add(3);
  tree1.add(1);
  tree1.add(2);
  tree1.add(5);
  tree1.add(8);
  tree1.add(7);
  tree1.add(11);
  tree1.add(9);
  tree1.add(13);
  tree1.thread();
}

void officialtest() {
  cout << "Input number of nodes from 1-n to put into a BST";
  int n;
  cin >> n;
  while (n <= 0) {
    cout << "Not a valid number, please input a number greater than 0";
    cin >> n;
  }
  ThreadedBST tree(n);
  // tree.inorder();
  ThreadedBST treecopy(tree);
  // treecopy.inorder();
}

int main() {
  test1();
  // test2();
  // removetest();
  // threadtest();
  cout << endl << "Done." << endl;
  return 0;
}