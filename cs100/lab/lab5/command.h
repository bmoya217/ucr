#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "composite.h"

class Command {
	protected:
		Base* root;
	
	public:
		Command() { };
		double execute() {
			return root->evaluate();
		}
		Base* get_root() {
			return root;
		}
};

class OpCommand : public Command {
	//OpCommand Code Here
    public:
	OpCommand(int data){
	    root = new Op(data);
	}
};

class AddCommand : public Command {
	//AddCommand Code Here
    public:
	AddCommand(Command *cmd, int right){
	    root = new Add(cmd->get_root(), new Op(right));
	}
};

class SubCommand : public Command {
	//SubCommand Code Here
    public:
	SubCommand(Command *cmd, int right){
	    root = new Sub(cmd->get_root(), new Op(right));
	}
};

class MultCommand : public Command {
	//MultCommand Code Here
    public:
	MultCommand(Command *cmd, int right){
	    root = new Mult(cmd->get_root(), new Op(right));
	}
};

class SqrCommand : public Command {
	//SqrCommand Code Here
    public:
	SqrCommand(Command *cmd){
	    root = new Sqr(cmd->get_root());
	}
};

#endif //__COMMAND_CLASS__
