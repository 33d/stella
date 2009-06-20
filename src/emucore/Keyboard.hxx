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
// Copyright (c) 1995-2008 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: Keyboard.hxx,v 1.8 2008-02-06 13:45:21 stephena Exp $
//============================================================================

#ifndef KEYBOARD_HXX
#define KEYBOARD_HXX

#include "bspf.hxx"
#include "Control.hxx"
#include "Event.hxx"

/**
  The standard Atari 2600 keyboard controller

  @author  Bradford W. Mott
  @version $Id: Keyboard.hxx,v 1.8 2008-02-06 13:45:21 stephena Exp $
*/
class Keyboard : public Controller
{
  public:
    /**
      Create a new keyboard controller plugged into the specified jack

      @param jack The jack the controller is plugged into
      @param event The event object to use for events
    */
    Keyboard(Jack jack, const Event& event);

    /**
      Destructor
    */
    virtual ~Keyboard();

  public:
    /**
      Write the given value to the specified digital pin for this
      controller.  Writing is only allowed to the pins associated
      with the PIA.  Therefore you cannot write to pin six.

      @param pin The pin of the controller jack to write to
      @param value The value to write to the pin
    */
    virtual void write(DigitalPin pin, bool value);

    /**
      Update the entire digital and analog pin state according to the
      events currently set.
    */
    virtual void update();

  private:
    // State of the output pins
    uInt8 myPinState;

    // Pre-compute the events we care about based on given port
    // This will eliminate test for left or right port in update()
    Event::Type myOneEvent, myTwoEvent, myThreeEvent,
                myFourEvent, myFiveEvent, mySixEvent,
                mySevenEvent, myEightEvent, myNineEvent,
                myStarEvent, myZeroEvent, myPoundEvent;
};

#endif
