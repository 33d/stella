//============================================================================
//
//   SSSS    tt          lll  lll       
//  SS  SS   tt           ll   ll        
//  SS     tttttt  eeee   ll   ll   aaaa 
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2015 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id$
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef STACK_HXX
#define STACK_HXX

#include <cassert>

/**
 * Simple fixed size stack class.
 */
namespace Common {

template <class T, int MAX_SIZE = 50>
class FixedStack
{
  protected:
    T   _stack[MAX_SIZE];
    int _size;

  public:
    FixedStack<T, MAX_SIZE>() : _size(0) { }

    bool empty() const { return _size <= 0; }
    bool full() const  { return _size >= MAX_SIZE; }
    void clear() { _size = 0; }
    void push(const T& x)
    {
      assert(_size < MAX_SIZE);
      _stack[_size++] = x;
    }
    T top() const
    {
      if(_size > 0)
        return _stack[_size - 1];
      else
        return 0;
    }
    T pop()
    {
      assert(_size > 0);
      return std::move(_stack[--_size]);
    }
    int size() const { return _size; }
    T operator [](int i) const
    {
      assert(0 <= i && i < MAX_SIZE);
      return _stack[i];
    }

  private:
    // Following constructors and assignment operators not supported
    FixedStack(const FixedStack&) = delete;
    FixedStack(FixedStack&&) = delete;
    FixedStack& operator=(const FixedStack&) = delete;
    FixedStack& operator=(FixedStack&&) = delete;
};

}  // Namespace Common

#endif
