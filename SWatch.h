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

struct SM;

typedef void (*Action)(struct SM *sm);

enum StateID
{
	TIME_MODE, SRESET, SRUNNING, SPAUSE, SFREEZE,
	TSET_HOURS, TSET_MINUTES,
	ASET_HOURS, ASET_MINUTES
};

struct State
{
	enum StateID s;
	Action entry;
	Action exit;
};

enum SignalID
{
	BSTOPWATCH, BTIMESET, BALARM, BTIME, BPLUS, BMINUS, BALARMSET, MAX_SIGNAL
};

//---------------------------------------------------------
// STATE MACHINE STRUCTURES
//---------------------------------------------------------

struct Timer
{
	EE_UINT8 hours;
	EE_UINT8 minutes;
	EE_UINT8 seconds;
	EE_UINT8 tenths;
};


struct Tran;

struct SM
{
	struct State const *stateArray;
	struct Tran  const *tranTable;
	enum StateID currState;
	EE_UINT8 numSignals;
	EE_UINT8 numStates;
	EE_UINT8 mode;
	EE_UINT8 submode;

	//status variables
	EE_UINT8 Trunning, Srunning;
	//timers
	struct Timer clockTimer, alarmTimer, sWatchTimer;
	//output timer
	struct Timer * outTimer;
	//alarm varaibles
	EE_UINT8 isAlarmSet, buzzer;
};


struct Tran
{
	Action action;
	enum StateID nextState;
};


//-------------------------------------------------------
//FUNCTIONS
//-------------------------------------------------------

void TimerInit(struct Timer *t);

void SWatchInit(struct SM * sm);
void SWatch_step(struct SM* sm);
void tick(struct Timer * t);

void doNothing(struct SM * sm);
void SWatchTimeMode(struct SM * sm);
void dispatch(struct SM * sm, EE_UINT8 const sig);
EE_UINT8 timerCompare(struct Timer * t1, struct Timer * t2);

void entryTM(struct SM * sm);
void entrySRES(struct SM * sm);
void entrySRUN(struct SM * sm);
void entrySP(struct SM * sm);
void entrySF(struct SM * sm);
void entryTSH(struct SM * sm);
void entryTSMIN(struct SM * sm);
void entryASH(struct SM * sm);
void entryASM(struct SM * sm);


void exitTSH(struct SM * sm);
void exitTSMIN(struct SM * sm);


void toSwatchMode(struct SM * sm);
void toTimeSetMode(struct SM * sm);
void toAlarmMode(struct SM * sm);
void toTimeMode(struct SM * sm);
void freeze(struct SM * sm);
void TincMinutes(struct SM * sm);
void TdecMinutes(struct SM * sm);
void TincHours(struct SM * sm);
void TdecHours(struct SM * sm);
void AincMinutes(struct SM * sm);
void AdecMinutes(struct SM * sm);
void AincHours(struct SM * sm);
void AdecHours(struct SM * sm);
void setAlarm(struct SM * sm);



#endif /* SWATCH_H_ */
