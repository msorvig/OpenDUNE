
#include "types.h"
#include "../os/error.h"

#include "video.h"

#include "../file.h"
#include "../gfx.h"
#include "../input/input.h"
#include "../input/mouse.h"
#include "../opendune.h"


//Mouse_EventHandler(s_mousePosX / SCREEN_MAGNIFICATION, s_mousePosY / SCREEN_MAGNIFICATION, s_mouseButtonLeft, s_mouseButtonRight);
// 	Input_EventHandler(key);

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
 * Because we rarely want to draw in 320x200, this function copies from the
 *  320x200 buffer to the real screen, scaling where needed.
 */
void Video_DrawScreen()
{
    puts("Video_DrawScreen()");
}

/**
 * Runs every tick to handle video driver updates.
 */
void Video_Tick()
{
   puts("Video_Tick()");
}

/**
 * Change the palette with the palette supplied.
 * @param palette The palette to replace the current with.
 * @param from From which colour.
 * @param length The length of the palette (in colours).
 */
void Video_SetPalette(void *palette, int from, int length)
{
   puts("Video_SetPalette()");
}
