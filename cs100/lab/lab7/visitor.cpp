#include <cstdio>
#include "visitor.h"

PrintVisitor::PrintVisitor(Base* root):Visitor(root){
    my_it = new PreOrderIterator(root);
}

void PrintVisitor::rootNode(){
}

void PrintVisitor::sqrNode(){
    output.append(" ^2");
}

void PrintVisitor::multNode(){
    output.append(" *");
}

void PrintVisitor::subNode(){
    output.append(" -");
}

void PrintVisitor::addNode(){
    output.append(" +");
}

void PrintVisitor::opNode(Op* op){
    int data = (int)op->evaluate();
    char buff[50];

    sprintf(buff, " %d", data);
    output.append((const char*)(&buff));
}

void PrintVisitor::execute(){
    for(my_it->first(); !(my_it->is_done()); my_it->next())
	my_it->current()->accept(this);

    cout << output << endl;
}
