#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include "sort.h"
#include "container.h"

using namespace std;

class Base{
    public:
    Base(){};
    
    virtual double evaluate()= 0;
};

//classes inherited from base
class op : public Base{
    double value;

    public:
    op(double v): value(v){}

    double evaluate(){
    return value;
        }
};

//only class with one op
class Sqr : public Base{
    Base *child;

    public:
    Sqr(Base *c) : child(c) {}

    double evaluate(){
        double dhold= child->evaluate();
        return dhold*dhold;
    }
};



//now for 2 op classes
class Add : public Base{
    Base *left;
    Base *right;
    
    public:
    Add(Base *l, Base *r) : left(l), right(r){}

    double evaluate(){
	double num1= left->evaluate();
	double num2= right->evaluate();
	return num1+num2;
    }
};

class Sub : public Base{
    Base *left;
    Base *right;
    
    public:
    Sub(Base *l, Base *r) : left(l), right(r){}

    double evaluate(){
	double num1= left->evaluate();
	double num2= right->evaluate();
	return num1-num2;
    }
};

class Mul : public Base{
    Base *left;
    Base *right;
    
    public:
    Mul(Base *l, Base *r) : left(l), right(r){}
	
    double evaluate(){
	double num1= left->evaluate();
	double num2= right->evaluate();
	return num1*num2;
    }
};

class Div : public Base{
    Base *left;
    Base *right;
    
    public:
    Div(Base *l, Base *r) : left(l), right(r){}	
	
    double evaluate(){
	double num1= left->evaluate();
        double num2= right->evaluate();
    
	if(num2 == 0){
	    cout << "Cannot divide by ZERO!" << endl;
	    exit(0);
	}

	 return num1/num2;
    }
};

//container-inherited classes
class List_Container : public Container{
    list<Base*> mylist;

    public:
    List_Container(Sort *sf){
	sort_function = sf;
    }
    
    void add_element(Base *element){
	mylist.push_back(element);
    }

    void print(){
	for (list<Base*>::iterator i = mylist.begin(); i != mylist.end(); i++)
	    cout << (*i)->evaluate() << " ";
    }

    void sort(){
	sort_function->sort(this);
    }

    void swap(int i, int j){
	list<Base*>::iterator it = mylist.begin();
	list<Base*>:: iterator ithold;
	Base *bhold;

	for(int count = 0; count <= j; count++){
	    if(count == i){
		ithold = it;
		bhold = *it;
	    }

	    if(count == j){
		*ithold = *it;
		*it = bhold;
	    }
	    it++;
	}
    }

    Base* at(int i){
	list<Base*>::iterator it = mylist.begin();
	for(int count = 0; count < i; count ++)
	    it++;

	return *it;
    }

    int size(){
	return mylist.size();
    }
};

class Vector_Container : public Container{
    vector<Base*> myvector;

    public:
    Vector_Container(Sort *sf){
	sort_function = sf;
    }

    void add_element(Base* element){
	myvector.push_back(element);
    }

    void print(){
	for(int i = 0; i < myvector.size(); i++){
	    cout << myvector[i]->evaluate() << " ";
	}
    }

    void sort(){
	sort_function->sort(this);
    }

    void swap(int i, int j){
	Base *bhold = myvector[i];
	myvector[i] = myvector[j];
	myvector[j] = bhold;
    }

    Base* at(int i){
	return myvector[i];
    }

    int size(){
	return myvector.size();
    }
};

//sort-inherited classes
class Bubble_Sort : public Sort{
    public:
    Bubble_Sort(){}
    
    void sort(Container *container){
	bool swapped = true;

	while (swapped){
	    swapped = false;

	    for (int i = 0; i < (container->size() - 1); i++){
		if (container->at(i)->evaluate() > container->at(i + 1)->evaluate()){
		    container->swap(i, i+1);
		    swapped = true;
		}
	    }
	}
    }
};

class Selection_Sort : public Sort{
    public:
    Selection_Sort(){
	//do nothing
    }

    void sort(Container *container){
	for (int i = 0; i < container->size(); i++){
	    int min = i;

	    for (int j = i; j < container->size(); j++){
		if(container->at(min)->evaluate() > container->at(j)->evaluate()){
		    min = j;
		}
	    }
	    container->swap(i, min);
	}
    }
};

int main(){
    //create nums
    op one(1);
    op two(2);
    op three(3);
    op six(6);
    op seven(7);
    op eight(8);
    op ten(10);

    //first tree (where the root is always the last made)
    Sqr sqr1(&three);
    Mul mul1(&sqr1, &one);
    Add add1(&six, &mul1);

    //second tree
    Add add2(&ten, &ten);
    Mul mul2(&seven, &six);
    Sub sub2(&add2, &mul2);

    //thrid tree
    Sqr sqr3(&three);
    Mul mul3(&sqr3, &three);

    //fourth tree
    Div div4a(&eight, &two);
    Div div4b(&div4a, &two);

    //fifth tree
    Div div5(&ten, &two);
    Sqr sqr5(&div5);
    
    //create sort classes
    Bubble_Sort mybubble;
    Selection_Sort myselection;

    //create containers
    List_Container lbubble(&mybubble);
    List_Container lselection(&myselection);

    Vector_Container vbubble(&mybubble);
    Vector_Container vselection(&myselection);
    
    //fill containers
    lbubble.add_element(&add1);
    vbubble.add_element(&add1);
    lselection.add_element(&add1);
    vselection.add_element(&add1);
    
    lbubble.add_element(&mul3);
    vbubble.add_element(&mul3);
    lselection.add_element(&mul3);
    vselection.add_element(&mul3);

    lbubble.add_element(&sub2);
    vbubble.add_element(&sub2);
    lselection.add_element(&sub2);
    vselection.add_element(&sub2);

    lbubble.add_element(&div4b);
    vbubble.add_element(&div4b);
    lselection.add_element(&div4b);
    vselection.add_element(&div4b);

    lbubble.add_element(&sqr5);
    vbubble.add_element(&sqr5);
    lselection.add_element(&sqr5);
    vselection.add_element(&sqr5);

    //display unsorted
    cout << "lbubble: ";
    lbubble.print();
    cout << endl;

    cout << "vbubble: ";
    vbubble.print();
    cout << endl;

    cout << "lselection: ";
    lselection.print();
    cout << endl;

    cout << "vselection: ";
    vselection.print();
    cout << endl << endl;

    //sort them
    cout << "Sorting..." << endl << endl;
    
    lbubble.sort();
    vbubble.sort();
    lselection.sort();
    vselection.sort();

    //display sorted
    cout << "lbubble: ";
    lbubble.print();
    cout << endl;

    cout << "vbubble: ";
    vbubble.print();
    cout << endl;

    cout << "lselection: ";
    lselection.print();
    cout << endl;

    cout << "vselection: ";
    vselection.print();
    cout << endl << endl;

    return 0;
}
