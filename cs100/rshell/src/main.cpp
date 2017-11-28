#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

using namespace std;

//simple Base class
class Base{
    public:
    int status;

    Base() {};
    virtual ~Base() {};

    virtual bool execute() = 0;
};


class Test_cmd : public Base{
    public:
    char* path;
    char option;

    void format(char *line){
	//extract path and option from line
	vector<char*> chold;
	chold.push_back(strtok(line, " "));
	while (chold[chold.size()-1] != NULL)
	    chold.push_back(strtok(NULL, " "));
	chold.pop_back();

	if(chold[0][0] == '['){
	    if(chold.size()==3)
		path = chold[1];
	    else{
		path = chold[2];
		option = chold[1][1];
	    }
	}

	else{
	    if(chold.size()==2)
		path = chold[1];
	    else{
		path = chold[2];
		option = chold[1][1];
	    }
	}
    }

    Test_cmd(char *line, int s){
	status = s;
	option = 'e';
	format(line);
    }

    bool execute(){
	//execute the test print (true) if true, (false) if false
	bool rvalue = false;

	struct stat info;   
	stat(path, &info);

	if(option == 'f' && S_ISREG(info.st_mode))
	    rvalue = true;

	else if(option == 'd' && S_ISDIR(info.st_mode))
	    rvalue = true;

	else if(option == 'e' && (S_ISREG(info.st_mode) || S_ISDIR(info.st_mode)))
	    rvalue = true;

	if(rvalue){
	    cout << "(True)\n";
	    return true;
	}

	cout << "(False)\n";
    
	return false;
    }
};

//classes that inherit Base
class Commands : public Base{
    public:
    char *cmd[256];

    Commands(char *line, int s){
	status = s;
	int i = 0;
	
	//splits up text even further into a format usable by execvp
	char *chold = strtok(line, " ");
	while (chold != NULL){
	    cmd[i] = chold;
	    chold = strtok(NULL, " ");
	    i++;
	}
	cmd[i] = '\0';
    }

    bool execute(){
	//exit called
	if (strcmp(*cmd, "exit") == 0)
	    exit(0);

	pid_t pid = fork();
	int ihold;
	
	//if forking failed
	if (pid == -1){
	    perror("Forking Failure");
	    exit(EXIT_FAILURE);
	}
	
	//if child
	else if (pid == 0){
	    if (execvp(*cmd, cmd) < 0){
		perror("Execvp Failure");
		exit(EXIT_FAILURE);
	    }
	}
	
	//if parent
	else
	   pid = wait(&ihold);
	
	//if the cmd worked (ie. execvp executed properly)
	if (ihold == 0)
	    return true;

	//if cmd failed (eg. <mkdir test> when the directory, test, already exists)
	return false;
    }
};

class Command_Line : public Base{
    public:
    vector<Base*> line;
    
    void get_vinfo(vector<int> &vstatus, vector<int> &vpos, char *chold){
	//breaks text into segments by setting ;/&&/|| into '\0' chars and saving status/pos info
	int quoted = 1; //1 for non quotes -1 for quotes
	int i;
	int paras = 0;
	bool semilast = false;

	for (i = 0; chold[i] != '\0'; i++){
	    if (chold[i] == '\"')
		quoted *= -1;
	    
	    if(chold[i] == '('){
		paras++;
		if(paras == 1){
		    vstatus[vstatus.size()-1]+=3;
		    vpos[vpos.size()-1]=i+1;
		    chold[i] = '\0';
		}

	    }
	    else if(chold[i] == ')'){
		paras--;
		if (paras == 0)
		    chold[i] = '\0';
	    }

	    if (quoted == 1 && paras == 0){
		if (chold[i] == ';'){
		    vstatus.push_back(0);
		    vpos.push_back(i+1);
		    chold[i] = '\0';
		    semilast = true;
		}

	        else if (chold[i] == '&' && chold[i+1] == '&'){
		    vstatus.push_back(1);
		    vpos.push_back(i+2);
		    chold[i] = '\0';
		    semilast = false;
		}	

		else if (chold[i] == '|' && chold[i+1] == '|'){
		    vstatus.push_back(2);
		    vpos.push_back(i+2);
		    chold[i] = '\0';
		    semilast = false;
		}
		
		else
		    semilast = false;
	    }
	}

	if (semilast){
	    vstatus.pop_back();
	    vpos.pop_back();
	}
    }
    
    bool is_test(char *line){
	//return true for:
	//  test -e src/main.cpp
	//  [ Makefile ]
	char tmp[256];
	strcpy(tmp, line);
	char *chold = strtok(tmp, " ");
	string first = chold;
	string last;
	while (chold != NULL){
	    last = chold;
	    chold = strtok(NULL, " ");
	}
	
    if(first == "test" || (first == "[" && last == "]"))
	return true;
    
    //false otherwise
    return false;
}

Command_Line(char *input, int s = 3){
    status = s;

    //cmds status'/position vectors (also count of how many cmds)
    vector<int> vstatus;
    vector<int> vpos;
    vstatus.push_back(0);
    vpos.push_back(0);

    get_vinfo(vstatus, vpos, input);
    
    //creates vector of commands to execute for the line
    for (unsigned int i = 0; i < vstatus.size(); i++){
	if (vstatus[i] > 2)
	    line.push_back(new Command_Line(input + vpos[i], vstatus[i]));
	else if (is_test(input + vpos[i]))
	    line.push_back(new Test_cmd(input + vpos[i], vstatus[i])); 
	else
	    line.push_back(new Commands(input + vpos[i], vstatus[i]));
    }
}

~Command_Line(){
    while (line.size() > 0){
	    delete line[line.size() - 1];
	    line.pop_back();
	}
    }
    
    bool execute(){
	bool last_cmd_passed;
	
	//execute vector of commands one by one
	for (unsigned int i = 0; i < line.size(); i++){
	    //if the first command or first after a semicolon
	    if (line[i]->status == 0 || line[i]->status == 3)
		last_cmd_passed= line[i]->execute();
	    
	    //if after &&
	    else if (line[i]->status == 1 || line[i]->status == 4){
		if (last_cmd_passed)
		    last_cmd_passed= line[i]->execute();
		else
		    last_cmd_passed= false;
	    }
	    
	    //if after ||
	    else if (line[i]->status == 2 || line[i]->status == 5){
		if (!last_cmd_passed)
		    last_cmd_passed= line[i]->execute();
	    }
	}
	return last_cmd_passed;
    }
};

//removes comments from input string
void rm_comments(char *input){
    for (int i = 0; input[i] != '\0'; i++)
	if (input[i] == '#')
	    input[i] = '\0';
}

int main(){
    char *name = getlogin();
    char host[256];
    gethostname(host, 250);
    string prompt = "$ ";

    if (name != NULL && host != NULL){
	string sname = name;
	string shost = host;
	prompt = sname + "@" + shost + "$ ";
   }

    while (true){
	//output propt (include username/location for extra credit)
	cout << prompt;

	//get arguement(s)
    	char input[1024];
	cin.getline(input, 1000, '\n');

	//remove comments
	rm_comments(input);
	
	//check for empty commands
	if (input[0] == '\0')
	    continue;

	//use input to construct a Command_Line
    	Command_Line cmd_ln(input);
	
	//execute commands
	cmd_ln.execute();
    }
 
    return 0;
}
