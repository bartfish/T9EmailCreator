#ifndef CON_CONSOLE_H
#define CON_CONSOLE_H

#pragma once

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <iterator>

namespace Con
{
	namespace detail
	{
		class ConData;
	}
	typedef boost::shared_ptr<detail::ConData> Impl;

	//
	// Pimpl class 
	//
	class Console
	{
		// the behind the scenes worker
		Impl impl;
		// the class will never get copied so leaving these as value types
		// is fine
		std::istream in;
		std::ostream out;

		// not implemented
		Console& operator=(const Console&);
		Console(const Console&);

	public:
		Console(const Impl&);

		// a unique token that represents this instance
		unsigned long get_id();

		// reads count bytes into buffer
		std::istream& read(char* buffer, std::streamsize count);

		// writes out count bytes from buffer
		std::ostream& write(const char* buffer, std::streamsize count);

		// insertion and extraction operators just forward to the i/ostreams
		template<class T>
		std::ostream& operator<<(const T& val)
		{
			out << val;
			out.flush();
			return out;
		}

		template<class T>
		std::istream& operator>>(T& val)
		{
			return in >> val;
		}

		// these allow the insertion and extraction
		// operators defined for the smart pointer 
		// (below) to work
		operator std::istream&();

		operator std::ostream&();

		// flushes the output stream
		void flush();

		// puts the console on top of all other windows
		void bring_to_top() const;

		// send the console to the back of all windows
		void send_to_back() const;
	};

	typedef boost::shared_ptr<Console> Handle;

	// allocates a new console and returns a handle to it
	bool __stdcall Create(Handle& newConsole);
	 // returns a handle to the console associated with the current process, if there is one
	Handle __stdcall GetOriginal();
	// returns the console with the specified id
	bool __stdcall GetFromID(unsigned long id, Handle& console);

	// these two operators allow the user to stream into and from
	// a console exactly the same way as they would with the 
	// stabdard streams, without having to dereference them first
	template<class T>
	Handle& operator<<(Handle& con, const T& val)
	{
		(*con) << val;
		return con;
	}

	template<class T>
	Handle& operator>>(Handle& con, T& val)
	{
		(*con) >> val;
		return con;
	}

	//
	// a reimplementation of std::ostream_iterator that can be configured
	// to flush either after every write, or when destructed.
	// std::ostream_iterator does work when given a console handle, 
	// but the results will not be visible on the console until the stream is flushed
	//
	// this class does it automatically, so that the copy operation
	// behaves more like using an ostream_iterator on cout/cerr
	//
	template<class T, class Elem = char, class Traits = std::char_traits<Elem> >
	class conout_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
	{
		std::ostream* console;
		Elem* delim;
		bool flushAfterWrite;
	public:
		conout_iterator(std::ostream& stream, const Elem* delim = 0, bool flushAfterWrite = true)
			: console(&stream), delim(delim), flushAfterWrite(flushAfterWrite)
		{}

		~conout_iterator()
		{
			if(!flushAfterWrite)
			{
				console->flush();
			}
		}

		// these 3 are dummy functions, which do nothing but are required
		conout_iterator& operator*()
		{
			return *this;
		}

		conout_iterator& operator++()
		{
			return *this;
		}

		conout_iterator& operator++(int)
		{
			return *this;
		}

		// Writes Val to the stream
		// followed by a delimeter if any was specified, before optionally flushing
		conout_iterator& operator=(const T& Val)
		{
			std::ostream& conout = *console;
			conout << Val;
			if(delim) conout << delim;
			if(flushAfterWrite)
			{
				conout.flush();
			}
			return *this;
		}
	};

	// convenience functions to construct a conout_iterator
	template<class T, class Elem>
	conout_iterator<T, Elem> make_ostream_iterator(Handle& handle, Elem* ptr = 0)
	{
		return conout_iterator<T, Elem>((*handle), ptr);
	}

	template<class T, class Elem, class Char_Traits>
	conout_iterator<T, Elem, Char_Traits> make_ostream_iterator(Handle& handle, Elem* ptr, Char_Traits& traits)
	{
		return conout_iterator<T, Elem, Char_Traits>((*handle), ptr, traits);
	}
}

using Con::make_ostream_iterator;

#endif
