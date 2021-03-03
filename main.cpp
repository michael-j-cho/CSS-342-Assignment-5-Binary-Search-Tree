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

}

int main() {
  test1();
  cout << "Done." << endl;
  return 0;
}