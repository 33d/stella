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
// Copyright (c) 1995-2010 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id$
//============================================================================

#include "Event.hxx"
#include "Booster.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
BoosterGrip::BoosterGrip(Jack jack, const Event& event, const System& system)
  : Controller(jack, event, system, Controller::BoosterGrip)
{
  if(myJack == Left)
  {
    myUpEvent      = Event::JoystickZeroUp;
    myDownEvent    = Event::JoystickZeroDown;
    myLeftEvent    = Event::JoystickZeroLeft;
    myRightEvent   = Event::JoystickZeroRight;
    myFireEvent    = Event::JoystickZeroFire1;
    myTriggerEvent = Event::JoystickZeroFire2;
    myBoosterEvent = Event::JoystickZeroFire3;
    myXAxisValue   = Event::SALeftAxis0Value;
    myYAxisValue   = Event::SALeftAxis1Value;
  }
  else
  {
    myUpEvent      = Event::JoystickOneUp;
    myDownEvent    = Event::JoystickOneDown;
    myLeftEvent    = Event::JoystickOneLeft;
    myRightEvent   = Event::JoystickOneRight;
    myFireEvent    = Event::JoystickOneFire1;
    myTriggerEvent = Event::JoystickOneFire2;
    myBoosterEvent = Event::JoystickOneFire3;
    myXAxisValue   = Event::SARightAxis0Value;
    myYAxisValue   = Event::SARightAxis1Value;
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
BoosterGrip::~BoosterGrip()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void BoosterGrip::update()
{
  // Digital events (from keyboard or joystick hats & buttons)
  myDigitalPinState[One]   = (myEvent.get(myUpEvent) == 0);
  myDigitalPinState[Two]   = (myEvent.get(myDownEvent) == 0);
  myDigitalPinState[Three] = (myEvent.get(myLeftEvent) == 0);
  myDigitalPinState[Four]  = (myEvent.get(myRightEvent) == 0);
  myDigitalPinState[Six]   = (myEvent.get(myFireEvent) == 0);

  // The CBS Booster-grip has two more buttons on it.  These buttons are
  // connected to the inputs usually used by paddles.
  myAnalogPinValue[Five] = (myEvent.get(myBoosterEvent) != 0) ? 
                            minimumResistance : maximumResistance;
  myAnalogPinValue[Nine] = (myEvent.get(myTriggerEvent) != 0) ? 
                            minimumResistance : maximumResistance;

  // Axis events (usually generated by the Stelladaptor)
  int xaxis = myEvent.get(myXAxisValue);
  int yaxis = myEvent.get(myYAxisValue);
  if(xaxis > 16384-4096)
  {
    myDigitalPinState[Four] = false;
    // Stelladaptor sends "half moved right" for L+R pushed together
    if(xaxis < 16384+4096)
      myDigitalPinState[Three] = false;
  }
  if(xaxis < -16384)
    myDigitalPinState[Three] = false;
  if(yaxis > 16384-4096)
  {
    myDigitalPinState[Two] = false;
    // Stelladaptor sends "half moved down" for U+D pushed together
    if(yaxis < 16384+4096)
      myDigitalPinState[One] = false;
  }
  if(yaxis < -16384)
    myDigitalPinState[One] = false;
}
