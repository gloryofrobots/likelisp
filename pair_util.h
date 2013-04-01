#ifndef LIKELISP_PAIR_UTIL_H
#define LIKELISP_PAIR_UTIL_H
#include "pair.h"
namespace likelisp
{
    /////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Pair<T> * map( Pair<T>* _pair, const boost::function<int (int)>& operation )
    {
        if( _pair == 0 )
        {
            return 0;
        }
        
        int val = operation ( car(_pair) );
        
        return cons<T>( val
                        , [ _pair ,operation ] () -> Pair<T>*
                        {
                            return map<T>( cdr( _pair ), operation );
                        });
    }
    /////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Pair<T> * filter( Pair<T>* _pair, const boost::function<bool (int)>& predicate )
    {
        if( _pair == 0 )
        {
            return 0;
        }
        
        if( predicate( car ( _pair ) ) == true )
        {
            return cons<T>( car(_pair)
                            , [ _pair ,predicate ] () -> Pair<T>* 
                            {
                                return filter<T>( cdr( _pair ), predicate );
                            });
        }
        
        return filter<T>( cdr(_pair), predicate );
    }
    /////////////////////////////////////////////////////////////////////////////
    template < typename T >
    void for_each( Pair<T> * _pair, const boost::function < void (int)>& operation, int _limit )
    {
        if ( _pair == 0 )
        {
            return;
        }
        
        if( _limit == 0 )
        {
            return;
        }
        
        operation( car( _pair ) );
        for_each<T>( cdr( _pair ), operation, _limit - 1 );
    }
    /////////////////////////////////////////////////////////////////////////////
    template < typename T >
    void print_pair( Pair<T> * _pair, int _limit )
    {
        
        for_each<T>( _pair
                , [] (int _val)
                {
                  std::cout << std::left << std::setw(2) << _val << " ";
                }
                , _limit );
             
        std::cout << std::endl;
    }
    /////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Pair<T> * sieve(Pair<T> * _pair, const boost::function<bool (int,int)>& _predicate )
    {
        if( _pair == 0 )
        {
            return 0;
        }
        
        return cons<T>( car(_pair)
                        , [ _pair, _predicate ] ()
                        {                          
                            int val = car( _pair );
                            
                            Pair<T> * filtered = filter<T>( cdr( _pair )
                                                    , [ val, _predicate ] ( int x )
                                                    {
                                                        return _predicate( x, val );
                                                    });
                            
                            return sieve<T>(filtered, _predicate);
                        });  
    }
    /////////////////////////////////////////////////////////////////////////////
}
#endif
