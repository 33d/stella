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
// Copyright (c) 1995-2016 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id$
//============================================================================

#include "Console.hxx"
#include "TIA.hxx"
#include "Switches.hxx"
#include "DialogContainer.hxx"
#include "Dialog.hxx"
#include "EventHandler.hxx"
#include "OSystem.hxx"
#include "Widget.hxx"
#include "CommandDialog.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CommandDialog::CommandDialog(OSystem& osystem, DialogContainer& parent)
  : Dialog(osystem, parent)
{
  const GUI::Font& font = instance().frameBuffer().font();
  const int buttonWidth = font.getStringWidth("Right Diff B") + 20,
            buttonHeight = font.getLineHeight() + 6,
            rowHeight = font.getLineHeight() + 10;

  // Set real dimensions
  _w = 3 * (buttonWidth + 5) + 20;
  _h = 6 * rowHeight + 15;

  WidgetArray wid;
  ButtonWidget* b[16];
  int xoffset = 10, yoffset = 10;

  auto ADD_CD_BUTTON = [&](const string& label, int cmd)
  {
    ButtonWidget* bw = new ButtonWidget(this, font, xoffset, yoffset,
            buttonWidth, buttonHeight, label, cmd);
    xoffset += buttonWidth + 6;
    return bw;
  };

  // Row 1
  b[0] = ADD_CD_BUTTON("Select", kSelectCmd);
  b[4] = ADD_CD_BUTTON("Left Diff A", kLeftDiffACmd);
  b[8] = ADD_CD_BUTTON("Save State", kSaveStateCmd);

  // Row 2
  xoffset = 10;  yoffset += buttonHeight + 3;
  b[1] = ADD_CD_BUTTON("Reset", kResetCmd);
  b[5] = ADD_CD_BUTTON("Left Diff B", kLeftDiffBCmd);
  b[9] = ADD_CD_BUTTON("State Slot", kStateSlotCmd);

  // Row 3
  xoffset = 10;  yoffset += buttonHeight + 3;
  b[2]  = ADD_CD_BUTTON("Color TV", kColorCmd);
  b[6]  = ADD_CD_BUTTON("Right Diff A", kRightDiffACmd);
  b[10] = ADD_CD_BUTTON("Load State", kLoadStateCmd);

  // Row 4
  xoffset = 10;  yoffset += buttonHeight + 3;
  b[3]  = ADD_CD_BUTTON("B/W TV", kBWCmd);
  b[7]  = ADD_CD_BUTTON("Right Diff B", kRightDiffBCmd);
  b[11] = ADD_CD_BUTTON("Snapshot", kSnapshotCmd);

  // Row 5
  xoffset = 10;  yoffset += buttonHeight + 3;
  b[12] = ADD_CD_BUTTON("NTSC/PAL", kFormatCmd);
  b[13] = ADD_CD_BUTTON("Palette", kPaletteCmd);
  b[14] = ADD_CD_BUTTON("Reload ROM", kReloadRomCmd);

  // Row 6
  xoffset = 10 + buttonWidth + 6;  yoffset += buttonHeight + 3;
  b[15] = ADD_CD_BUTTON("Exit Game", kExitCmd);

  for(int i = 0; i < 16; ++i)
    wid.push_back(b[i]);

  addToFocusList(wid);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CommandDialog::handleCommand(CommandSender* sender, int cmd,
                                  int data, int id)
{
  bool consoleCmd = false, stateCmd = false;
  Event::Type event = Event::NoType;

  switch(cmd)
  {
    case kSelectCmd:
      event = Event::ConsoleSelect;
      consoleCmd = true;
      break;

    case kResetCmd:
      event = Event::ConsoleReset;
      consoleCmd = true;
      break;

    case kColorCmd:
      event = Event::ConsoleColor;
      consoleCmd = true;
      break;

    case kBWCmd:
      event = Event::ConsoleBlackWhite;
      consoleCmd = true;
      break;

    case kLeftDiffACmd:
      event = Event::ConsoleLeftDiffA;
      consoleCmd = true;
      break;

    case kLeftDiffBCmd:
      event = Event::ConsoleLeftDiffB;
      consoleCmd = true;
      break;

    case kRightDiffACmd:
      event = Event::ConsoleRightDiffA;
      consoleCmd = true;
      break;

    case kRightDiffBCmd:
      event = Event::ConsoleRightDiffB;
      consoleCmd = true;
      break;

    case kSaveStateCmd:
      event = Event::SaveState;
      consoleCmd = true;
      break;

    case kStateSlotCmd:
      event = Event::ChangeState;
      stateCmd = true;
      break;

    case kLoadStateCmd:
      event = Event::LoadState;
      consoleCmd = true;
      break;

    case kSnapshotCmd:
      instance().eventHandler().leaveMenuMode();
      instance().eventHandler().handleEvent(Event::TakeSnapshot, 1);
      break;

    case kFormatCmd:
      instance().eventHandler().leaveMenuMode();
      instance().console().toggleFormat();
      break;

    case kPaletteCmd:
      instance().eventHandler().leaveMenuMode();
      instance().console().togglePalette();
      break;

    case kReloadRomCmd:
      instance().eventHandler().leaveMenuMode();
      instance().reloadConsole();
      break;

    case kExitCmd:
      instance().eventHandler().handleEvent(Event::LauncherMode, 1);
      break;
  }

  // Console commands show be performed right away, after leaving the menu
  // State commands require you to exit the menu manually
  if(consoleCmd)
  {
    instance().eventHandler().leaveMenuMode();
    instance().eventHandler().handleEvent(event, 1);
    instance().console().switches().update();
    instance().console().tia().update();
    instance().eventHandler().handleEvent(event, 0);
  }
  else if(stateCmd)
    instance().eventHandler().handleEvent(event, 1);
}
