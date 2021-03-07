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
    ThreadedBST tree2(20);
    // cout << endl;
    ThreadedBST tree3(21);
    // tree2.remove(1);

}

void removetest()
{
    ThreadedBST tree1;
    tree1.add(10);
    tree1.add(15);
    tree1.add(5);
    tree1.add(3);
    tree1.add(7);
    tree1.add(12);
    tree1.add(9);
    tree1.add(6);
    tree1.add(8);
    tree1.add(11);
    /* tree1.remove(8);
     assert(!tree1.contains(8));
     tree1.remove(12);
     assert(!tree1.contains(12));
     tree1.remove(7);
     assert(!tree1.contains(7));*/
    tree1.remove(10);
}

int main() {
    //test1();
    removetest();
    cout << endl << "Done." << endl;
    return 0;
}