#include <iostream>
#include <string>
#include <iomanip>  
#include "likelisp.h"

using namespace likelisp;

template < typename T >
Pair<T>* integers_from( int n )
{
    return cons<T>( n
                    , [ n ] ()
                    {
                        return integers_from<T>( n + 1 );
                    });   
}

template < typename T >
Pair<T> * fibonacci_from( int a, int b )
{
    return cons<T>( a
                    , [ a ,b ] ()
                    {
                       return fibonacci_from<T>( b, a + b );
                    });  
}

int main()
{
    Pair<int> * integers = integers_from<int>(2);
    print_pair( integers, 10 );

    Pair<int> * evens = filter( integers, [] ( int _in ) { return ( ( _in % 2 ) == 0 ); } );
    print_pair( evens, 10 );
    
    Pair<int> * squares = map( evens, [] ( int _in ) { return _in * _in; }  );
    print_pair( squares, 10 );
    
    Pair<int> * primes = sieve( integers, [] ( int _first, int _second ) { return ( ( _first % _second ) != 0 ); } ); 
    print_pair( primes, 10 );
    
    Pair<int> * fibonacci = fibonacci_from<int>( 21, 34 );
    print_pair( fibonacci, 10 );
    

    destroy_pair(integers);
    destroy_pair(evens);
    destroy_pair(squares);
    destroy_pair(primes);
    destroy_pair(fibonacci);
    return 0;
}
