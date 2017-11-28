#ifndef sorth
#define sorth

using namespace std;

class Container;
class Base;

class Sort{
    public:
    int holdme;
    Sort(): holdme(0) {};

    virtual void sort(Container *container) = 0;
};

#endif
