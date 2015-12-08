/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"

#include "STMPE811QTR.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "SWatch.h"
#include "lcd_add.h"
#include "fonts.h"
#include "debug.h"

/* State variables for generated code */
RT_MODEL_SWatch_T SWatch_state;
char_T errorSig[6];
PrevZCX_SWatch_T ZCSig;
DW_SWatch_T DWork;


boolean_T Btime, Btimeset, Balarm, Bswatch, Bplus, Bminus, Balarmset, isAlarmset;
uint8_T hours=0, minutes=0, seconds=0, tenths=0, mode=0, buzzer=0, submode = 0 ;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * TASK LCD
 */
TASK(TaskLCD)
{
	static TS_STATE lastState;
	TPoint p;

	TS_STATE *ts = IOE_TS_GetState();

	if (!lastState.TouchDetected && ts->TouchDetected)
	{
		p.x = (unsigned int)(ts->X * (-0.09) - (-354));
		p.y = (unsigned int)(ts->Y * (0.063) - 9);

		OnTouch(MyWatchScr, &p);
	}

	lastState = *ts;

	/*
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
	*/
}

void setTimeString(char *watchstr, uint8_T hours, uint8_T minutes, uint8_T seconds, uint8_T tenths, uint8_T mode)
{
	sprintf(watchstr, "%2d:%2d:%2d", hours, minutes, seconds);
}
/*
 * TASK Clock
 */
unsigned char IsUpdateTime()
{
	unsigned char res;
	static unsigned char oh=0, om=0, os=0;
	if (hours!=oh || minutes!=om || seconds!= os)
		res = 1;
	else
		res = 0;
	oh = hours;
	om = minutes;
	os = seconds;
	return res;
}

void UpdateTime()
{
	unsigned char watchstr[20];
	setTimeString(watchstr, hours, minutes, seconds, tenths, mode);

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(Blue);
	//LCD_DrawFullRect(25, 100, 106, 32);

/*	WPrint(&MyWatchScr[TIMESTR], watchstr); */
}

void UpdateMode(unsigned char om, unsigned char m)
{
	switch(om) {
	case 2:
		DrawOff(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOff(&MyWatchScr[BTIMESET]);
		break;
	case 0:
		DrawOff(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOff(&MyWatchScr[BSWATCH]);
		DrawOff(&MyWatchScr[BPLU]);
		DrawOff(&MyWatchScr[BMINUS]);
		break;
	}
	switch(m) {
	case 2:
		DrawOn(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOn(&MyWatchScr[BTIMESET]);
		break;
	case 0:
		DrawOn(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOn(&MyWatchScr[BSWATCH]);
		DrawOn(&MyWatchScr[BPLU]);
		DrawOn(&MyWatchScr[BMINUS]);
		break;
	}
}

void strencode2digit(char *str, int digit)
{
	str[2]=0;
	str[0]=digit/10+'0';
	str[1]=digit%10+'0';
}

void updatealarmbutton()
{
	if(isAlarmset && buzzer == 0)
		DrawOn(&MyWatchScr[BALARMSET]);
	else
		DrawOff(&MyWatchScr[BALARMSET]);

}

void drawalarm()
{
	if(buzzer == 1 && isAlarmset)
		DrawOn(&MyWatchScr[WAKE]);
}

void tenths2digit(char *str, int digit)
{
	str[1]=0;
	str[0]=digit%10+'0';
}

TASK(TaskClock)
{
	unsigned char i;
	static int oldmode=0xFF;
	static int oldsubmode=0xFF;
	static unsigned char oh=99, om=99, os=99, ot=99;
	static unsigned char ob=0xFF, oas=0xFF;
	char tstr[3];
	char astr[2];

	if (IsEvent(TIMEMODE))
		Btime=1;
	else
		Btime=0;

	if (IsEvent(TIMESETMODE))
		Btimeset=1;
	else
		Btimeset=0;

	if (IsEvent(ALARMMODE))
		Balarm=1;
	else
		Balarm=0;

	if (IsEvent(SWATCHMODE))
		Bswatch=1;
	else
		Bswatch=0;

	if (IsEvent(PLUS))
		Bplus=1;
	else
		Bplus=0;

	if (IsEvent(MINUS))
		Bminus=1;
	else
		Bminus=0;

	if (IsEvent(ALARMSET))
		Balarmset=1;
	else
		Balarmset=0;


//	debuginfo(6, button[0], button[2], button[3]);

	SWatch_step(&SWatch_state,
			  Bplus, Bminus, Btime, Btimeset, Balarm, Bswatch, Balarmset,
			  &hours, &minutes, &seconds, &tenths, &mode, &buzzer, &isAlarmset, &submode);

	ClearEvents();
	Bplus=Bminus=Btime=Btimeset=Balarm=Bswatch=Balarmset=0;

	if (hours!=oh || mode!= oldmode || submode != oldsubmode) {
		strencode2digit(tstr, (int)hours);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(40, 75, 62, 48);
		if(submode == 1 && (mode == 1 || mode == 2))
			WPrint(&MyWatchScr[HRSSTR], tstr, true);
		else
			WPrint(&MyWatchScr[HRSSTR], tstr, false);
		if(mode!=1 && mode!=2)
		{
			WPrint(&MyWatchScr[SEP1STR], ":", false);
			WPrint(&MyWatchScr[SEP2STR], ":", false);
		}
		oh=hours;

	}
	if (minutes!=om || mode!= oldmode || submode != oldsubmode) {
		strencode2digit(tstr, (int)minutes);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(110, 75, 62, 48);
		if(submode == 2 && (mode == 1 || mode == 2))
			WPrint(&MyWatchScr[MINSTR], tstr, true);
		else
			WPrint(&MyWatchScr[MINSTR], tstr, false);
		if(mode!=1 && mode!=2)
		{
			WPrint(&MyWatchScr[SEP1STR], ":", false);
			WPrint(&MyWatchScr[SEP2STR], ":", false);
		}
		om=minutes;
	}
	if (seconds!= os) {
		strencode2digit(tstr, (int)seconds);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(180, 75, 62, 48);
		WPrint(&MyWatchScr[SECSTR], tstr, false);
		if(mode!=1 && mode!=2){
			WPrint(&MyWatchScr[SEP1STR], ":", false);
			WPrint(&MyWatchScr[SEP2STR], ":", false);
		}
		os=seconds;
	}

	if (mode == 3 && tenths != ot) {
		tenths2digit(astr, (int)tenths);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(250, 75, 31, 48);
		WPrint(&MyWatchScr[TTSSTR], astr, false);
		WPrint(&MyWatchScr[SEP3STR], ".", false);
		if(mode!=1 && mode!=2){
			WPrint(&MyWatchScr[SEP1STR], ":", false);
			WPrint(&MyWatchScr[SEP2STR], ":", false);
		}
		ot=tenths;
	}
	else if (mode != oldmode)
	{
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(242, 80, 35, 48);

	}

	oldsubmode = submode;

	if (mode != oldmode) {
		UpdateMode(oldmode, mode);
		if(mode == 2 || mode == 1){
			LCD_SetTextColor(Black);
			LCD_SetBackColor(Black);
			LCD_DrawFullRect(172, 75, 115, 48);}
		oldmode = mode;
	}

	if (oas != isAlarmset) {
		updatealarmbutton();
		oas = isAlarmset;
	}

	if (ob != buzzer) {
		drawalarm();
		ob = buzzer;
	}


}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */



/*
 * MAIN TASK
 */
int main(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
  /*Initializes Erika related stuffs*/
	EE_system_init();

	SWatch_state.errorStatus = errorSig;
	SWatch_state.ModelData.prevZCSigState = &ZCSig;
	SWatch_state.ModelData.dwork = &DWork;

  /* init state machine */
	SWatch_initialize(&SWatch_state,
			  &Bplus, &Bminus, &Btime, &Btimeset, &Balarm, &Bswatch, &Balarmset,
			  &hours, &minutes, &seconds, &tenths, &mode, &buzzer, &isAlarmset, &submode);

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/* Initializes LCD and touchscreen */
	IOE_Config();
	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();

//	LCD_Clear(White);

	/* Set the LCD Text size */
//	LCD_SetFont(&Font8x12);
//	Lcd_Touch_Calibration();
	InitTouch(-0.102, 0.0656, -335, 10);

	/* Draw the background */
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(35, 75, 250, 56);



	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmTaskLCD, 10, 100);
	SetRelAlarm(AlarmTaskClock, 10, 100);

  /* Forever loop: background activities (if any) should go here */
	for (;;) { 
	}

}


