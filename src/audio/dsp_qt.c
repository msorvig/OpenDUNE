/* $Id$ */

/** @file src/dsp_qt.c Qt implementation of the DSP. */

#include <assert.h>
#include "types.h"
#include "dsp.h"
#include "../src/opendune_interface_qt.h"

static uint8 s_status;

void DSP_Stop()
{
    qtStopSound();
    s_status = 0;
}

void DSP_Uninit()
{
    DSP_Stop();
}

bool DSP_Init()
{
 //   puts("DSP_Init");
    qtCreateSoundSystem();
    s_status = 0;
    return true;
}


void DSP_Play(const uint8 *data)
{
    DSP_Stop();

    data += ((uint16 *)data)[10];

    if (*data != 1) return;

    int bufferLength = (*(uint32 *)data >> 8) - 2;
    int frequency = 1000000 / (256 - data[4]);
    const uint8 *bufferStart = data + 6;

//    printf("DSP_PLAY %d %d\n", bufferLength, frequency);
    qtPlaySound(bufferStart, bufferLength, frequency);
    s_status = 2;
}

uint8 DSP_GetStatus()
{
//    puts("DSP_GetStatus");
    return qtIsPlaying() ? s_status : 0;
}
