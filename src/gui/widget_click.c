/* $Id$ */

#include <assert.h>
#include <stdio.h>
#include "types.h"
#include "libemu.h"
#include "../global.h"
#include "../pool/structure.h"
#include "../pool/unit.h"
#include "../structure.h"
#include "../unit.h"
#include "widget.h"

extern void f__0C3A_142D_0018_6667();
extern void f__B4E9_0050_003F_292A();
extern void f__B520_08E6_0038_85A4();
extern void f__B520_096E_003C_F7E4();
extern void overlay(uint16 cs, uint8 force);

/**
 * Handles scrolling of a scrollbar.
 *
 * @param scrollbar The scrollbar.
 * @param scroll The amount of scrolling.
 */
void GUI_Widget_Scrollbar_Scroll(WidgetScrollbar *scrollbar, uint16 scroll, csip32 scrollbarcsip)
{
	scrollbar->scrollPosition += scroll;

	if ((int16)scrollbar->scrollPosition >= scrollbar->scrollMax - scrollbar->scrollPageSize) {
		scrollbar->scrollPosition = scrollbar->scrollMax - scrollbar->scrollPageSize;
	}

	if ((int16)scrollbar->scrollPosition <= 0) scrollbar->scrollPosition = 0;

	emu_push(scrollbarcsip.s.cs); emu_push(scrollbarcsip.s.ip);
	emu_push(emu_cs); emu_push(0x068C); f__B520_096E_003C_F7E4();
	emu_sp += 4;

	GUI_Widget_ScrollBar_Draw((Widget *)emu_get_memorycsip(scrollbar->parent), scrollbar->parent);
}

/**
 * Handles Click event for a sprite/text button.
 *
 * @param w The widget.
 * @return False, always.
 */
bool GUI_Widget_SpriteTextButton_Click(Widget *w)
{
	Structure *s;

	VARIABLE_NOT_USED(w);

	s = Structure_Get_ByPackedTile(g_global->selectionPosition);

	switch (g_global->variable_97E5) {
		default: break;

		case 0x26: /* "Place it" */
			if (s->type == STRUCTURE_CONSTRUCTION_YARD) {
				Structure *ns;

				ns = Structure_Get_ByIndex(s->linkedID);
				g_global->activeStructure = g_global->structureStartPos;
				g_global->activeStructure.s.ip += ns->index * sizeof(Structure);
				g_global->activeStructureType = s->objectType;
				g_global->variable_38EC = Structure_IsValidBuildLocation(g_global->variable_3A00, g_global->activeStructureType);
				g_global->activeStructurePosition = g_global->selectionPosition;
				s->linkedID = STRUCTURE_INVALID;

				emu_push(2);
				emu_push(emu_cs); emu_push(0x111E); emu_cs = 0x34E9; overlay(0x34E9, 0); f__B4E9_0050_003F_292A();
				emu_sp += 2;
			}
			break;

		case 0x28: /* "On hold" */
			s->flags.s.repairing = false;
			s->flags.s.onHold    = false;
			s->flags.s.upgrading = false;
			break;

		case 0x29: /* "Build it" */
			emu_push(s->objectType);
			emu_push(g_global->structureStartPos.s.cs); emu_push(g_global->structureStartPos.s.ip + s->index * sizeof(Structure));
			emu_push(emu_cs); emu_push(0x1151); emu_cs = 0x0C3A; f__0C3A_142D_0018_6667();
			emu_sp += 6;
			break;

		case 0x2A: /* "Launch" */
		case 0x2B: /* "Fremen" */
		case 0x2C: /* "Saboteur" */
			Structure_ActivateSpecial(s);
			break;

		case 0x2E: /* "%d%% done" */
			s->flags.s.onHold = true;
			break;
	}
	return false;
}

/**
 * Handles Click event for scrollbar up button.
 *
 * @param w The widget.
 * @return False, always.
 */
bool GUI_Widget_Scrollbar_ArrowUp_Click(Widget *w)
{
	GUI_Widget_Scrollbar_Scroll((WidgetScrollbar *)emu_get_memorycsip(w->scrollbar), -1, w->scrollbar);

	return false;
}

/**
 * Handles Click event for scrollbar down button.
 *
 * @param w The widget.
 * @return False, always.
 */
bool GUI_Widget_Scrollbar_ArrowDown_Click(Widget *w)
{
	GUI_Widget_Scrollbar_Scroll((WidgetScrollbar *)emu_get_memorycsip(w->scrollbar), 1, w->scrollbar);

	return false;
}

/**
 * Handles Click event for scrollbar button.
 *
 * @param w The widget.
 * @return False, always.
 */
bool GUI_Widget_Scrollbar_Click(Widget *w, csip32 wcsip)
{
	WidgetScrollbar *scrollbar;
	uint16 positionX, positionY;

	scrollbar = (WidgetScrollbar *)emu_get_memorycsip(w->scrollbar);

	positionX = w->offsetX;
	if (w->offsetX < 0) positionX += g_global->variable_4062[w->parentID][2] << 3;
	positionX += g_global->variable_4062[w->parentID][0] << 3;

	positionY = w->offsetY;
	if (w->offsetY < 0) positionY += g_global->variable_4062[w->parentID][3];
	positionY += g_global->variable_4062[w->parentID][1];

	if ((w->state & 0x4400) != 0) {
		scrollbar->pressed = 0;
		GUI_Widget_ScrollBar_Draw(w, wcsip);
	}

	if ((w->state & 0x1100) != 0) {
		int16 positionCurrent;
		int16 positionBegin;
		int16 positionEnd;

		scrollbar->pressed = 0;

		if (w->width > w->height) {
			positionCurrent = g_global->mouseX;
			positionBegin = positionX + scrollbar->position + 1;
		} else {
			positionCurrent = g_global->mouseY;
			positionBegin = positionY + scrollbar->position + 1;
		}

		positionEnd = positionBegin + scrollbar->size;

		if (positionCurrent <= positionEnd && positionCurrent >= positionBegin) {
			scrollbar->pressed = 1;
			scrollbar->pressedPosition = positionCurrent - positionBegin;
		} else {
			GUI_Widget_Scrollbar_Scroll(scrollbar, (positionCurrent < positionBegin ? -scrollbar->scrollPageSize : scrollbar->scrollPageSize), w->scrollbar);
		}
	}

	if ((w->state & 0x2200) != 0 && scrollbar->pressed != 0) {
		int16 position, size;

		if (w->width > w->height) {
			size = w->width - 2 - scrollbar->size;
			position = g_global->mouseX - scrollbar->pressedPosition - positionX - 1;
		} else {
			size = w->height - 2 - scrollbar->size;
			position = g_global->mouseY - scrollbar->pressedPosition - positionY - 1;
		}

		if (position < 0) {
			position = 0;
		} else if (position > size) {
			position = size;
		}

		if (scrollbar->position != position) {
			scrollbar->position = position;
			scrollbar->dirty = 1;
		}

		emu_push(w->scrollbar.s.cs); emu_push(w->scrollbar.s.ip);
		emu_push(emu_cs); emu_push(0x0605); emu_cs = 0xB520; f__B520_08E6_0038_85A4();
		emu_sp += 4;

		if (scrollbar->dirty != 0) {
			assert(scrollbar->parent.csip == wcsip.csip);
			GUI_Widget_ScrollBar_Draw(w, wcsip);
		}
	}

	return false;
}