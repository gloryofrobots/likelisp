#ifndef LIKELISP_INTERFACE_H
#define LIKELISP_INTERFACE_H
//#include <boost/function.hpp>
#include <functional>

namespace likelisp
{
    template< typename T > class Pair;
    
    ///////////////////////////////////////////////////////////////
    template< typename T > Pair<T>* cons( T val, const std::function< Pair<T>* (void)>&  op );
    template< typename T > Pair<T>* cons( T val, Pair<T>* next );
    template< typename T > T car( Pair<T>* _pair );
    template< typename T > Pair<T>* cdr( Pair<T>* _pair );
    template< typename T > bool has_next( Pair<T>* _pair );
    template< typename T > void destroy_pair( Pair<T>* _pair );
    ///////////////////////////////////////////////////////////////
    template < typename T > Pair<T> * map( Pair<T>* _pair, const std::function<int (int)>& operation );
    template < typename T > Pair<T> * filter( Pair<T>* _pair, const std::function<bool (int)>& predicate );
    template < typename T > void for_each( Pair<T> * _pair, const std::function <void (int)>& operation, int _limit );
    template < typename T > Pair<T> * sieve( Pair<T> * _pair, std::function<bool (int,int)>& _predicate );
    template < typename T > void print_pair( Pair<T> * _pair, int _limit );
    ///////////////////////////////////////////////////////////////
}

#endif
