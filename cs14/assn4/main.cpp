#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>

using namespace std;

class Fraction{
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
    public:
        Fraction(int num, int dem = 1){
            n= num/gcd(num,dem);
            d= dem/gcd(num,dem);
            if(d < 0){
                n*=-1;
                d*=-1;
            }
        }
        int num() const { return n; }
        int den() const { return d; }
        Fraction& operator*=(const Fraction& rhs){
            int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
            d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
            n = new_n;
            return *this;
        }
};
ostream& operator<<(std::ostream& out, const Fraction& f){
    return out << f.num() << ' ' << f.den();
} //fix before turing in
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return ((lhs.num() * rhs.den()) == (rhs.num() * lhs.den()));
}
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() < rhs.num() * lhs.den());
}
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() > rhs.num() * lhs.den());
}
Fraction operator*(Fraction lhs, const Fraction& rhs){
    return lhs *= rhs;
}

template <typename type>
struct node{
    type *data;
    node<type> *left;
    node<type> *right;
};

template <typename type>
struct tree{ 
    node<type> *root;
    
    tree(){
        root = NULL;
    }
    ~tree(){
        clear();
    }
    void clear(){
        clear_tree(root);
        root = NULL;
    }
    void clear_tree(node<type> *leaf){
        if(leaf != NULL){
            clear_tree(leaf->left);
            delete leaf;
            clear_tree(leaf->right);
        }
    }
    
    void insert(type &data_ptr){
        if(root == NULL){
            root= new node<type>;
            root->data= &data_ptr;
            root->left= NULL;
            root->right= NULL;
        }
        else
            insert_leaf(data_ptr, root);
    }
    void insert_leaf(type &data_ptr, node<type> *leaf){
        bool goleft = false;
        bool goright = false;
        
        if(data_ptr == *(leaf->data)){
            if(leaf->left == NULL && leaf->right != NULL)
                goleft= true;
            else if(leaf->left != NULL && leaf->right == NULL)
                goright= true;
            else if(rand() < RAND_MAX/2)
                goleft= true;
            else
                goright= true;
        }
        
        if(data_ptr < *(leaf->data) || goleft){
            if(leaf->left == NULL){
                leaf->left= new node<type>;
                leaf->left->data= &data_ptr;
                leaf->left->left= NULL;
                leaf->left->right= NULL;
            } 
            else
                insert_leaf(data_ptr, leaf->left);
        }
        
        else if(data_ptr > *(leaf->data) || goright){
            if(leaf->right == NULL){
                leaf->right= new node<type>;
                leaf->right->data= &data_ptr;
                leaf->right->left=NULL;
                leaf->right->right=NULL;
            }
            
            else
                insert_leaf(data_ptr, leaf->right);
        }
    }
    
    void display(ofstream &ofile){
        if(root != NULL)
            display_tree(ofile, root);
    }
    void display_tree(ofstream &ofile, node<type> *leaf){
        if(leaf != NULL){
            display_tree(ofile, leaf->left);
            ofile << *(leaf->data) << " ";
            display_tree(ofile, leaf->right);
        }
    }
    
    void list_sort(list<type> &myList){
        if(root != NULL){
            int size = myList.size();
            typename list<type>::iterator i= myList.begin();
            list_sorter(myList, i, root);
            for(int  j= myList.size(); j > size; --j)
                myList.pop_back();
        }
    }
    void list_sorter(list<type> &myList,typename list<type>::iterator &i, node<type> *leaf){
        if(leaf->left != NULL)
            list_sorter(myList, i, leaf->left);
        
        if(!(*i == *(leaf->data))){
            myList.insert(i, *(leaf->data));
            --i;
            leaf->data= &(*i);
        }
        
        ++i;
        
        if(leaf->right != NULL)
            list_sorter(myList, i, leaf->right);
    }
};

//driver main
int main(int argc, char *argv[]){
    //declares variables
    string shold, shold2; int ihold, ihold2; //string & int holders
    list<int> iList; list<Fraction> fList; //int & fraction lists
    tree<int> iTree; tree<Fraction> fTree; //int & fraction trees
    
    //sets up iofile streams{
    istringstream ofnames(argv[1]);
    ofnames >> shold;
    ifstream ifile(shold.c_str()); 
    
    ihold = shold.find(".");
    if(ihold != -1)
        shold= shold.substr(0,ihold);
    shold+= ".out";
    ofstream ofile(shold.c_str());
    
    if(!(ifile.is_open() || ofile.is_open())){
        cout << "Could not open input and/or output file(s)..\n";
        return -1;
    }
    
    //run test cases
    while(getline(ifile, shold)){
        istringstream in(shold);
        in >> shold;
        getline(ifile, shold2);
        istringstream in2(shold2);
        
        if(shold == "i" || shold == "I"){
            while(in2 >> ihold)
                iList.push_back(ihold);
            
            //outputs the list to make sure they were taken correctly
         	for(list<int>::iterator i= iList.begin(); i != iList.end(); ++i)
                iTree.insert(*(&(*i)));
            
            iTree.list_sort(iList);
            
            ofile << "i\n";
            for(list<int>::iterator i= iList.begin(); i != iList.end(); ++i)
                ofile << *i << " ";
            ofile << endl;
            
            iTree.clear();
            iList.clear();
        }
        
        else if(shold == "f" || shold == "F"){
            while(in2 >> ihold){
                in2 >> ihold2;
                Fraction fhold(ihold,ihold2);
                fList.push_back(fhold);
            }
            
            for(list<Fraction>::iterator i= fList.begin(); i != fList.end(); i++)
                fTree.insert(*(&(*i)));
            
            fTree.list_sort(fList);
            
            //outputs list to file
            ofile << "f\n";
            for(list<Fraction>::iterator i= fList.begin(); i != fList.end(); i++)
                ofile << *i << " ";
            ofile << endl;
            
            fTree.clear();
            fList.clear();
        }
        
        else{
            cout << "Input file formatted incorectly!\n";
            return -1;
        }
    }
    
    //closes used files
    ifile.close();
    ofile.close();
    
    return 0;
}
