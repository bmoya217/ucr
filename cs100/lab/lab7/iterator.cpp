#include "iterator.h"
#include "composite.h"

OperatorIterator::OperatorIterator(Base* ptr):Iterator(ptr){
    this->self_ptr=ptr;
}

void OperatorIterator::first(){
    current_ptr = self_ptr->get_left();  
}

void OperatorIterator::next(){
    if(current_ptr == self_ptr->get_left())
	current_ptr = self_ptr->get_right();
    
    else
	current_ptr = NULL;
}

bool OperatorIterator::is_done(){
    if(current_ptr == NULL)
	return true;
    return false;
}

Base* OperatorIterator::current(){
    return current_ptr;
}

UnaryIterator::UnaryIterator(Base* ptr):Iterator(ptr){
    this->self_ptr=ptr;
}

void UnaryIterator::first(){
    current_ptr = self_ptr->get_left();
}

void UnaryIterator::next(){
    current_ptr = NULL;
}

bool UnaryIterator::is_done(){
    if(current_ptr == NULL)
	return true;
    return false;
}

Base* UnaryIterator::current(){
    return current_ptr;
}

NullIterator::NullIterator(Base* ptr):Iterator(ptr){
    this->self_ptr=ptr;
}


void NullIterator::first(){
    //empty class
}

void NullIterator::next(){
    //empty class
}

bool NullIterator::is_done(){
    return true;
}

Base* NullIterator::current(){
    return NULL;
}

PreOrderIterator::PreOrderIterator(Base* ptr):Iterator(ptr){
    this->self_ptr=ptr;
}

void PreOrderIterator::first(){
    while(iterators.size() > 0)
	iterators.pop();

    Iterator* it = self_ptr->create_iterator();
    it->first();
    iterators.push(it);
}

void PreOrderIterator::next(){
    Iterator *it = iterators.top()->current()->create_iterator();
    it->first();
    iterators.push(it);

    while(iterators.top()->is_done()){
	iterators.pop();
	if(iterators.size() == 0)
	    break;
	
	iterators.top()->next();
    }
}

bool PreOrderIterator::is_done(){
    if(iterators.size() == 0)
	return true;
    return false;
}

Base* PreOrderIterator::current(){
    return iterators.top()->current();
}
