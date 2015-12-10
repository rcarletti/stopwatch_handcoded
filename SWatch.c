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
	{SRESET, &entrySRES, &exitSRES},
	{SRUNNING, &entrySRUN, &exitSRUN},
	{SPAUSE, &entrySP, &exitSP},
	{SFREEZE, &entrySF, &exitSF},
	{TSET_HOURS, &entryTSH, &exitTSH},
	{TSET_MINUTES, &entryTSMIN, &exitTSMIN},
	{ASET_HOURS, &entryASH, &exitASH},
	{ASET_MINUTES &entryASM, &exitASM},
	{CHECK, &entryCH, &exitCH}
}
Tran const Ttable[MAX_STATE][MAX_SIGNAL] =
{
		{//TIME MODE
				{}
		},
		{//SWATCH MODE
				{}
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
	if(sm->)
}

void doNothing(SM * sm){}


//----------------------------------------------------------
//TRANSITION FUNCTIONS
//----------------------------------------------------------



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
void exitSM(SM * sm){doNothing(sm);}
void exitTSM(SM * sm){sm->Trunning = true;}
void exitAM(SM * sm){doNothing(sm);}
void exitSRES(SM * sm){doNothing(sm);}
void exitSRUN(SM * sm){doNothing(sm);}
void exitSP(SM * sm){doNothing(sm);}
void exitSF(SM * sm){doNothing(sm);}
void exitTSH(SM * sm){doNothing(sm);}
void exitTSMIM(SM * sm){doNothing(sm);}
void exitASH(SM * sm){doNothing(sm);}
void exitASM(SM * sm){doNothing(sm);}
void exitCH(SM * sm){doNothing(sm);}



void tick(Timer * t)
{
	t-tenths++;

	if(t->tenths == 10){t->tenths = 0; t->seconds++;}
	if(t->seconds == 60){t->seconds = 0; t->minutes++;}
	if(t->minutes == 60){t->minutes = 0; t->hours++}
	if(t->hours == 24){t->hours = 0;}
}
