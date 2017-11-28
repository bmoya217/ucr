#include <iostream>
#include <vector>
#include <stack>
#include "composite.h"
#include "iterator.h"

using namespace std;

int main() {
    //create nums
    Op* one = new Op(1);
    Op* two = new Op(2);
    Op* three = new Op(3);
    Op* six = new Op(6);
    Op* seven = new Op(7);
    Op* eight = new Op(8);
    Op* ten = new Op(10);

    //first tree (where the root is always the last made)
    Sqr* sqr1 = new Sqr(three);
    Mult* mul1 = new Mult(sqr1, one);
    Add* add1 = new Add(six, mul1);
    Root* root1= new Root(add1);
	
    //second tree
    Add* add2 = new Add(one, ten);
    Mult* mul2 = new Mult(seven, six);
    Sub* sub2 = new Sub(add2, mul2);
    Root* root2 = new Root(sub2);
    
    //thrid tree
    Sqr* sqr3 = new Sqr(three);
    Mult* mul3 = new Mult(sqr3, three);
    Root* root3 = new Root(mul3);
    
    //fourth tree
    Add* div4a = new Add(eight, two);
    Add* div4b = new Add(div4a, two);
    Root* root4 = new Root(div4b);
    
    //fifth tree
    Add* div5 = new Add(ten, two);
    Sqr* sqr5 = new Sqr(div5);
    Root* root5 = new Root(sqr5);
    
    //given tree
    Add* addg = new Add(three, eight);
    Sqr* sqrg = new Sqr(two);
    Sub* subg = new Sub(addg, sqrg);
    Root* rootg = new Root(subg);
    
    //iteration tests (same order as the trees were created)
    cout << "PreOrder Iteration 1: " << endl;
    PrintVisitor vis1(root1);
    vis1.execute();

    cout << "\nPreOrder Iteration 2: " << endl;
    PrintVisitor vis2(root2);
    vis2.execute();

    cout << "\nPreOrder Iteration 3: " << endl;
    PrintVisitor vis3(root3);
    vis3.execute();

    cout << "\nPreOrder Iteration 4: " << endl;
    PrintVisitor vis4(root4);
    vis4.execute();

    cout << "\nPreOrder Iteration 5: " << endl;
    PrintVisitor vis5(root5);
    vis5.execute();

    cout << "\n Given PreOrder Iteration: " << endl;
    PrintVisitor visg(rootg);
    visg.execute();

};
