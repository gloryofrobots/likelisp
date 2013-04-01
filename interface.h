#ifndef LIKELISP_INTERFACE_H
#define LIKELISP_INTERFACE_H
#include <boost/function.hpp>

namespace likelisp
{
    template< typename T > class Cons;
    
    ///////////////////////////////////////////////////////////////
    template< typename T > Cons<T>* make_cons( T val, const boost::function< Cons<T>* (void)>&  op );
    template< typename T > Cons<T>* make_cons( T val, Cons<T>* next );
    template< typename T > T car( Cons<T>* _pair );
    template< typename T > Cons<T>* cdr( Cons<T>* _pair );
    template< typename T > bool has_next( Cons<T>* _pair );
    template< typename T > void destroy_cons( Cons<T>* _pair );
    ///////////////////////////////////////////////////////////////
    template < typename T > Cons<T> * map( Cons<T>* _pair, const boost::function<int (int)>& operation );
    template < typename T > Cons<T> * filter( Cons<T>* _pair, const boost::function<bool (int)>& predicate );
    template < typename T > void for_each( Cons<T> * _pair, const boost::function < void (int)>& operation, int _limit );
    template < typename T > Cons<T> * sieve( Cons<T> * _pair, boost::function<bool (int,int)>& _predicate );
    template < typename T > void print_cons( Cons<T> * _pair, int _limit );
    ///////////////////////////////////////////////////////////////
}

#endif
