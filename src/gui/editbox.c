/* $Id$ */

#include <assert.h>
#include <stdio.h>
#include "types.h"
#include "libemu.h"
#include "../global.h"
#include "widget.h"
#include "gui.h"

extern void f__2598_0000_0017_EB80();
extern void f__2B6C_0137_0020_C73F();
extern void f__2B6C_0169_001E_6939();
extern void f__B4DA_16CB_001D_31CC();
extern void f__B518_14F2_003E_977C();
extern void emu_Input_Flags_SetBits();
extern void emu_Input_Flags_ClearBits();
extern void emu_Input_Keyboard_HandleKeys2();
extern void emu_Font_GetCharWidth();
extern void emu_GUI_DrawFilledRectangle();
extern void emu_GUI_DrawText_Wrapper();
extern void emu_Unknown_07AE_0000();
extern void emu_Unknown_07AE_0103();
extern void overlay(uint16 cs, uint8 force);

/**
 * Draw a blinking cursor, used inside the EditBox.
 *
 * @param positionX Where to draw the cursor on the X position.
 * @param resetBlink If true, the blinking is reset and restarted.
 */
static void GUI_EditBox_BlinkCursor(uint16 positionX, bool resetBlink)
{
	assert(g_global->variable_6668.csip == 0x22A60D31);

	if (resetBlink) {
		g_global->tickEditBox = 0;
		g_global->editBoxShowCursor = 1;
	}

	if (g_global->tickEditBox > g_global->variable_76AC) return;
	if (!resetBlink) {
		g_global->tickEditBox = g_global->variable_76AC + 20;
	}

	g_global->editBoxShowCursor = (g_global->editBoxShowCursor == 0) ? 1 : 0;

	emu_push(emu_cs); emu_push(0x0329); emu_cs = 0x2B6C; f__2B6C_0137_0020_C73F();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }

	emu_push('W');
	emu_push(emu_cs); emu_push(0x034A); emu_cs = 0x2521; emu_Font_GetCharWidth();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }
	emu_sp += 2;

	emu_push((g_global->editBoxShowCursor) ? g_global->variable_6D5B : g_global->variable_6D59);
	emu_push(g_global->variable_992B + g_global->variable_9931 - 1);
	emu_push(positionX + emu_ax);
	emu_push(g_global->variable_992B);
	emu_push(positionX);
	emu_push(emu_cs); emu_push(0x035F); emu_cs = 0x22A6; emu_GUI_DrawFilledRectangle();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }
	emu_sp += 10;

	emu_push(emu_cs); emu_push(0x0367); emu_cs = 0x2B6C; f__2B6C_0169_001E_6939();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }
}

uint16 GUI_EditBox(csip32 text, uint16 maxLength, uint16 unknown1, csip32 wcsip, csip32 unknown3, uint16 unknown4)
{
	uint16 oldValue_2598_0000;
	uint16 oldValue_07AE_0000;
	uint16 positionX;
	uint16 maxWidth;
	uint16 textWidth;
	uint16 textLength;
	uint16 returnValue;
	char *t;

	/* Initialize */
	{
		emu_push(0x2);
		emu_push(emu_cs); emu_push(0x0016); emu_cs = 0x29E8; emu_Input_Flags_SetBits();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		emu_push(0x2000);
		emu_push(emu_cs); emu_push(0x0020); emu_cs = 0x29E8; emu_Input_Flags_ClearBits();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		emu_push(0);
		emu_push(emu_cs); emu_push(0x0029); emu_cs = 0x2598; f__2598_0000_0017_EB80();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;
		oldValue_2598_0000 = emu_ax;

		emu_push(unknown1);
		emu_push(emu_cs); emu_push(0x0035); emu_cs = 0x07AE; emu_Unknown_07AE_0000();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;
		oldValue_07AE_0000 = emu_ax;

		returnValue = 0x0;
	}

	positionX = g_global->variable_992D << 3;

	emu_push('W');
	emu_push(emu_cs); emu_push(0x004B); emu_cs = 0x2521; emu_Font_GetCharWidth();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }
	emu_sp += 2;

	textWidth = 0;
	textLength = 0;
	maxWidth = (g_global->variable_992F << 3) - emu_ax - 1;
	t = (char *)emu_get_memorycsip(text);

	/* Calculate the length and width of the current string */
	for (; *t != '\0'; t++) {
		emu_push(*t);
		emu_push(emu_cs); emu_push(0x007D); emu_cs = 0x2521; emu_Font_GetCharWidth();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		textWidth += emu_ax;
		textLength++;

		if (textWidth >= maxWidth) { /* Unresolved jump */ emu_ip = 0x008F; emu_last_cs = 0xB527; emu_last_ip = 0x0084; emu_last_length = 0x0025; emu_last_crc = 0x7FAE; emu_call(); return 0; }
	}
	*t = '\0';

	if ((unknown4 & 0x1) != 0) {
		unknown4 |= 0x4;
	}

	emu_push(emu_cs); emu_push(0x00A6); emu_cs = 0x2B6C; f__2B6C_0137_0020_C73F();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }

	if ((unknown4 & 0x4) != 0) {
		emu_push(emu_cs); emu_push(0x00B2); emu_cs = 0x07AE; emu_Unknown_07AE_0103();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
	}

	/* Draw current text */
	emu_push(0);
	emu_push(g_global->variable_6D59);
	emu_push(g_global->variable_6D5B);
	emu_push(g_global->variable_992B);
	emu_push(positionX);
	emu_push(text.s.cs); emu_push(text.s.ip);
	emu_push(emu_cs); emu_push(0x00CF); emu_cs = 0x10E4; emu_GUI_DrawText_Wrapper();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }
	emu_sp += 14;

	GUI_EditBox_BlinkCursor(positionX + textWidth, false);

	emu_push(emu_cs); emu_push(0x00E8); emu_cs = 0x2B6C; f__2B6C_0169_001E_6939();
	/* Check if this overlay should be reloaded */
	if (emu_cs == 0x3527) { overlay(0x3527, 1); }

	while (true) {
		uint16 keyWidth;
		uint16 key;

		if (unknown3.csip != 0x0) {
			/* Call based on memory/register values */
			emu_push(emu_cs); emu_push(0x00FB);

			emu_ip = unknown3.s.ip;
			emu_cs = unknown3.s.cs;

			switch ((emu_cs << 16) + emu_ip) {
				case 0x34DA003E: overlay(0x34DA, 0); f__B4DA_16CB_001D_31CC(); break;
				case 0x35180066: overlay(0x3518, 0); f__B518_14F2_003E_977C(); break;
				default:
					/* In case we don't know the call point yet, call the dynamic call */
					emu_last_cs = 0xB527; emu_last_ip = 0x00F8; emu_last_length = 0x000B; emu_last_crc = 0xFF42;
					emu_call();
					return 0;
			}
			/* Check if this overlay should be reloaded */
			if (emu_cs == 0x3527) { overlay(0x3527, 1); }

			returnValue = emu_ax;
			if (returnValue != 0) break;
		}

		key = GUI_Widget_HandleEvents((wcsip.csip == 0x0) ? NULL : (Widget *)emu_get_memorycsip(wcsip), wcsip);

		GUI_EditBox_BlinkCursor(positionX + textWidth, false);

		if (key == 0x0) continue;
		if ((key & 0x8000) != 0) {
			returnValue = key;
			break;
		}
		if (key == 0x2B) {
			returnValue = 0x2B;
			break;
		}
		if (key == 0x6E) {
			emu_ip = 0x0164; emu_last_cs = 0xB527; emu_last_ip = 0x015D; emu_last_length = 0x0004; emu_last_crc = 0x3BFB;
			emu_call();
			continue;
		}

		/* Handle backspace */
		if (key == 0x0F) {
			if (textLength == 0) continue;

			GUI_EditBox_BlinkCursor(positionX + textWidth, true);

			emu_push(*(t - 1));
			emu_push(emu_cs); emu_push(0x01A8); emu_cs = 0x2521; emu_Font_GetCharWidth();
			/* Check if this overlay should be reloaded */
			if (emu_cs == 0x3527) { overlay(0x3527, 1); }
			emu_sp += 2;

			textWidth -= emu_ax;
			textLength--;
			*(--t) = '\0';

			GUI_EditBox_BlinkCursor(positionX + textWidth, false);
			continue;
		}

		emu_push(key);
		emu_push(emu_cs); emu_push(0x01CF); emu_cs = 0x29E8; emu_Input_Keyboard_HandleKeys2();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;
		key = emu_ax & 0xFF;

		/* Names can't start with a space, and should be alpha-numeric */
		if (key == 0x20 && textLength == 0) continue;
		if (key < 0x20) continue;
		if (key > 0x7E) continue;

		emu_push(key);
		emu_push(emu_cs); emu_push(0x01FE); emu_cs = 0x2521; emu_Font_GetCharWidth();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;
		keyWidth = emu_ax;

		if (textWidth + keyWidth >= maxWidth) continue;
		if (textLength >= maxLength) continue;

		/* Add char to the text */
		*t = key & 0xFF;
		*(++t) = '\0';
		textLength++;

		emu_push(emu_cs); emu_push(0x0228); emu_cs = 0x2B6C; f__2B6C_0137_0020_C73F();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }

		GUI_EditBox_BlinkCursor(positionX + textWidth, true);

		/* Draw new character */
		emu_push(32);
		emu_push(g_global->variable_6D59);
		emu_push(g_global->variable_6D5B);
		emu_push(g_global->variable_992B);
		emu_push(positionX + textWidth);
		emu_push(text.s.cs); emu_push(text.s.ip + textLength - 1);
		emu_push(emu_cs); emu_push(0x0259); emu_cs = 0x10E4; emu_GUI_DrawText_Wrapper();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 14;

		emu_push(emu_cs); emu_push(0x0261); emu_cs = 0x2B6C; f__2B6C_0169_001E_6939();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }

		textWidth += keyWidth;

		GUI_EditBox_BlinkCursor(positionX + textWidth, false);
	}

	/* Deinitialize */
	{
		emu_push(2);
		emu_push(emu_cs); emu_push(0x0293); emu_cs = 0x29E8; emu_Input_Flags_ClearBits();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		emu_push(0x2000);
		emu_push(emu_cs); emu_push(0x029D); emu_cs = 0x29E8; emu_Input_Flags_SetBits();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		emu_push(oldValue_07AE_0000);
		emu_push(emu_cs); emu_push(0x02A6); emu_cs = 0x07AE; emu_Unknown_07AE_0000();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;

		emu_push(oldValue_2598_0000);
		emu_push(emu_cs); emu_push(0x02AF); emu_cs = 0x2598; f__2598_0000_0017_EB80();
		/* Check if this overlay should be reloaded */
		if (emu_cs == 0x3527) { overlay(0x3527, 1); }
		emu_sp += 2;
	}

	return returnValue;
}