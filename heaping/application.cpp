
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



#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "application.h"
#include "HeapUtil.h"

//					----- general and public ------
//===========================================================================
//---------------------------------------------------------------------------

//----------------------------------------------------------
proj::application::application()
{
}
//----------------------------------------------------------


//----------------------------------------------------------
proj::application::~application()
{
}
//----------------------------------------------------------


//----------------------------------------------------------
void	proj::application::go()
{
	printMenu();
	//buildDatabase();
}
//----------------------------------------------------------

//---------------------------------------------------------------------------
//===========================================================================



//							------ menue -------
//===========================================================================
//---------------------------------------------------------------------------

//--------------------------------------------------------------------
void	proj::application::printMenu()
{
	unsigned int size, deg ;
	char random=0;

	// general
	//---------------------------------------------
	std::cout<<" enter: degree, size: "<<std::endl;
	std::cin>>deg>>size;
	std::cout<<std::endl<<std::endl;
	//---------------------------------------------

	// another choice to make..
	//---------------------------------------------
	std::cout<<" random? (y/n) ";
	while( random!='y' && random!='n' )
		std::cin>>random;
	//---------------------------------------------

	std::vector<int> vec;

	// make the vector
	//---------------------------------------------
	switch( random )
	{

	case 'y':	
		for( unsigned int i=0 ; i<size ; ++i )
		{
			vec.push_back( rand()%999 );
			std::cout<<vec.back()<<" ";
		}
		break;

	case 'n':
		std::cout<<"gimme some values - ";
		for( unsigned int i=0 ; i<size ; ++i )
		{
			int j;
			std::cin>>j;
			vec.push_back( j );
		}
		break;
	}
	//---------------------------------------------


	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	
	proj::HeapUtil<std::vector<int>> util(deg);
	proj::Report r;

	// init the vec as a heap
	//---------------------------------
	util.makeHeap( vec.begin(), vec.end() );
	r = util.getReport();
	std::cout<<"building heap: "					<<std::endl<<std::endl<<std::endl; 
	std::cout	<<"comparisons:\t"<<r._cmp_count	<<std::endl
				<<"swaps:\t\t"<<r._swap_count		<<std::endl
				<<"cpu cycles:\t"<<r._ticks			<<std::endl<<std::endl;
	//---------------------------------
	
	// print initialized heap
	for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it )
		std::cout<<*it<<" ";
	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;

/*
	// test push and pop
	util.popHeap( vec.begin(), vec.end() );		vec.pop_back();for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	util.popHeap( vec.begin(), vec.end() );		vec.pop_back();for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	util.popHeap( vec.begin(), vec.end() );		vec.pop_back();for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	util.popHeap( vec.begin(), vec.end() );		vec.pop_back();for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;

	vec.push_back( rand()%20 );  util.pushHeap( vec.begin(), vec.end() );for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	vec.push_back( rand()%20 );  util.pushHeap( vec.begin(), vec.end() );for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	vec.push_back( rand()%20 );  util.pushHeap( vec.begin(), vec.end() );for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
	vec.push_back( rand()%20 );  util.pushHeap( vec.begin(), vec.end() );for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it ) std::cout<<*it<<" ";	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
*/

	// sort it
	//---------------------------------
	util.sortHeap( vec.begin(), vec.end()  );
	r = util.getReport();
	std::cout<<"sorting: "							<<std::endl<<std::endl<<std::endl; 
	std::cout	<<"comparisons:\t"<<r._cmp_count	<<std::endl
				<<"swaps:\t\t"<<r._swap_count		<<std::endl
				<<"cpu cycles:\t"<<r._ticks			<<std::endl<<std::endl;
	//---------------------------------

	// print sorted
	for( std::vector<int>::iterator it=vec.begin() ; it!=vec.end() ; ++it )
		std::cout<<*it<<" ";
	std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
}
//--------------------------------------------------------------------


//--------------------------------------------------------------------
/*	method for creating a database for performance analysis. 
	the data is saved in "Comma Separated Values" (csv) format to ease 
	trasfer to Microsoft Access or any other DBMS. */
void	proj::application::buildDatabase()
{
	std::ofstream f;
	f.open( "data.csv" ) ;

	f<<"type, degree, size, action, cmp_count, swaps_count, cpu_cycles"<<std::endl;

	std::cout<<"here goes:"<<std::endl;

	unsigned int min_deg=2,		max_deg=20,		deg_interval=1, 
				 min_size=100,	max_size=1000,	size_interval=100, 
				 repeats=1000;

	// for vector
	for( unsigned int deg=min_deg ; deg<=max_deg ; deg+=deg_interval )
	{
		
		proj::HeapUtil<std::vector<int>>  util( deg );

		for( unsigned int size=min_size ; size<=max_size ; size+=size_interval )
		{

			for( unsigned int again=0 ; again<repeats ; ++again )
			{
				std::cout<<" : vector :: degree: "<<deg<<","<<" size: "<<size<<" )"<<again<<"/"<<repeats<<std::endl;
				
				std::vector<int> vec(0);

				for( unsigned int i=0 ; i<size ; ++i )
				{
					vec.push_back( rand()%999 );
				}
				proj::Report r;

				//---------------------------------
				util.makeHeap( vec.begin(), vec.end() );
				r = util.getReport();
				f<<"vector,"<<deg<<","<<size<<",build, "<<r._cmp_count<<","<<r._swap_count<<","<<r._ticks<<std::endl;
				//---------------------------------

				//---------------------------------
				util.popHeap( vec.begin(), vec.end() );
				vec.pop_back();
				r = util.getReport();
				f<<"vector,"<<deg<<","<<size<<",pop, "<<r._cmp_count<<","<<r._swap_count<<","<<r._ticks<<std::endl;
				//---------------------------------

				//---------------------------------
				vec.push_back( rand()%999 );
				util.pushHeap( vec.begin(), vec.end() );
				r = util.getReport();
				f<<"vector,"<<deg<<","<<size<<",insert, "<<r._cmp_count<<","<<r._swap_count<<","<<r._ticks<<std::endl;
				//---------------------------------

				//---------------------------------
				util.sortHeap( vec.begin(), vec.end() );
				r = util.getReport();
				f<<"vector,"<<deg<<","<<size<<",sort, "<<r._cmp_count<<","<<r._swap_count<<","<<r._ticks<<std::endl;
				//---------------------------------
			}
		}
	}
}
//--------------------------------------------------------------------

//---------------------------------------------------------------------------
//===========================================================================