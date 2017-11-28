#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>

using namespace std;

int postfixSolver(string eq){
   list<int> stack;
   istringstream in(eq.c_str());
   char hold;
   
   while(in >> hold){
        if(hold <= '9' && hold >= '0')
            stack.push_back(hold-'0');
        
        else if((hold=='+'||hold=='-'||hold=='/'||hold=='*')&&(stack.size()>1)){
            int op1= stack.back();
            stack.pop_back();
            int op2= stack.back();
            stack.pop_back();
            
            if(hold=='+')
                stack.push_back(op1+op2);
            if(hold=='-')
                stack.push_back(op1-op2);
            if(hold=='/')
                stack.push_back(op1/op2);
            if(hold=='*')
                stack.push_back(op1*op2);
        }
   }
   return stack.back();
    
    
}

int main(){
    string eq;//= "1 2 3 * 4 5 6 * + + +";
    cout << "Enter an equation in postfix notation: ";
    getline(cin, eq);
    cout << postfixSolver(eq) << endl;
    
    
    return 0;
}