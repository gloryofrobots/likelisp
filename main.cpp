#include <iostream>
#include <string>
#include <iomanip>  
#include "likelisp.h"

using namespace likelisp;

template < typename T >
Cons<T>* integers_from( int n )
{
    return make_cons<T>( n
                    , [ n ] ()
                    {
                        return integers_from<T>( n + 1 );
                    });   
}

template < typename T >
Cons<T> * fibonacci_from( int a, int b )
{
    return make_cons<T>( a
                    , [ a ,b ] ()
                      {
                       return fibonacci_from<T>( b, a + b );
                      } );  
}

int main()
{
    Cons<int> * integers = integers_from<int>(2);
    print_cons( integers, 10 );

    Cons<int> * evens = filter( integers, [] ( int _in ) { return ( ( _in % 2 ) == 0 ); } );
    print_cons( evens, 10 );
    
    Cons<int> * squares = map( evens, [] ( int _in ) { return _in * _in; }  );
    print_cons( squares, 10 );
    
    Cons<int> * primes = sieve( integers, [] ( int _first, int _second ) { return ( ( _first % _second ) != 0 ); } ); 
    print_cons( primes, 10 );
    
    Cons<int> * fibonacci = fibonacci_from<int>( 21, 34 );
    print_cons( fibonacci, 10 );
    

    destroy_cons(integers);
    destroy_cons(primes);
    destroy_cons(squares);
    destroy_cons(evens);
    destroy_cons(fibonacci);
    return 0;
}
