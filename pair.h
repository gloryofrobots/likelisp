#ifndef LIKELISP_PAIR_H
#define LIKELISP_PAIR_H
#include "interface.h"
namespace likelisp
{
    ////////////////////////////////////////////////////////////////////////////
    template< typename T >
    class Pair
    {
    private:
        Pair( T _val, const std::function< Pair<T>* (void)>& _generator )
        : value( _val )
        , next( 0 )
        , generator( _generator )
        {
        }
        
        Pair( T _val )
        : next( 0 )
        , value( _val )
        {
        }
        
        virtual ~Pair()
        {
         if( next != 0 ) delete next;
         //std::cout<< "~Cons" << car << std::endl;  
        }
        
        T value;
        std::function< Pair<T>* (void)> generator;
        Pair* next;
     
        
    friend Pair<T>* cons<>( T val, const std::function< Pair<T>* (void)>& op );
    friend Pair<T>* cons<>( T val, Pair<T>* next );
    friend T car<>( Pair<T>* _pair );
    friend Pair<T>* cdr<>( Pair<T>* _pair );
    friend bool has_next<>( Pair<T>* _pair );
    friend void destroy_pair<>( Pair<T>* _pair );
    };
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    bool has_next( Pair<T>* _pair )
    {
       if ( !_pair->generator )
       {
            return false;
       }
       
       return true;
    }
    ////////////////////////////////////////////////////////////////////////////
    template < class T >
    Pair<T>* cons( T val,const std::function< Pair<T>* (void)>& op )
    {
        return new Pair<T>(val, op);
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Pair<T>* cons( T val, Pair<T>* next )
    {
        if ( next == 0 )
        {
            return new Pair<T>(val);
        }

        
        return new Pair<T>(val
                        , [ next ] ()
                        {
                            return next;
                        });
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    void destroy_pair( Pair<T> * _pair )
    {
        delete _pair;
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    T car( Pair<T>* _pair )
    {
        return _pair->value;
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Pair<T>* cdr( Pair<T>* _pair )
    {
        if ( has_next<T>( _pair ) == false )
        {
            return 0;
        }
        
        if ( _pair->next != 0 )
        {
            return _pair->next;
        }
        
        _pair->next = _pair->generator();
        return _pair->next;
    }
}
#endif
