#include "chain.h"
#include <iostream>
using namespace std;

/**
 * A hash routine for string objects.
 */
size_t hash( const string & key )
{
    size_t hashVal = 0;

    for( char ch : key ){
        int highorder = hashVal & 0xf8000000;// do some stuff
        hashVal = hashVal << 5; //do some other stuff
        hashVal = hashVal ^ (highorder >> 27); // do some more stuff
        hashVal = hashVal ^ ch; // do the last stuff

    }

    return hashVal;
}

/**
 * A hash routine for ints.
 */
size_t hash( int key )
{
    return key;
}

