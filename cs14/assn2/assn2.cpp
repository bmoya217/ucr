#include <vector>
#include <iostream>

using namespace std;

class whopper{
    
    public:
        vector<short int> v;
        
        whopper(){
            v.push_back(0);
        }
        
        //comparison opperators
        bool operator>(const whopper &right) const;
        bool operator==(const whopper &right) const;
        
        //arithmetic operators and their helper functions
        int abscomp(const whopper &left, const whopper &right);
        whopper add(const whopper &bigwhop, const whopper &lilwhop, int sign);
        whopper minus(const whopper &bigwhop, const whopper &lilwhop, int sign);
        whopper operator+(whopper right);
        whopper operator-(whopper right);
        whopper operator*(whopper right);
        whopper operator*(int n);
        
        //input and output
        friend ostream& operator<<(ostream& os, const whopper &right);
        friend istream& operator>>(istream &is, whopper &right);
        
        //test harnesses
        void test();
};

//comparison opperators

bool whopper::operator>(const whopper &right) const{
    int sign=1; //the sign of "this" and "right" assumed to be 1
    if(this->v[0] > right.v[0]){ //"this" is bigger than "right" by sign
        return true;
    }
    else if(this->v[0] < right.v[0]){ //"this" is smaller than "right" by sign
        return false;
    }
    else if(this->v[0]==0){ //"this" and "right" are both zero
        return false;
    }
    else if(this->v[0]==-1){ 
        sign =-1;   //the sign of "this" and "right" affirmed to be -1 
    }
    
    if(this->v.size()>right.v.size() && sign==1){
        return true;
    }
    else if(this->v.size()>right.v.size() && sign==-1){
        return false;
    }
    else if(this->v.size()<right.v.size() && sign==1){
        return false;
    }
    else if(this->v.size()<right.v.size() && sign==-1){
        return true;
    }
    
    for(int i = this->v.size()-1; i > 0; i--){
        if(this->v[i]>right.v[i] && sign==1){ //ie. 45 > 13
            return true;
        }
        else if(this->v[i]>right.v[i] && sign==-1){ //ie. -25 > -13
            return false;
        }
        else if(this->v[i]<right.v[i] && sign==1){ //ie. 4 < 5
            return false;
        }
        else if(this->v[i]<right.v[i] && sign==-1){ //ie. -3 < -6
            return true;
        }
    }
    return false; //they are equal
}

bool whopper::operator==(const whopper &right) const{
    if(this->v.size()!=right.v.size()){
        return false;
    }
    for(int i=0; i < this->v.size(); i++){
        if(this->v[i] != right.v[i]){
            return false;
        }
    }
    return true;
}

//arithmetic helpers 

//checks if abs(left) is (1:greater, 0: same, -1: less than) abs(right)
int whopper::abscomp(const whopper &left, const whopper &right){
    if(left.v.size()>right.v.size()){
        return 1;
    }
    else if(left.v.size()<right.v.size()){
        return -1;
    }
    
    for(int i=left.v.size()-1; i>0; i--){
        if(left.v[i]>right.v[i]){
            return 1;
        }
        else if(left.v[i]<right.v[i]){
            return -1;
        }
    }
    return 0; // they have the same absolute value
}

whopper whopper::add(const whopper &bigwhop, const whopper &lilwhop, int sign){
    whopper sum;
    sum.v[0]=sign;
    for(int i = 1; i < lilwhop.v.size(); i++){
        sum.v.push_back(lilwhop.v[i]+bigwhop.v[i]);
    }
    
    for(int i = lilwhop.v.size(); i < bigwhop.v.size();i++){
        sum.v.push_back(bigwhop.v[i]);
    }
    
    for(int i = 1; i < sum.v.size()-1;i++){
        if(sum.v[i]>=100){
            sum.v[i]-=100;
            sum.v[i+1]++;
        }
    }
    if(sum.v[sum.v.size()-1]>=100){
        sum.v[sum.v.size()-1]-=100;
        sum.v.push_back(1);
    }
    
    return sum;
}

whopper whopper::minus(const whopper &bigwhop,const whopper &lilwhop,int sign){
    whopper difference;
    difference.v[0]=sign;
    
    for(int i = 1; i < lilwhop.v.size(); i++){
        difference.v.push_back(bigwhop.v[i]-lilwhop.v[i]);
    }
    
    for(int i = lilwhop.v.size(); i < bigwhop.v.size();i++){
        difference.v.push_back(bigwhop.v[i]);
    }
    
    for(int i = 1; i < difference.v.size();i++){
        if(difference.v[i]<0){
            difference.v[i]+=100;
            difference.v[i+1]--;
        }
    }
    while(difference.v[difference.v.size()-1]==0){
        difference.v.pop_back();
    }
    
    return difference;
}

//arithmetic operators

//fixme: could optimize by not changing signs so could pass "right" by reference
whopper whopper::operator+(whopper right){
    int sign= 1;
    
    if(this->v[0]==0){
        return right;
    }
    else if(right.v[0]==0){
        return *this;
    }
    else if(this->v[0]==-1 && right.v[0]==-1){
        sign= -1;
    }
    else if(this->v[0]==1 && right.v[0]==-1){
        right.v[0]= 1;
        return (*this-right); 
    }
    else if(this->v[0]==-1 && right.v[0]==1){
        this->v[0]= 1;
        return (right-*this); 
    }
    
    if(this->v.size()>right.v.size()){
        return add(*this, right, sign);
    }
    else{
        return add(right, *this, sign);
    }
}

whopper whopper::operator-(whopper right){
    int acomp = abscomp(*this, right);
    right.v[0]*=-1;
    whopper difference;
    
    if(this->v[0]==0){
        return right;
    }
    else if(right.v[0]==0){
        return *this;
    }
    else if(this->v[0]==-1 && right.v[0]==1){
        if(acomp==-1){
            return minus(right, *this, 1);
        }
        else if(acomp==1){
            return minus(*this, right, -1);
        }
    }
    else if((this->v[0]==-1&& right.v[0]==-1)||(this->v[0]==1&& right.v[0]==1)){
        return (*this+right);
    }
    
    if(acomp==0){
        return difference;
    }
    else if(acomp==-1){
        return minus(right, *this, -1);
    }
    else{
        return minus(*this, right, 1);
    }
}

whopper whopper::operator*(whopper right) {
    int carry= 0;
    int temp;
    whopper product;
    product.v[0]= this->v[0]*right.v[0];
    if(product.v[0]==0){
        return product;
    }
    if(this->v.size()<right.v.size()){
        return (right*(*this));
    }
    //fixme
    for(int i = 1; i < right.v.size(); i++){
        for(int j = 1; j < this->v.size(); j++){
            while(product.v.size()< i+j){
                product.v.push_back(0);
            }
            temp = product.v[j+i-1] + (right.v[i]*this->v[j]) + carry;
            product.v[i+j-1]= temp%100;
            carry= temp/100;
        }
        if(carry!=0){
            product.v[i+this->v.size()]+=carry;
            carry= 0;
        }
    }
    while(product.v[product.v.size()-1]==0){
        product.v.pop_back();
    }
    
    return product;
}

//input and output
ostream& operator<<(ostream &os, const whopper &right){
    os << right.v[0];
    if(right.v[0]==0){
        return os;
    }
    os << " ";
    
    for(int i = right.v.size()-1; i>0; i--){
        if(right.v[i]<10 && i!= right.v.size()-1){
            os << "0";
        }
        os << right.v[i];
        if(i!=1){
            os << " ";
        }
    }
    
    return os;
}

istream& operator>>(istream &is, whopper &right){
    while(right.v.size()>0){
        right.v.pop_back();
    }
    
    string s;
    is >> s;
    if(s== "exit"){
        return is;
    }
    right.v.push_back(0);
    
    int tmp=static_cast<char>(s[0])-'0';
    if(tmp==1||tmp==0){
        right.v[0]= static_cast<char>(s[0])-'0';
    }
    else{
        right.v[0]= -1;
        s= s.substr(1);
    }
    while(s.substr(1,1)=="0"){
        s= s.substr(0,1)+s.substr(2);
    }
    
    int mod2 = s.size()%2;
    for(int i = s.size()-1; i >= 2; i-=2){
        tmp= ((static_cast<char>(s[i])-'0')+10*(static_cast<char>(s[i-1])-'0'));
        right.v.push_back(tmp);
    }
    if(!mod2){
        right.v.push_back(static_cast<char>(s[1])-'0');
    }
    
    return is;
}

int main(){
    whopper operand1;
    whopper operand2;
    char operation = '+';
    
    while(true){
        cin >> operand1;
        if(operand1.v.size()==0){
            return 0;
        }
        cin >> operation;
        if(!(operation=='+'||operation == '-'||operation == '*')){
            return 0;
        }
        cin >> operand2;
        if(operand2.v.size()==0){
            return 0;
        }
        
        if(operation == '+'){
            cout << operand1+operand2;
        }
        if(operation == '-'){
            cout << operand1-operand2;
        }
        if(operation == '*'){
            cout << operand1*operand2;
        }
        cout << endl << endl;
    }
    
    return 0;
}
