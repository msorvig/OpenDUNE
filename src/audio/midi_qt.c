/* $Id$ */

/** @file src/midi_qt.c Windows implementation of the MIDI. Uses midiOut
 *  functions from the Windows API, which contain a softsynth and handles all
 *  MIDI output for us. */

#include <stdio.h>
#include "types.h"
#include "../os/error.h"
#include "midi.h"
#include "../src/opendune_interface_qt.h"

bool midi_init()
{
    return qtCreateMidiSystem();
}

void midi_uninit()
{
    qtDestroyMidiSystem();
}

void midi_send(uint32 data)
{
    qtMidiSend(data);
}

void midi_reset()
{
    puts("midi_reset");
}
