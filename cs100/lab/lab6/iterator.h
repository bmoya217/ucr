#ifndef iterator_h
#define iterator_h
#include <stack>
#include "composite.h"
using namespace std;

class Base;

class Iterator{
    protected:
	Base* self_ptr;
	Base* current_ptr;
    public:
	Iterator(Base* ptr){ this->self_ptr = ptr; }
	/*Sets up the iterator to start at the beginning of traversal*/
	virtual void first()=0;
	/*Move on to the next element*/
	virtual void next()=0;
	/*Returns if you have finished iterating through all elements*/
	virtual bool is_done()=0;
	/*Return the element the iterator is currently at*/
	virtual Base* current()=0;
};

class OperatorIterator : public Iterator{
    public:
    OperatorIterator(Base* ptr);
    void first(); 
    void next();
    bool is_done();
    Base* current();
};

class UnaryIterator : public Iterator{
    public:
    UnaryIterator(Base* ptr);
    void first();
    void next();
    bool is_done();
    Base* current();
};

class NullIterator : public Iterator{
    public:
    NullIterator(Base* ptr);
    void first();
    void next();
    bool is_done();
    Base* current();
};

class PreOrderIterator : public Iterator{
    protected:
    stack<Iterator*> iterators;
    
    public:
    PreOrderIterator(Base* ptr);
    void first();
    void next();
    bool is_done();
    Base* current();
};

#endif
