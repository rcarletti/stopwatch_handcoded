/*
 * WidgetConfig.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "Widget.h"
#include "WidgetConfig.h"
#include "pictures.h"
#include <stdio.h>
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"

ButtonIcon buttontime = {
		icontime_on, icontime_off, TIMEMODE
};

ButtonIcon buttontimeset = {
		icontimeset_on, icontimeset_off, TIMESETMODE
};

ButtonIcon buttonalarm = {
		iconalarm_on, iconalarm_off, ALARMMODE
};

ButtonIcon buttonswatch = {
		iconswatch_on, iconswatch_off, SWATCHMODE
};

ButtonIcon buttonplus = {
		iconstart, iconplus, PLUS
};

ButtonIcon buttonminus = {
		iconreset, iconminus, MINUS
};

ButtonIcon buttonalarmset = {
		iconalarmon, iconalarmoff, ALARMSET
};


Text txt = {
		&Font32x48, White, Cyan
};

Image backg = {
	ImageBuffer, ImageBuffer
};

Image wake_up = {
	iconwakeup, 0
};

const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{0, 0, 80, 55, BUTTONICON, (void *)&buttontime},
		{80, 0, 80, 55, BUTTONICON, (void *)&buttontimeset},
		{160, 0, 80, 55, BUTTONICON, (void *)&buttonalarm},
		{240, 0, 80, 55, BUTTONICON, (void *)&buttonswatch},
		{25, 158, 70, 46, BUTTONICON, (void *)&buttonplus},
		{225, 158, 70, 46, BUTTONICON, (void *)&buttonminus},
		{125, 158, 70, 46, BUTTONICON, (void *)&buttonalarmset},
		{125, 158, 70, 46, IMAGE, (void *)&wake_up},
//		{26, 76, 100, 32, RECTANGLE, (void *)&rectangle}
		{40, 80, 40, 40, TEXT, (void *)&txt},
		{110, 80, 40, 40, TEXT, (void *)&txt},
		{180, 80, 40, 40, TEXT, (void *)&txt},
		{250, 80, 20, 20, TEXT, (void *)&txt},
		{91, 80, 40, 40, TEXT, (void *)&txt},
		{160, 80, 40, 40, TEXT, (void *)&txt},
		{229, 80, 40, 40, TEXT, (void *)&txt}
};

