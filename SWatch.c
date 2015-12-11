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
	{TIME_MODE, &entryTM, &doNothing},
	{SRESET, &entrySRES, &doNothing},
	{SRUNNING, &entrySRUN, &doNothing},
	{SPAUSE, &entrySP, &doNothing},
	{SFREEZE, &entrySF, &doNothing},
	{TSET_HOURS, &entryTSH, &exitTSH},
	{TSET_MINUTES, &entryTSMIN, &exitTSMIN},
	{ASET_HOURS, &entryASH, &doNothing},
	{ASET_MINUTES, &entryASM, &doNothing},
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
			{&toSwatchMode,	SRESET},
			{&toTimeSetMode, 	TSET_HOURS},
			{&toAlarmMode, 		ASET_HOURS},
			{&toTimeMode, 		TIME_MODE},
			{&AincMinutes,		ASET_MINUTES},
			{&AdecMinutes,		ASET_MINUTES},
			{&setAlarm, 		ASET_MINUTES}
		}
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
	sm->currState = Sarray[TIME_MODE];
	sm->tranTable = &Ttable[0][0];
	sm->stateArray = &Sarray[0];
	sm->numStates = MAX_STATE;
	sm->numSignals = MAX_SIGNAL;

	TimerInit(&(sm->alarmTimer));
	TimerInit(&(sm->clockTimer));
	TimerInit(&(sm->sWatchTimer));

	toTimeMode(sm);

	sm->Srunning = 0;
	sm->Trunning = 1;
	sm->isAlarmSet = 0;
	sm->buzzer = 0;
	sm->mode = 0;
}

void dispatch(SM * sm, EE_UINT8 const sig)
{
	Tran const * t = sm->tranTable + sm->numSignals * sm->currState.s + sig;
	sm->stateArray[sm->currState.s].exit;
	t->action(sm);
	sm->currState = t->nextState;
	sm->stateArray[sm->currState.s].entry;
}

void SWatch_step(SM * sm)
{
	if(sm->Trunning) {tick(sm->clockTimer);}
	if(sm->Srunning) {tick(sm->sWatchTimer);}
	if((timerCompare(&sm->alarmTimer, &sm->clockTimer) == 1) && sm->isAlarmSet)
	{
		sm->buzzer = 1;
	}
}

void doNothing(SM * sm){}


//----------------------------------------------------------
//TRANSITION FUNCTIONS
//----------------------------------------------------------

void toSwatchMode(SM * sm)	{sm->mode = 3; sm->outTimer = &(sm->sWatchTimer); }
void toTimeSetMode(SM * sm) {sm->mode = 1; sm->Trunning = 0; sm->submode = 1;}
void toAlarmMode(SM * sm)	{sm->mode = 2; sm->outTimer = &(sm->alarmTimer); sm->submode = 1;}
void setAlarm(SM * sm)		{sm->isAlarmSet = !sm->isAlarmSet; if(sm->buzzer) sm->buzzer = 0;}
void freeze(SM * sm)		{/*??*/}
void toTimeMode(SM * sm)	{sm->mode = 0; sm->outTimer = &(sm->clockTimer);}
void TincMinutes(SM * sm)	{sm->clockTimer.minutes = (sm->clockTimer.minutes + 1) % 60;}
void TdecMinutes(SM * sm)
{
	sm->clockTimer.minutes = sm->clockTimer.minutes - 1;
	if(sm->clockTimer.minutes < 0){sm->clockTimer.minutes = 59;}
}
void TincHours(SM * sm)		{sm->clockTimer.hours = (sm->clockTimer.hours + 1) % 24;}
void TdecHours(SM * sm)
{
	sm->clockTimer.hours -= 1;
	if(sm->clockTimer.hours < 0) {sm->clockTimer.hours = 24;}
}
void AincMinutes(SM * sm)	{sm->alarmTimer.minutes = (sm->alarmTimer.minutes + 1) % 60;}
void AdecMinutes(SM * sm)
{
	sm->alarmTimer.minutes = sm->alarmTimer.minutes - 1;
	if(sm->alarmTimer.minutes < 0){sm->alarmTimer.minutes = 59;}
}
void AincHours(SM * sm)		{sm->alarmTimer.hours = (sm->alarmTimer.hours + 1) % 24;}
void AdecHours(SM * sm)
{
	sm->alarmTimer.hours -= 1;
	if(sm->alarmTimer.hours < 0) {sm->alarmTimer.hours = 24;}
}




//----------------------------------------------------------
//ENTRY FUNCTIONS
//----------------------------------------------------------
void entryTM(SM * sm){sm->mode = 0; sm->outTimer = &(sm->clockTimer);}
void entrySRES(SM * sm)
{
	sm->Srunning = 0;
	sm->sWatchTimer.hours = sm->sWatchTimer.minutes = sm->sWatchTimer.seconds = sm->sWatchTimer.tenths = 0;
	sm->outTimer = &(sm->sWatchTimer);
}
void entrySRUN(SM * sm)	{sm->Srunning = 1; sm->outTimer = &(sm->sWatchTimer);}
void entrySP(SM * sm)	{sm->Srunning = 0;}
void entrySF(SM * sm)	{doNothing(sm);}
void entryTSH(SM * sm)	{sm->outTimer->hours = sm->clockTimer.hours; sm->submode = 1;}
void entryTSMIN(SM * sm){sm->outTimer->minutes = sm->clockTimer.minutes; sm->submode = 2;}
void entryASH(SM * sm) 	{sm->outTimer->hours = sm->alarmTimer.hours; sm->submode = 1;}
void entryASM(SM * sm)	{sm->outTimer->minutes = sm->alarmTimer.minutes; sm->submode = 2;}
void entryCH(SM * sm)	{doNothing(sm);}

//------------------------------------------------------------
//EXIT FUNCTIONS
//------------------------------------------------------------


void exitTSH(SM * sm){sm->Trunning = 1;}
void exitTSMIN(SM * sm){sm->Trunning = 1;}



void tick(Timer * t)
{
	t->tenths++;

	if(t->tenths == 10){t->tenths = 0; t->seconds++;}
	if(t->seconds == 60){t->seconds = 0; t->minutes++;}
	if(t->minutes == 60){t->minutes = 0; t->hours++;}
	if(t->hours == 24){t->hours = 0;}
}

EE_UINT8 timerCompare(Timer * t1, Timer * t2)
{
	if(t1->hours != t2->hours || t1->minutes != t2->minutes)
		return 0;
	return 1;
}
