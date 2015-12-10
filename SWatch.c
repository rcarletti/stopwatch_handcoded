/*
 * SWatch.c
 *
 *  Created on: 08/dic/2015
 *      Author: Rossella
 */

#include "SWatch.h"

#define MAX_STATE 9

state const Sarray[MAX_STATE] =
{
	{TIME_MODE, &entrytm, &exittm},
	{SRESET, &entrySRES, &exitSRES},
	{SRUNNING, &entrySRUN, &exitSRUN},
	{SPAUSE, &entrySP, &exitSP},
	{SFREEZE, &entrySF, &exitSF},
	{TSET_HOURS, &entryTSH, &exitTSH},
	{TSET_MINUTES, &entryTSMIN, &exitTSMIN},
	{ASET_HOURS, &entryASH, &exitASH},
	{ASET_MINUTES &entryASM, &exitASM},
	{CHECK, &entryCH, &exitCH}
};
Tran const Ttable[MAX_STATE][MAX_SIGNAL] =
{
		{//TIME MODE
			{&toSwatchMode,		SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode,		ASET_HOURS},
			{&doNothing, 		TIME_MODE},
			{&doNothing,		TIME_MODE},
			{&setAlarm, 		TIME_MODE}
		},
		{//STOPWATCH RESET
			{&doNothing, 		SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&doNothing, 		SRUNNING},
			{&doNothing,		SRESET},
			{&setAlarm, 		SRESET}
		},
		{//STOPWATCH RUNNING
			{&freeze, 			SFREEZE},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&doNothing, 		SPAUSE},
			{&doNothing,		SRESET},
			{&setAlarm, 		SRUNNING}
		},
		{//STOPWATCH PAUSE
			{&doNothing,		SPAUSE},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&doNothing, 		SRUNNING},
			{&doNothing, 		SRESET},
			{&setAlarm, 		SPAUSE}
		},
		{//STOPWATCH FREEZE
			{&doNothing, 		SRUNNING},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&doNothing, 		SFREEZE},
			{doNothing, 		SFREEZE},
			{&setAlarm, 		SFREEZE}

		},
		{//TIME SET HOURS
			{&toSwatchMode, 	SRESET},
			{&doNothing, 		TSET_MINUTES},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&TincHours, 		TSET_HOURS},
			{&TdecHours,		TSET_HOURS},
			{&setAlarm, 		TSET_HOURS}
		},
		{//TIME SET MINUTES
			{&toSwatchMode,		SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&TincMinutes,		TSET_MINUTES},
			{&TdecMinutes,		TSET_MINUTES},
			{&setAlarm, 		TSET_MINUTES}

		},
		{//ALARM SET HOURS
			{&toSwatchMode,		SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_MINUTES},
			{&toTimeMode, 		TIME_MODE},
			{&AincHours,		ASET_HOURS},
			{&AdecHours,		ASET_HOURS},
			{&setAlarm, 		ASET_HOURS}
		},
		{//ALARM SET MINUTES
			{{&toSwatchMode,	SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&AincMinutes,		ASET_MINUTES},
			{&AdecMinutes,		ASET_MINUTES},
			{&setAlarm, 		ASET_MINUTES}}
		},
};



//----------------------------------------------------
//FUNCTION DEFINITIONS
//----------------------------------------------------

void TimerInit(Timer * t)
{
	t->hours = t->minutes = t->seconds = t->tenths = 0;
}

void SWatchInit(SM * sm)
{
	sm->currentState = TIME_MODE;
	sm->tranTable = &Ttable[0][0];
	sm->stateArray = &Sarray[0];
	sm->numStates = MAX_STATE;
	sm->numSignals = MAX_SIGNAL;

	Timerinit(&(sm->alarmTimer));
	Timerinit(&(sm->clockTimer));
	Timerinit(&(sm->sWatchTimer));

	SWatchTimeMode(sm);

	sm->Srunning = false;
	sm->Trunning = true;
	sm->isAlarmSet = false;
	sm->buzzer = 0;
	sm->mode = 0;
}

void dispatch(SM * sm, uint8 const sig)
{
	Tran const *t = sm->stateTable + sm->numSignals * sm->currentState + sig;
	sm->stateArray[sm->currState].exit;
	t->Action(sm);
	sm->currState = t->state;
	sm->stateArray[sm->currState].entry;
}

void SWatchStep(SM * sm)
{
	if(sm->Trunning) {tick(sm->clockTimer);}
	if(sm->Srunning) {tick(sm->sWatchTimer);}
	if((timerCompare(sm->alarmTimer, sm->clockTimer)) && sm->isAlarmSet)
	{
		sm->buzzer = true;
	}
}

void doNothing(SM * sm){}


//----------------------------------------------------------
//TRANSITION FUNCTIONS
//----------------------------------------------------------

void toSwatchMode(SM * sm)	{sm->mode = 3; sm->outTimer = sm->sWatchTimer; }
void toTimeSetMode(SM * sm) {sm->mode = 1; sm->Trunning = false; sm->submode = 1;}
void toAlarmMode(SM * sm)	{sm->mode = 2; sm->outTimer = sm->alarmTimer; sm->submode = 1;}
void setAlarm(SM * sm)		{sm->isAlarmSet = !sm->isAlarmSet; if(sm->buzzer) sm->buzzer = false;}
void freeze(SM * sm)		{/*??*/}
void toTimeMode(SM * sm)	{sm->mode = 0; sm->outTimer = sm->clockTimer;}
void TincMinutes(SM * sm)	{sm->clockTimer->minutes = (sm->clockTimer->minutes + 1) % 60;}
void TdecMinutes(SM * sm)
{
	sm->clockTimer->minutes = (sm->clockTimer->minutes - 1) % 60;
	if(sm->clockTimer->minutes == 59){sm->clockTimer->minutes = 0;}
}




//----------------------------------------------------------
//ENTRY FUNCTIONS
//----------------------------------------------------------

void entrySRES(SM * sm)
{
	sm->Srunning = false;
	sm->sWatchTimer->hours = sm->sWatchTimer->minutes = sm->sWatchTimer->seconds = sm->sWatchTimer->tenths = 0;
	sm->outTimer = &(sm->sWatchTimer);
}
void entrySRUN(SM * sm){sm->Srunning = true; sm->outTimer = sm->sWatchTimer;}
void entrySP(SM * sm){sm->Srunning = false;}
void entrySF(SM * sm){doNothing(sm);}
void entryTSH(SM *sm){sm->outTimer->hours = sm->clockTimer->hours; sm->submode = 1;}
void entryTSMIN(SM * sm){sm->outTimer->minutes = sm->clockTimer->minutes; sm->submode = 2;}
void entryASH(SM * sm) {sm->outTimer->hours = sm->alarmTimer->hours; sm->submode = 1;}
void entryASM(SM * sm){sm->outTimer->minutes = sm->alarmTimer->minutes; sm->submode = 2;}
void entryCH(SM * sm){doNothing(sm);}

//------------------------------------------------------------
//EXIT FUNCTIONS
//------------------------------------------------------------

void exitTM(SM * sm){doNothing(sm);}
void exitSRES(SM * sm){doNothing(sm);}
void exitSRUN(SM * sm){doNothing(sm);}
void exitSP(SM * sm){doNothing(sm);}
void exitSF(SM * sm){doNothing(sm);}
void exitTSH(SM * sm){sm->Trunning = true;}
void exitTSMIM(SM * sm){sm->Trunning = true;}
void exitASH(SM * sm){doNothing(sm);}
void exitASM(SM * sm){doNothing(sm);}
void exitCH(SM * sm){doNothing(sm);}



void tick(Timer * t)
{
	t-tenths++;

	if(t->tenths == 10){t->tenths = 0; t->seconds++;}
	if(t->seconds == 60){t->seconds = 0; t->minutes++;}
	if(t->minutes == 60){t->minutes = 0; t->hours++;}
	if(t->hours == 24){t->hours = 0;}
}

boolean timerCompare(Timer * t1, Timer * t2)
{
	if(t1->hours != t2->hours || t1->minutes != t2->minutes)
		return false;
	return true;
}
