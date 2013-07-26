
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


#ifndef _RDTSCTIMER_H_
#define _RDTSCTIMER_H_

namespace proj
{
	//				 ----CPU tick timer----
	//=======================================================
	//-------------------------------------------------------
	// included for performance analysis.
	// made by Andreas Masur, codeguru forums:
	// http://www.codeguru.com/forum/showthread.php?t=291294

	class CRdtscTimer
	{
	  unsigned __int64 begin, end;

	  inline static unsigned __int64 _RDTSC()
	  {
		_asm    _emit 0x0F
		_asm    _emit 0x31
	  }

	public:
	  inline void start()
	  {
		begin = _RDTSC();
	  }
  
	  inline unsigned __int64 stop()
	  {
		end = _RDTSC();
		return (end-begin);
	  }
	};

	//-------------------------------------------------------
	//=======================================================
}


#endif // _RDTSCTIMER_H_