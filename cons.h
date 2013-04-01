#ifndef LIKELISP_CONS_H
#define LIKELISP_CONS_H
#include <boost/function.hpp>
#include "interface.h"
namespace likelisp
{
   
    ////////////////////////////////////////////////////////////////////////////
    template< typename T >
    class Cons
    {
    private:
        Cons( T _val, const boost::function< Cons<T>* (void)>& _generator )
        : value( _val )
        , next( 0 )
        , generator( _generator )
        {
        }
        
        Cons( T _val )
        : next( 0 )
        , value( _val )
        {
        }
        
        virtual ~Cons()
        {
         if( next != 0 ) delete next;
         //std::cout<< "~Cons" << car << std::endl;  
        }
        
        T value;
        boost::function< Cons<T>* (void)> generator;
        Cons* next;
     
        
    friend Cons<T>* make_cons<>( T val, const boost::function< Cons<T>* (void)>& op );
    friend Cons<T>* make_cons<>( T val, Cons<T>* next );
    friend T car<>( Cons<T>* _pair );
    friend Cons<T>* cdr<>( Cons<T>* _pair );
    friend bool has_next<>( Cons<T>* _pair );
    friend void destroy_cons<>( Cons<T>* _pair );
    };
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    bool has_next( Cons<T>* _pair )
    {
       return !( _pair->generator.empty() );
    }
    ////////////////////////////////////////////////////////////////////////////
    template < class T >
    Cons<T>* make_cons( T val,const boost::function< Cons<T>* (void)>& op )
    {
        return new Cons<T>(val, op);
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Cons<T>* make_cons( T val, Cons<T>* next )
    {
        if ( next == 0 )
        {
            return new Cons<T>(val);
        }

        
        return new Cons<T>(val
                        , [ next ] ()
                        {
                            return next;
                        });
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    void destroy_cons( Cons<T> * _pair )
    {
        delete _pair;
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    T car( Cons<T>* _pair )
    {
        return _pair->value;
    }
    ////////////////////////////////////////////////////////////////////////////
    template < typename T >
    Cons<T>* cdr( Cons<T>* _pair )
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
