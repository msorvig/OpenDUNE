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
extern void qtPaletteUpdate(unsigned char *palette, int from, int length);

#ifdef __cplusplus
}
#endif

#endif
