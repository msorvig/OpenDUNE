/* $Id$ */

#include <stdio.h>
#include "types.h"
#include "libemu.h"
#include "map.h"

/**
 * Emulator wrapper around Map_MoveDirection().
 *
 * @name emu_Map_MoveDirection
 * @implements 0F78:0435:000E:32E0 ()
 */
void emu_Map_MoveDirection()
{
	uint16 direction;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	direction = emu_get_memory16(emu_ss, emu_sp, 0x0);

	emu_ax = Map_MoveDirection(direction);
}

/**
 * Emulator wrapper around Map_SetSelection().
 *
 * @name emu_Map_SetSelection
 * @implements 0F78:02D5:0014:4ABC ()
 */
void emu_Map_SetSelection()
{
	uint16 packed;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	packed = emu_get_memory16(emu_ss, emu_sp, 0x0);

	Map_SetSelection(packed);
}

/**
 * Emulator wrapper around Map_SetSelectionSize().
 *
 * @name emu_Map_SetSelectionSize
 * @implements 0F78:0285:001C:04DB ()
 */
void emu_Map_SetSelectionSize()
{
	uint16 layout;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	layout = emu_get_memory16(emu_ss, emu_sp, 0x0);

	emu_ax = Map_SetSelectionSize(layout);
}

/**
 * Emulator wrapper around Map_SetSelectionObjectPosition().
 *
 * @name emu_Map_SetSelectionObjectPosition
 * @implements 0F78:01B4:0016:23DD ()
 */
void emu_Map_SetSelectionObjectPosition()
{
	uint16 packed;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	packed = emu_get_memory16(emu_ss, emu_sp, 0x0);

	emu_ax = Map_SetSelectionObjectPosition(packed);
}

/**
 * Emulator wrapper around Map_UpdateMinimapPosition().
 *
 * @name emu_Map_UpdateMinimapPosition
 * @implements 0F78:0008:002C:AB63 ()
 */
void emu_Map_UpdateMinimapPosition()
{
	uint16 packed;
	bool forceUpdate;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	packed      = emu_get_memory16(emu_ss, emu_sp, 0x0);
	forceUpdate = (emu_get_memory16(emu_ss, emu_sp, 0x2) != 0);

	Map_UpdateMinimapPosition(packed, forceUpdate);
}

/**
 * Emulator wrapper around Map_IsValidPosition().
 *
 * @name emu_Map_IsValidPosition
 * @implements B4CD:0F8B:0015:1689 ()
 */
void emu_Map_IsValidPosition()
{
	uint16 packed;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	packed = emu_get_memory16(emu_ss, emu_sp, 0x0);

	emu_ax = Map_IsValidPosition(packed) ? 1 : 0;
}

/**
 * Emulator wrapper around Map_IsPositionUnveiled().
 *
 * @name emu_Map_IsPositionUnveiled
 * @implements B4CD:1BC4:0013:1AB3 ()
 */
void emu_Map_IsPositionUnveiled()
{
	uint16 position;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	position = emu_get_memory16(emu_ss, emu_sp, 0x0);

	emu_ax = Map_IsPositionUnveiled(position) ? 1 : 0;
}