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

void test1() {
    ThreadedBST tree;
    tree.add(1);
    tree.add(2);
    tree.display();
    ThreadedBST tree2(20);
    cout << endl;
     ThreadedBST tree3(21);

}

int main() {
  test1();
  cout << "Done." << endl;
  return 0;
}