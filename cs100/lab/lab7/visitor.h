#ifndef visitor_h
#define visitor_h

#include "composite.h"
#include "iterator.h"

using namespace std;

class Base;
class Iterator;
class Op;
class PreOrderIterator;

class Visitor{
    protected:
	Iterator* my_it;
    
    public:
	Visitor(Base* root) {};
	virtual void rootNode() = 0; //For visiting a rootnode (donothing)
	virtual void sqrNode() = 0; //For visiting a square node
	virtual void multNode() = 0; //For visiting a multiple node
	virtual void subNode() = 0; //For visiting asubtraction node
	virtual void addNode() = 0; //For visiting an add node
	virtual void opNode(Op* op) = 0; //For visiting a leaf node
	virtual void execute() = 0; //Prints all visited node
};





class PrintVisitor:public Visitor{
    private:
	string output;
    
    public:
	PrintVisitor(Base* root);
	void rootNode(); //For visiting a rootnode (donothing)
	void sqrNode(); //For visiting a square node
	void multNode(); //For visiting a multiple node
	void subNode(); //For visiting asubtraction node
	void addNode(); //For visiting an add node
	void opNode(Op* op); //For visiting a leaf node
	void execute(); //Prints all visited node
};

#endif
