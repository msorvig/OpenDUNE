#ifndef OPENDUNE_INTERFACE_QT_H
#define OPENDUNE_INTERFACE_QT_H

#ifdef __cplusplus
extern "C" {
#else
#include "types.h"
#endif

struct DuneEvent
{
    bool isKeyEvent; // key or mouse event.
    unsigned char key;
    bool isPress;
    int mouseX;
    int mouseY;
    bool leftButton;
    bool rightButton;
} ;

bool qtHasEvent();
struct DuneEvent qtNextEvent();

void qtLockMutex();
void qtUnlockMutex();

void qtFramebufferUpdate(unsigned char *frameBuffer, int width, int height);
void qtPaletteUpdate(unsigned char *palette, int from, int length);

void qtCreateSoundSystem();
void qtDestroySoundSystem();
void qtPlaySound(unsigned char *soundBuffer, int lenght, int frequency);
void qtStopSound();
bool qtIsPlaying();

#ifdef __cplusplus
}
#endif

#endif
