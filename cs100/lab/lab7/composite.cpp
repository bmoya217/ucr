#include "composite.h"
#include "visitor.h"
#include "iterator.h"

class Visitor;
class PrintVisitor;
//--------------------------------------------------------------------------
// Op Class
//--------------------------------------------------------------------------
Op::Op() : Base(), value(0){};
Op::Op(double val) : Base(), value(val){};

Base* Op::get_left() { return NULL; }
Base* Op::get_right() { return NULL; }
void Op::print() { cout << this->value; }
double Op::evaluate() { return this->value; };
Iterator* Op::create_iterator() { return new NullIterator(this); }
void Op::accept(Visitor* my_vis){ my_vis->opNode(this); }

//--------------------------------------------------------------------------
// Operator Base Class
//--------------------------------------------------------------------------
Operator::Operator() : Base(){ };
Operator::Operator(Base* l, Base* r) : left(l), right(r){  };

Base* Operator::get_left() { return left; };
Base* Operator::get_right() { return right; };
Iterator* Operator::create_iterator() { return new OperatorIterator(this); }
void Operator::accept(Visitor* my_vis){}

//--------------------------------------------------------------------------
// Unary Base Class
//--------------------------------------------------------------------------
UnaryOperator::UnaryOperator() : Base(){};
UnaryOperator::UnaryOperator(Base* c) : child(c) { };

Base* UnaryOperator::get_left() { return child; }
Base* UnaryOperator::get_right() { return NULL; }
Iterator* UnaryOperator::create_iterator() { return new UnaryIterator(this); }
void UnaryOperator::accept(Visitor* my_vis){}

//--------------------------------------------------------------------------
// Add Class
//--------------------------------------------------------------------------
Add::Add() : Operator() { };
Add::Add(Base* left, Base* right) : Operator(left,right) { };

void Add::print() { cout << "+"; }
double Add::evaluate() { return this->left->evaluate() + this->right->evaluate(); };
void Add::accept(Visitor* my_vis) { my_vis->addNode(); }

//--------------------------------------------------------------------------
// Sub Class
//--------------------------------------------------------------------------
Sub::Sub() : Operator() { };
Sub::Sub(Base* left, Base* right) : Operator(left,right) { };

void Sub::print() { cout << "-"; }
double Sub::evaluate() { return this->left->evaluate() - this->right->evaluate(); };
void Sub::accept(Visitor* my_vis) { my_vis->subNode(); }

//--------------------------------------------------------------------------
// Mult Class
//--------------------------------------------------------------------------
Mult::Mult() : Operator() { };
Mult::Mult(Base* left, Base* right) : Operator(left,right) { };

void Mult::print() { cout << "*"; }
double Mult::evaluate() { return this->left->evaluate() * this->right->evaluate(); };
void Mult::accept(Visitor* my_vis) { my_vis->multNode(); }

//--------------------------------------------------------------------------
// Sqr Class
//--------------------------------------------------------------------------
Sqr::Sqr() : UnaryOperator() { };
Sqr::Sqr(Base* child) : UnaryOperator(child) { };

void Sqr::print() { cout << "^2"; }
double Sqr::evaluate() { return pow(this->child->evaluate(),2); };
void Sqr::accept(Visitor* my_vis) { my_vis->sqrNode(); }

//--------------------------------------------------------------------------
// Root Class
//--------------------------------------------------------------------------
Root::Root() : UnaryOperator() { };
Root::Root(Base* child) : UnaryOperator(child) { };

void Root::print() { cout << "ROOT"; }
double Root::evaluate() { return this->child->evaluate(); };
void Root::accept(Visitor* my_vis){}
