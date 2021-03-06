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

#ifndef AUDIO_WIDGET_HXX
#define AUDIO_WIDGET_HXX

class GuiObject;
class DataGridWidget;

#include "Widget.hxx"
#include "Command.hxx"


class AudioWidget : public Widget, public CommandSender
{
  public:
    AudioWidget(GuiObject* boss, const GUI::Font& lfont, const GUI::Font& nfont,
                int x, int y, int w, int h);
    virtual ~AudioWidget() = default;

  private:
    // ID's for the various widgets
    // We need ID's, since there are more than one of several types of widgets
    enum {
      kAUDFID,
      kAUDCID,
      kAUDVID
    };

    DataGridWidget* myAudF;
    DataGridWidget* myAudC;
    DataGridWidget* myAudV;

  private:
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;
    void loadConfig() override;

    // Following constructors and assignment operators not supported
    AudioWidget() = delete;
    AudioWidget(const AudioWidget&) = delete;
    AudioWidget(AudioWidget&&) = delete;
    AudioWidget& operator=(const AudioWidget&) = delete;
    AudioWidget& operator=(AudioWidget&&) = delete;
};

#endif
