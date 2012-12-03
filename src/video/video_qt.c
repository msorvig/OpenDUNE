#include "../opendune_interface_qt.h"
#include "types.h"
#include "../os/error.h"

#include "video.h"

#include "../file.h"
#include "../gfx.h"
#include "../input/input.h"
#include "../input/mouse.h"
#include "../opendune.h"

// Globals
static uint8 s_gfx_screen8[SCREEN_WIDTH * SCREEN_HEIGHT]; // The current dune framebuffer

/**
 * Set the current position of the mouse.
 * @param x The new X-position of the mouse.
 * @param y The new Y-position of the mouse.
 */
void Video_Mouse_SetPosition(uint16 x, uint16 y)
{
    puts("Video_Mouse_SetPosition");
}

/**
 * Set the region in which the mouse is allowed to move, or 0 for no limitation.
 * @param minX The minimal X-position.
 * @param maxX The maximal X-position.
 * @param minY The minimal Y-position.
 * @param maxY The maximal Y-position.
 */
void Video_Mouse_SetRegion(uint16 minX, uint16 maxX, uint16 minY, uint16 maxY)
{
    puts("Video_Mouse_SetRegion");
}

/**
 * Initialize the video driver.
 */
bool Video_Init()
{
    puts("Video_Init()");
}

/**
 * Uninitialize the video driver.
 */
void Video_Uninit()
{
    puts("Video_Uninit");
}

/**
 * Runs every tick to handle video driver updates.
 */
void Video_Tick()
{
    // puts("Video_Tick()");

    qtLockMutex();
    // Process Events
    while (qtHasEvent()) {
        struct DuneEvent event = qtNextEvent();
        qtUnlockMutex();
        if (event.isKeyEvent) {
            Input_EventHandler(event.key | (event.isPress ? 0x0 : 0x80));
        } else {
            Mouse_EventHandler(event.mouseX, event.mouseY, event.leftButton, event.rightButton);
        }
        qtLockMutex();
    }
    qtUnlockMutex();

    // Push frame buffer update to Qt. (if it has changes)
    if (memcmp(GFX_Screen_Get_ByIndex(0), s_gfx_screen8, SCREEN_WIDTH * SCREEN_HEIGHT) != 0) {
        memcpy(s_gfx_screen8, GFX_Screen_Get_ByIndex(0), SCREEN_WIDTH * SCREEN_HEIGHT);
        qtLockMutex();
        qtFramebufferUpdate(&s_gfx_screen8, SCREEN_WIDTH, SCREEN_HEIGHT);
        qtUnlockMutex();
    }
}

/**
 * Change the palette with the palette supplied.
 * @param palette The palette to replace the current with.
 * @param from From which colour.
 * @param length The length of the palette (in colours).
 */
void Video_SetPalette(void *palette, int from, int length)
{
    // puts("Video_SetPalette()");

    qtLockMutex();
    qtPaletteUpdate(palette, from, length);
    qtUnlockMutex();
}
