/*
 * SWatch.h
 *
 *  Created on: 08/dic/2015
 *      Author: Rossella
 */

#ifndef SWATCH_H_
#define SWATCH_H_


typedef void (*Action)(SM *sm);

typedef struct state
{
	State s;
	Action entry;
	Action exit;
}state;

typedef enum Signal
{
	BSTOP, BTIMESET, BALARM, BTIME, BPLUS, BMINUS, BALARMSET, MAX_SIGNAL
}Signal;

typedef enum State
{
	TIME_MODE, SRESET, SRUNNING, SPAUSE, SFREEZE,
	TSET_HOURS, TSET_MINUTES,
	ASET_HOURS, ASET_MINUTES
}State;

typedef struct Timer
{
	uint8 hours;
	uint8 minutes;
	uint8 seconds;
	uint8 tenths;
}Timer;

typedef struct Tran
{
	action Action;
	state nextState;
}tran;

typedef struct SM
{
	state const *stateArray;
	Tran const *tranTable;
	state currState;
	uint8 numSignals;
	uint8 numStates;
	uint8 mode;
	uint8 submode;

	//status variables
	boolean Trunning, Srunning;
	//timers
	Timer clockTimer, alarmTimer, sWatchTimer;
	//output timer
	Timer * outTimer;
	//alarm varaibles
	boolean isAlarmSet, buzzer;
}SM;





//-------------------------------------------------------
//FUNCTIONS
//-------------------------------------------------------

void TimerInit(Timer *t);

void SWatchInit(SM * sm);
void SWatchStep(SM* sm);

void doNothing(SM * sm);
void SWatchTimeMode(SM * sm);


void entrySRES(SM * sm);
void entrySRUN(SM * sm);
void entrySP(SM * sm);
void entrySF(SM * sm);
void entryTSH(SM * sm);
void entryTSMIN(SM * sm);
void entryASH(SM * sm);
void entryASM(SM * sm);
void entryCH(SM * sm);

void exitSRES(SM * sm);
void exitSRUN(SM * sm);
void exitSP(SM * sm);
void exitSF(SM * sm);
void exitTSH(SM * sm);
void exitTSMIM(SM * sm);
void exitASH(SM * sm);
void exitASM(SM * sm);
void exitCH(SM * sm);

void toSwatchMode(SM * sm);
void toTimeSetMode(SM * sm);
void toAlarmMode(SM * sm);
void toTimeMode(SM * sm);
void freeze(SM * sm);
void TincMinutes(SM * sm);



#endif /* SWATCH_H_ */
