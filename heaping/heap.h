/*
#ifndef MAXHEAP_H
#define MAXHEAP_H


#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include"maxheap.h"


//								------ base ------
//===================================================================================
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------
proj::MaxHeap::MaxHeap ( int degree, int capacity, int default_value )
		:	_size			( 0 ),
			_capacity		( capacity	< 1 ? 1 : capacity	),
			_degree			( degree	< 2 ? 2 : degree	),
			_cmp_count		( 0 ),
			_copy_count		( 0 ),
			_initialized	( false ),
			_default_value	( default_value )
{
	_heap_arr	= new int[_capacity] ;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
proj::MaxHeap::~MaxHeap	( )	 
{ 
	delete [] _heap_arr; 
}
//-----------------------------------------------------------

//-----------------------------------------------------------------------------------
//===================================================================================



//						------ public access controls ------
//===================================================================================
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------
/*	initialized the arrays heap to follow heap logic.

void	proj::MaxHeap::init ( )
{
	_cmp_count		= 0;
	_copy_count		= 0;
	_initialized	= true;

	for( int  i=_size/_degree ; i>=0 ; --i ) 
		heapifyDown( i );

	std::cout<<" initializing	: cmp : " <<_cmp_count<<"  cpy: "<<_copy_count <<std::endl;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
 /*will pop the max back to the user and reorginize the heap
 if the heap is not initialized or empty will return the default
 that was set at contruction
int proj::MaxHeap::popMax	( )
{
	// throw default value
	if( _size==0 || !_initialized )		return _default_value;

	int ret = _heap_arr[0];
	
	std::swap( _heap_arr[0], _heap_arr[_size-1] );
	--_size;
	heapifyDown( 0 );
	
	return ret;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
 /*	insert item into the heap. note that if the heap was
	not initialized the new item will simply be appended
	(no heap logic will be applied)
bool	proj::MaxHeap::insert	( int item )
{
	if ( isFull() )		return false;
	_heap_arr[_size-1] = item;

	if( _initialized )	heapifyUp( _size );
	++_size;

	return true;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/* randomize the list (will render the list uninitialized)
void	proj::MaxHeap::randomize	( )
{
	_initialized = false;

	srand(time(0));

	for( int i=0 ; i<_capacity ; ++i )
	{
		_heap_arr[i] = rand()%999;
	}

	_size = _capacity;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/* well you know...
void	proj::MaxHeap::printSelf	( ) const
{
	for( int i=0 ; i<_size ; ++i )
	{
		std::cout<<_heap_arr[i]<<" " ;
	}

	std::cout<<std::endl;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	sorts the array in accending order, print a summery of the
	operation and the sorted array if show_result is true.
	NOTE : will cause the heap to empty
bool proj::MaxHeap::sort	( bool show_result ) 
{
	if( !_initialized ) return false;

	_cmp_count	= 0;
	_copy_count = 0;

	while( !isEmpty() )
	{
		popMax();
	}
	
	if(show_result)
	{
		for( int i=0 ; i<_capacity ; ++i )
		{
			std::cout<<_heap_arr[i]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<" sorting	: cmp : " <<_cmp_count<<" cpy: "<<_copy_count <<std::endl;
	return true;
}
//-----------------------------------------------------------

//-----------------------------------------------------------------------------------
//===================================================================================



//							------ private (utilities) ------
//===================================================================================
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------
/*	slides item at _heap_arr[index] down until its where it should be
	will do nothing when heap is unitialized unless invoked by proj::MaxHeap::init()

void	proj::MaxHeap::heapifyDown	( int index )
{
	if( !_initialized )		return ;

	int  dominant = index;

	// seek dominant between current index and its children
	for( int j=0, child_i=childIndex(index, 0) ; j<=_degree && child_i<_size ; ++j, child_i=childIndex(index, j) )
	{
		++_cmp_count;
		if( _heap_arr[dominant] < _heap_arr[child_i] )		
		{
			dominant = child_i;
		}
	}

	// if the parent is not the dominant, replace the two and heapify again
	if( dominant!=index )
	{
		++_copy_count;
		std::swap( _heap_arr[dominant], _heap_arr[index] );

		// no need to go deeper if we know dominant is infertile
		if( dominant*_degree<_size )
		{
			heapifyDown( dominant );
		}
	}
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	slides item at _heap_arr[index] up until its where it should be.
	will do nothing when heap is unitialized unless invoked by proj::MaxHeap::init()

void	proj::MaxHeap::heapifyUp	( int index )
{
	if( !_initialized )		return ;

	int	parent_i = parentIndex( index );

	// if parent is weaker than his child slide child up
	if( _heap_arr[parent_i] < _heap_arr[index] )
	{
		std::swap( _heap_arr[parent_i], _heap_arr[index] );

		if( parent_i!=0 )	
		{
			heapifyUp( parent_i );
		}
	}
}
//-----------------------------------------------------------

//-----------------------------------------------------------------------------------
//===================================================================================
*/