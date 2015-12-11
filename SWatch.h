/*
 * SWatch.h
 *
 *  Created on: 08/dic/2015
 *      Author: Rossella
 */

#ifndef SWATCH_H_
#define SWATCH_H_

#include "ee.h"
//------------------------------------------------------
// SIGNALS AND STATES
//------------------------------------------------------
typedef struct SM SM;

typedef void (*Action)(SM *sm);

typedef enum State
{
	TIME_MODE, SRESET, SRUNNING, SPAUSE, SFREEZE,
	TSET_HOURS, TSET_MINUTES,
	ASET_HOURS, ASET_MINUTES
}State;

typedef struct state
{
	State s;
	Action entry;
	Action exit;
}state;


typedef enum Signal
{
	BSTOPWATCH, BTIMESET, BALARM, BTIME, BPLUS, BMINUS, BALARMSET, MAX_SIGNAL
}Signal;

//---------------------------------------------------------
//
//---------------------------------------------------------

typedef struct Timer
{
	EE_UINT8 hours;
	EE_UINT8 minutes;
	EE_UINT8 seconds;
	EE_UINT8 tenths;
}Timer;

typedef struct Tran Tran;


struct SM
{
	state *stateArray;
	Tran  *tranTable;
	state currState;
	EE_UINT8 numSignals;
	EE_UINT8 numStates;
	EE_UINT8 mode;
	EE_UINT8 submode;

	//status variables
	EE_UINT8 Trunning, Srunning;
	//timers
	Timer clockTimer, alarmTimer, sWatchTimer;
	//output timer
	Timer * outTimer;
	//alarm varaibles
	EE_UINT8 isAlarmSet, buzzer;
};


struct Tran
{
	Action action;
	state nextState;
};


//-------------------------------------------------------
//FUNCTIONS
//-------------------------------------------------------

void TimerInit(Timer *t);

void SWatchInit(SM * sm);
void SWatch_step(SM* sm);

void doNothing(SM * sm);
void SWatchTimeMode(SM * sm);
void dispatch(SM * sm, EE_UINT8 const sig);
EE_UINT8 timerCompare(Timer * t1, Timer * t2);

void entryTM(SM * sm);
void entrySRES(SM * sm);
void entrySRUN(SM * sm);
void entrySP(SM * sm);
void entrySF(SM * sm);
void entryTSH(SM * sm);
void entryTSMIN(SM * sm);
void entryASH(SM * sm);
void entryASM(SM * sm);
void entryCH(SM * sm);


void exitTSH(SM * sm);
void exitTSMIN(SM * sm);


void toSwatchMode(SM * sm);
void toTimeSetMode(SM * sm);
void toAlarmMode(SM * sm);
void toTimeMode(SM * sm);
void freeze(SM * sm);
void TincMinutes(SM * sm);
void TdecMinutes(SM * sm);
void TincHours(SM * sm);
void TdecHours(SM * sm);
void AincMinutes(SM * sm);
void AdecMinutes(SM * sm);
void AincHours(SM * sm);
void AdecHours(SM * sm);
void setAlarm(SM * sm);



#endif /* SWATCH_H_ */
