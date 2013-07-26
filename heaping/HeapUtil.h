
/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
part of project for "data structores/introduction to algorithms" 
summer course, 2011

case study: heaps with variable degree ("d-ary heap")

the project was compiled and executed successfuly under:
- platform	::	Microsoft Windows 7
- IDE		::	Microsoft Visual C++ Express 2010 (msvc10)

last revision	::  3/september/2010, 16:28
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


#ifndef HeapUtil_H
#define HeapUtil_H

#include "clock.h"

namespace proj
{

	//						---- struct report ----
	//==========================================================================
	//--------------------------------------------------------------------------
	/*used by HeapUtil to store performance reports*/
	struct Report
	{
		void	reset( )
		{
			_degree		= 0;
			_ticks		= 0;
			_swap_count	= 0;
			_cmp_count	= 0;
		}

		unsigned int		_degree;
		unsigned __int64	_ticks;
		unsigned long		_swap_count;
		unsigned long		_cmp_count;
	};
	//--------------------------------------------------------------------------
	//==========================================================================
	

	//						   ---- class HeapUtil ----
	//==========================================================================
	//--------------------------------------------------------------------------
	// utility class for heap methods. 
	// imitates std heap related in <algorithm>

	template < class Container, class Iterator = Container::iterator, class Type = Container::value_type >
	class HeapUtil
	{
	public:
		HeapUtil ( unsigned int degree );
		~HeapUtil( ) ;

		void	makeHeap	( Iterator begin, Iterator end );
		void	sortHeap	( Iterator begin, Iterator end );
		void	popHeap		( Iterator begin, Iterator end );
		void	pushHeap	( Iterator begin, Iterator end );

		inline		Report	getReport ( )						const	{ return _cur_report; }
		inline		void	setDegree ( unsigned int degree )			{ _degree = degree<2 ? _degree : degree }
		inline		int		getDegree ( )						const	{ return _degree; }

	private:
		void		heapifyDown	( Iterator begin, Iterator end, Iterator suspect );
		void		heapifyUp	( Iterator begin, Iterator end, Iterator suspect );
		Iterator	child		( Iterator begin, Iterator end, Iterator parent,  int childNumber );
		Iterator	parent		( Iterator begin, Iterator end, Iterator item );

		void	iterSwap	( Iterator first, Iterator second );
		void	beginReport ( );
		void	endReport	( );

		inline		int	parentIndex ( int itemIndex )						const { return (itemIndex-1)/_degree; }
		inline		int	childIndex	( int parentIndex, int childNumber )	const { return _degree*parentIndex + (childNumber+1); }

		//---------------------------
		unsigned int	_degree;
		Report			_cur_report;
		CRdtscTimer		_timer;
		//---------------------------
	};
	
	//--------------------------------------------------------------------------
	//==========================================================================

} //namespace proj


//-----------------------------------------------------------
template < class Container, class Iterator, class Type >
proj::HeapUtil<Container,Iterator,Type>::HeapUtil ( unsigned int degree )
	:
		_degree	( degree < 2 ? 2 : degree )
{
}
//-----------------------------------------------------------


//-----------------------------------------------------------
template < class Container, class Iterator, class Type >
proj::HeapUtil<Container,Iterator,Type>::~HeapUtil	( )	 
{
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	Rearranges the elements in the range [begin,end) in such a 
	way that they form a heap.*/
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::makeHeap ( Iterator begin, Iterator end )
{
	beginReport();

	for( Iterator i = begin + (end-begin)/_degree ; i!=begin ; --i ) 
	{
		heapifyDown( begin, end, i );
	}
	
	heapifyDown( begin, end, begin );

	endReport();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	Rearranges the elements in the range [begin,end) in such a way that the 
	part considered a heap is shortened by one by removing its highest element.
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::popHeap(	Iterator begin,
															Iterator end	)
{
	beginReport();

	iterSwap( begin, end-1 );
	heapifyDown( begin, end-1, begin );

	endReport();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	extends the range considered a heap to [begin,end) 
	by placing the value in (last-1) into its corresponding location in it.
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::pushHeap(	Iterator begin,
															Iterator end	)
{
	beginReport();

	heapifyUp( begin, end-1, end-1 );

	endReport();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	sort the range [begin,end) in increasing order by breaking the heap down.
	the range must have been initialized as a heap using buildHeap. 
	the range will no longer maintain the heap property.*/
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::sortHeap	( Iterator begin, Iterator end )
{
	beginReport();

	for( Iterator cur_end = end-1 ; cur_end!=begin ; --cur_end )
	{
		iterSwap( begin, cur_end );
		heapifyDown( begin, cur_end, begin );
	}

	endReport();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	slides suspect down if it breaks the heap property in respect to its children.
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::heapifyDown(	Iterator begin, 
																Iterator end, 
																Iterator suspect )
{
	Iterator	dominant = suspect;
	Iterator	child_i	 = child(begin, end, suspect, 0);

	// seek dominant between current index and its children
	for( int j=0 ; j<=int(_degree) && child_i!=end ; ++j, ++child_i )
	{
		++_cur_report._cmp_count;
		dominant = *dominant < *child_i ? child_i : dominant;
	}

	// if the parent is not the dominant, slide him down and heapify again
	if( dominant!=suspect )
	{
		iterSwap( dominant, suspect );
		heapifyDown( begin, end, dominant );
	}
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	slides suspect up if it breaks the heap property in respect to its parent.
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::heapifyUp	(	Iterator begin, 
																Iterator end, 
																Iterator suspect )
{
	Iterator	parent_i = parent( begin, end, suspect );

	// if parent is weaker than his child bubble child up
	++_cur_report._cmp_count;
	if( *parent_i < *suspect )
	{
		iterSwap( parent_i, suspect );
		if( parent_i!=begin )
		{
			heapifyUp( begin, end, parent_i );
		}
	}
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/* reset current report and start clock. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::beginReport ()
{
	_cur_report.reset();
	_cur_report._degree = this->_degree;
	_timer.start();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/* stop clock. */
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::endReport ()
{
	_cur_report._ticks = _timer.stop();
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/* swap first and last, increment reports swap count.*/
template < class Container, class Iterator, class Type >
void	proj::HeapUtil<Container,Iterator,Type>::iterSwap	( Iterator first, Iterator second )
{
	++_cur_report._swap_count;
	std::iter_swap( first, second );
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	get child of parent within the range [begin,end)
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
Iterator proj::HeapUtil<Container,Iterator,Type>::child	(	Iterator begin,
															Iterator end,
															Iterator parent, 
															int childNumber )	
{
	int c = childIndex( parent-begin, childNumber );
	return  c < end-begin ? begin+c : end;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
/*	get the parent of item within the range [begin,end). 
	range must have been initialized as a heap using buildHeap. */
template < class Container, class Iterator, class Type >
Iterator proj::HeapUtil<Container,Iterator,Type>::parent (	Iterator begin,
															Iterator end,
															Iterator item )
{
	unsigned p = parentIndex( item-begin );
	return p>0 ? begin+p : begin ;
}
//-----------------------------------------------------------

#endif
