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
// Copyright (c) 1995-2005 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: TiaWidget.hxx,v 1.4 2005-08-16 18:34:12 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef TIA_WIDGET_HXX
#define TIA_WIDGET_HXX

class GuiObject;
class ButtonWidget;
class DataGridWidget;
class StaticTextWidget;
class ToggleBitWidget;
class EditTextWidget;
class ColorWidget;

#include "Widget.hxx"
#include "Command.hxx"


class TiaWidget : public Widget, public CommandSender
{
  public:
    TiaWidget(GuiObject* boss, int x, int y, int w, int h);
    virtual ~TiaWidget();

    void handleCommand(CommandSender* sender, int cmd, int data, int id);
    void loadConfig();

  private:
    void fillGrid();
    void changeColorRegs();
    void convertCharToBool(BoolArray& b, unsigned char value);
    int convertBoolToInt(const BoolArray& b);

  private:
    DataGridWidget* myRamGrid;
    EditTextWidget* myBinValue;
    EditTextWidget* myDecValue;
    EditTextWidget* myLabel;

    DataGridWidget* myColorRegs;

    ColorWidget* myCOLUP0Color;
    ColorWidget* myCOLUP1Color;
    ColorWidget* myCOLUPFColor;
    ColorWidget* myCOLUBKColor;

    ToggleBitWidget* myGRP0;
    ToggleBitWidget* myGRP1;

    DataGridWidget* myPosP0;
    DataGridWidget* myPosP1;

    DataGridWidget* myHMP0;
    DataGridWidget* myHMP1;

    DataGridWidget* myNusiz0;
    DataGridWidget* myNusiz1;
    EditTextWidget* myNusiz0Text;
    EditTextWidget* myNusiz1Text;

    CheckboxWidget* myRefP0;
    CheckboxWidget* myRefP1;
    CheckboxWidget* myDelP0;
    CheckboxWidget* myDelP1;
};

#endif
