/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/11 20:21:14 $
 * $Revision: 1.19.2.1 $
 */

// iostream.cpp

#include <mslconfig>

#ifndef _MSL_NO_IO

#include <ios>

#ifndef _MSL_NO_CONSOLE_IO

#include <cstdio>
#include <istream>
#include <ostream>
#include <msl_consolebuf>
#include <msl_thread>

#endif

#ifdef __MWERKS__
	#pragma warn_padding off
#endif

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#if _MSL_FORCE_ENUMS_ALWAYS_INT
		#pragma enumsalwaysint on
	#else
		#pragma enumsalwaysint off
	#endif
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#if _MSL_FORCE_ENABLE_BOOL_SUPPORT
		#pragma bool on
	#else
		#pragma bool off
	#endif
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

int ios_base::index_;

#ifndef _MSL_NO_CONSOLE_IO

int __nInit::ninit_cnt_s;
int __wInit::winit_cnt_s;

_MSL_IMP_EXP_CPP extern istream cin;
_MSL_IMP_EXP_CPP extern ostream cout;
_MSL_IMP_EXP_CPP extern ostream clog;
_MSL_IMP_EXP_CPP extern ostream cerr;

#ifndef _MSL_NO_WCHART_CPP_SUPPORT

	_MSL_IMP_EXP_CPP extern wistream wcin;
	_MSL_IMP_EXP_CPP extern wostream wcout;
	_MSL_IMP_EXP_CPP extern wostream wclog;
	_MSL_IMP_EXP_CPP extern wostream wcerr;

#endif

#ifdef __MWERKS__
	#pragma suppress_init_code on
#endif

istream cin;
ostream cout;
ostream clog;
ostream cerr;

#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	wistream wcin;
	wostream wcout;
	wostream wclog;
	wostream wcerr;
#endif

#ifdef __MWERKS__
	#pragma suppress_init_code off
#endif

namespace
{

Metrowerks::mutex&
get_stream_init_mutex_impl()
{
	static Metrowerks::mutex mut;
	return mut;
}

extern "C" void init_stream_init_mutex()
{
	get_stream_init_mutex_impl();
}

Metrowerks::once_flag stream_init_flag = _MSL_THREAD_ONCE_INIT;

Metrowerks::mutex&
get_stream_init_mutex()
{
	Metrowerks::call_once(init_stream_init_mutex, stream_init_flag);
	return get_stream_init_mutex_impl();
}

}

__nInit::__nInit()
{
	Metrowerks::mutex::scoped_lock lock(get_stream_init_mutex());
	static Metrowerks::console_inputbuf<char> fin(stdin);
	static Metrowerks::console_outputbuf<char> fout(stdout);
	static Metrowerks::console_outputbuf<char> ferr(stderr);

	if (ninit_cnt_s++ == 0)
	{
		new (&cin)istream(&fin);
		new (&cout)ostream(&fout);
		new (&cerr)ostream(&ferr);
		new (&clog)ostream(&ferr);
		cin.tie(&cout);
		cerr.setf(ios_base::unitbuf);

		fin.pubsetbuf(0, 0);
		fout.pubsetbuf(0, 0);
		ferr.pubsetbuf(0, 0);
	}
}

__nInit::~__nInit()
{
	Metrowerks::mutex::scoped_lock lock(get_stream_init_mutex());
	if (--ninit_cnt_s == 0)
	{
		cout.flush();
		cerr.flush();
		clog.flush();
	#ifdef __MWERKS__
		__destroy(&cin);
		__destroy(&cout);
		__destroy(&cerr);
		__destroy(&clog);
	#endif
	}
}

__wInit::__wInit()
{
#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	Metrowerks::mutex::scoped_lock lock(get_stream_init_mutex());

	static Metrowerks::console_inputbuf<wchar_t> wfin(stdin);
	static Metrowerks::console_outputbuf<wchar_t> wfout(stdout);
	static Metrowerks::console_outputbuf<wchar_t> wferr(stderr);

	if (winit_cnt_s++ == 0)
	{
		new (&wcin)wistream(&wfin);
		new (&wcout)wostream(&wfout);
		new (&wcerr)wostream(&wferr);
		new (&wclog)wostream(&wferr);
		wcin.tie(&wcout);
		wcerr.setf(ios_base::unitbuf);

		wfin.pubsetbuf(0, 0);
		wfout.pubsetbuf(0, 0);
		wferr.pubsetbuf(0, 0);
	}
#endif
}

__wInit::~__wInit()
{
#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	Metrowerks::mutex::scoped_lock lock(get_stream_init_mutex());
	if (--winit_cnt_s == 0)
	{
		wcout.flush();
		wcerr.flush();
		wclog.flush();
	#ifdef __MWERKS__
		__destroy(&wcin);
		__destroy(&wcout);
		__destroy(&wcerr);
		__destroy(&wclog);
	#endif
	}
#endif
}

ios_base::Init::Init ()
{
	static __nInit n;
	static __wInit w;
}

#endif  // _MSL_NO_CONSOLE_IO

#ifndef _MSL_NO_CPP_NAMESPACE
	} // namespace std
#endif

#endif // _MSL_NO_IO

// hh 971220 fixed MOD_INCLUDE
// hh 980112 Modifications to prevent memory leaks
// hh 981122 Replace #include <iostream> with <istream> and <ostream>
// hh 981124 Added code to insure that the standard streams are constructed and destructed
//           only within ios_base::Init
// hh 990617 Rewrote.
// hh 000130 Installed _MSL_IMP_EXP_CPP
// hh 000604 Added support for sync_with_stdio
// hh 010125 Split ios_base::Init into 2 classes, one for narrow and one for wide streams
// hh 010212 Installed _MSL_NO_CONSOLE_IO
// hh 011106 Removed tie statements for cerr, clog, wcerr and wclog
// hh 030711 Protected from pad warning
