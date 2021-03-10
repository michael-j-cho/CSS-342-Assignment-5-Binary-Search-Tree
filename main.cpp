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

// Testing constructor, add, and contains methods.
void test1() {
  ThreadedBST tree1(20);
  tree1.thread();
  tree1.inorder();
  // assert(!tree1.contains(21));
  // //tree1.add(21);                  adding after threading will crash program (destructor dont work)
  // assert(tree1.contains(20));
  // cout << endl << endl;
}

// // Testing copy constuctor
// void test2() {
//   ThreadedBST tree2(20);  
//   cout << endl << endl;
//   ThreadedBST tree3(tree2);
//   tree2.thread();
//   tree3.thread();
// }

// void removetest() {
//   ThreadedBST tree1;
//   tree1.add(10);
//   tree1.add(15);
//   tree1.add(5);
//   tree1.add(3);
//   tree1.add(7);
//   tree1.add(12);
//   tree1.add(9);
//   tree1.add(6);
//   tree1.add(8);
//   tree1.add(11);
//   /* tree1.remove(8);
//    assert(!tree1.contains(8));
//    tree1.remove(12);
//    assert(!tree1.contains(12));
//    tree1.remove(7);
//    assert(!tree1.contains(7));*/
//   tree1.remove(10);
//   tree1.thread()2;
// }

// void threadtest() {
//   ThreadedBST tree1;
//   tree1.add(6);
//   tree1.add(3);
//   tree1.add(1);
//   tree1.add(2);
//   tree1.add(5);
//   tree1.add(8);
//   tree1.add(7);
//   tree1.add(11);
//   tree1.add(9);
//   tree1.add(13);
//   tree1.thread();
//   cout << endl;
//   tree1.inorder();
// }

// void officialtest() {
//   cout << "Input number of nodes from 1-n to put into a BST";
//   int n;
//   cin >> n;
//   while (n <= 0) {
//     cout << "Not a valid number, please input a number greater than 0";
//     cin >> n;
//   }
//   ThreadedBST tree(n);
//   tree.inorder();
//   ThreadedBST treecopy(tree);
//   treecopy.inorder();
// }

int main() {
  test1();
  // test2();
  // removetest();
  //threadtest();
  cout << endl << "Done." << endl;
  return 0;
}