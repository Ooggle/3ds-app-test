// Simple citro2d untextured shape example
#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

#define BOTTOM_SCREEN_WIDTH 320
#define BOTTOM_SCREEN_HEIGHT 240

#define BTN_CLICKED 1
#define BTN_NOT_CLICKED 0

#define BTN_SELECTED 1
#define BTN_NOT_SELECTED 0

struct GuiButton{
	int rectX;
	int rectY;
	int rectW;
	int rectH;
	int selected;
	int clicked;
	char* text[255];
};

void drawButtonOld(int rectX, int rectY, int rectW, int rectH, int clicked) {
	int rectZ = 0;
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
	u32 blurple = C2D_Color32(0x72, 0x89, 0xDA, 0xFF);

	if(clicked) {
		C2D_DrawLine(rectX - 1, rectY - 1, clrBlue, rectX - 1, rectY + rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(rectX - 2, rectY, clrBlue, rectX + rectW + 2, rectY, clrBlue, 4, 1);
		C2D_DrawLine(rectX - 2, rectY + rectH, clrBlue, rectX + rectW + 2, rectY + rectH, clrBlue, 4, 1);
		C2D_DrawLine(rectX + rectW + 1, rectY - 1, clrBlue, rectX + rectW + 1, rectY + rectH + 1, clrBlue, 4, 1);
	} else {
		C2D_DrawLine(rectX - 2, rectY - 1, clrBlue, rectX - 2, rectY + rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(rectX - 2, rectY - 1, clrBlue, rectX + rectW + 2, rectY - 1, clrBlue, 4, 1);
		C2D_DrawLine(rectX - 2, rectY + rectH + 1, clrBlue, rectX + rectW + 2, rectY + rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(rectX + rectW + 2, rectY - 1, clrBlue, rectX + rectW + 2, rectY + rectH + 1, clrBlue, 4, 1);
	}
	C2D_DrawRectSolid(rectX, rectY, rectZ, rectW, rectH, blurple);
}

void drawButton(struct GuiButton button) {
	int rectZ = 0;
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
	u32 blurple = C2D_Color32(0x72, 0x89, 0xDA, 0xFF);
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);

	if(button.clicked) {
		C2D_DrawLine(button.rectX - 1, button.rectY - 1, clrBlue, button.rectX - 1, button.rectY + button.rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX - 2, button.rectY, clrBlue, button.rectX + button.rectW + 2, button.rectY, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX - 2, button.rectY + button.rectH, clrBlue, button.rectX + button.rectW + 2, button.rectY + button.rectH, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX + button.rectW + 1, button.rectY - 1, clrBlue, button.rectX + button.rectW + 1, button.rectY + button.rectH + 1, clrBlue, 4, 1);
	} else if(button.selected) {
		C2D_DrawLine(button.rectX - 2, button.rectY - 1, clrBlue, button.rectX - 2, button.rectY + button.rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX - 2, button.rectY - 1, clrBlue, button.rectX + button.rectW + 2, button.rectY - 1, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX - 2, button.rectY + button.rectH + 1, clrBlue, button.rectX + button.rectW + 2, button.rectY + button.rectH + 1, clrBlue, 4, 1);
		C2D_DrawLine(button.rectX + button.rectW + 2, button.rectY - 1, clrBlue, button.rectX + button.rectW + 2, button.rectY + button.rectH + 1, clrBlue, 4, 1);
	}
	C2D_DrawRectSolid(button.rectX, button.rectY, rectZ, button.rectW, button.rectH, blurple);

	// display text
	C2D_TextBuf myTextBuf = C2D_TextBufNew(15);
	C2D_Text myText;

	C2D_TextParse(&myText, myTextBuf, *button.text);
	
	C2D_TextOptimize(&myText);

	float outWidth = 0;
	float outHeight = 0;
	C2D_TextGetDimensions(&myText, 0.8, 0.8, &outWidth, &outHeight);
	C2D_DrawText(&myText, C2D_WithColor | C2D_AlignCenter, button.rectX + (button.rectW / 2), button.rectY + (button.rectH / 2) - (outHeight / 2), 1, 0.8, 0.8, clrWhite);
}

void clearSelectedButtons(struct GuiButton screenButtons, int count) {

}

void drawButtons(struct GuiButton *screenButtons, int count) {

	u32 kDown = hidKeysHeld();

	for(int i = 0; i < count; i++) {

		// touchscreen check
		if (kDown & KEY_TOUCH) {
			touchPosition screenPos;
			hidTouchRead(&screenPos);
			if((screenPos.px > screenButtons[i].rectX && screenPos.px < screenButtons[i].rectX + screenButtons[i].rectW) &&
			(screenPos.py > screenButtons[i].rectY && screenPos.py < screenButtons[i].rectY + screenButtons[i].rectH)) {

				printf("\x1b[1;1HTouch button: %d    ", i + 1);

				// clearSelectedButtons(screenButtons, 3);
				for(int y = 0; y < count; y++) {
					screenButtons[y].selected = BTN_NOT_SELECTED;
					screenButtons[y].clicked = BTN_NOT_CLICKED;
				}

				screenButtons[i].selected = BTN_SELECTED;
				screenButtons[i].clicked = BTN_CLICKED;
				
			} else {
				for(int y = 0; y < count; y++) {
					screenButtons[y].clicked = BTN_NOT_CLICKED;
				}
			}

			printf("\x1b[3;1HTouch X: %d  ", screenPos.px);
			printf("\x1b[4;1HTouch Y: %d  ", screenPos.py);
			printf("\x1b[5;1HScreen touch: yes");
		} else {
			printf("\x1b[1;1HTouch button: none");
			printf("\x1b[5;1HScreen touch: no ");
			for(int y = 0; y < count; y++) {
				screenButtons[y].clicked = BTN_NOT_CLICKED;
			}
		}

		/* if(kDown & KEY_A) {
			drawButton(screenButtons[i], BTN_SELECTED, BTN_CLICKED);
			//drawButton((BOTTOM_SCREEN_WIDTH /2) - 70, (BOTTOM_SCREEN_HEIGHT /2) - 15, 140, 30, BTN_CLICKED);
		} else {
			drawButton(screenButtons[i], BTN_NOT_SELECTED, BTN_NOT_CLICKED);
			//drawButton((BOTTOM_SCREEN_WIDTH /2) - 70, (BOTTOM_SCREEN_HEIGHT /2) - 15, 140, 30, BTN_NOT_CLICKED);
		} */

		drawButton(screenButtons[i]);
	}
}

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_TOP, NULL);

	// Create screens
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	// Create colors
	
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	/* u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);

	u32 clrTri1 = C2D_Color32(0xFF, 0x15, 0x00, 0xFF);
	u32 clrTri2 = C2D_Color32(0x27, 0x69, 0xE5, 0xFF); */

	u32 blurple = C2D_Color32(0x72, 0x89, 0xDA, 0xFF);

	u32 clrClear = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

	char text1[] = "Install CIA";
	char text2[] = "2nd menu";
	char text3[] = "3rd menu";

	struct GuiButton screenButtons[3] = {
		{(BOTTOM_SCREEN_WIDTH /2) - 70, (BOTTOM_SCREEN_HEIGHT /2) - 60, 140, 30, 1, 0, {text1}},
		{(BOTTOM_SCREEN_WIDTH /2) - 70, (BOTTOM_SCREEN_HEIGHT /2) - 15, 140, 30, 0, 0, {text2}},
		{(BOTTOM_SCREEN_WIDTH /2) - 70, (BOTTOM_SCREEN_HEIGHT /2) + 30, 140, 30, 0, 0, {text3}}
	};

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysHeld();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		/* printf("\x1b[1;1HSimple citro2d example");
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f); */

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bottom, clrClear);
		C2D_SceneBegin(bottom);

		drawButtons(screenButtons, 3);

		C3D_FrameEnd(0);
	}

	/* while(1) {
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysHeld();
		if (kDown & KEY_B)
			break;
	} */

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
