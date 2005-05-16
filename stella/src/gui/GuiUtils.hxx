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
// Copyright (c) 1995-2005 by Bradford W. Mott
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: GuiUtils.hxx,v 1.8 2005-05-16 00:02:32 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef UTILITIES_HXX
#define UTILITIES_HXX

#include "bspf.hxx"

/**
  A place to put GUI-related things that don't fit anywhere else.
  Probably not very neat, but at least it works ...

  @author  Stephen Anthony
  @version $Id: GuiUtils.hxx,v 1.8 2005-05-16 00:02:32 stephena Exp $
*/

#define kLineHeight 12
#define kScrollBarWidth 9

// Colors indices to use for the various GUI elements
enum OverlayColor {
  kColor,
  kBGColor,
  kShadowColor,
  kTextColor,
  kTextColorHi,
  kTextColorEm,
  kNumColors
};

// The commands generated by various widgets
enum {
  kOKCmd          = 'OK  ',
  kCloseCmd       = 'CLOS',
  kNextCmd        = 'NEXT',
  kPrevCmd        = 'PREV',
  kDefaultsCmd    = 'DEFA',
  kSetPositionCmd = 'SETP',
  kRendererChanged,
  kAspectRatioChanged,
  kFrameRateChanged,
  kZoomChanged,
  kVolumeChanged,
  kSoundEnableChanged
};

// Indicates a three-way possibility when changing the size of some quantity
enum Size {
  PreviousSize,
  GivenSize,
  NextSize
};

static const string EmptyString("");

template<typename T> inline void SWAP(T &a, T &b) { T tmp = a; a = b; b = tmp; }
template<typename T> inline T ABS (T x) { return (x>=0) ? x : -x; }

#define ARRAYSIZE(x) ((int)(sizeof(x) / sizeof(x[0])))

#endif
