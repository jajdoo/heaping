
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



#ifndef Application_H
#define Application_H

namespace proj
{

	//						---- class Application ----
	//==========================================================================
	//--------------------------------------------------------------------------

	class application
	{
	public:
		 application	( );
		~application	( );

		void go( );

	private:
		void printMenu		( );
		void buildDatabase	( );
	};

	//--------------------------------------------------------------------------
	//==========================================================================
	
}

#endif