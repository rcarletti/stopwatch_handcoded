/*
 * SWatch.h
 *
 *  Created on: 08/dic/2015
 *      Author: Rossella
 */

#ifndef SWATCH_H_
#define SWATCH_H_


typedef enum Signal
{
	BSTOP, BTIMESET, BALARM, BTIME, BPLUS, BMINUS, BALARMSET, MAX_SIGNAL
}Signal;

typedef enum State
{
	TIME_MODE, SWATCH_MODE, TIMESET_MODE, ALARM_MODE,
	SRESET, SRUNNING, SPAUSE, SFREEZE,
	TSET_HOURS, TSET_MINUTES,
	ASET_HOURS, ASET_MINUTES,
	CHECK
};

typedef struct Timer
{
	uint8 hours;
	uint8 minutes;
	uint8 seconds;
	uint8 tenths;
}Timer;

typedef struct SM
{
	State currentState;
	Tran const *stateTable;
	uint8 numSignals;
	uint8 numStates;

	//status variables
	uint8 Trunning, Srunning;
	//timers
	Timer clockTimer, alarmTimer, sWatchTimer;
	//output timer
	Timer * outTimer;
	//alarm varaibles
	boolean isAlarmSet, buzzer;
}SM;

typedef void (*Action)(SM *sm);

struct Tran
{
	action Action;
	uint8 nextState;
};


//-------------------------------------------------------
//FUNCTIONS
//-------------------------------------------------------

void TimerInit(Timer *t);

void SWatchInit(SM * sm);
void SWatchStep(SM* me);




#endif /* SWATCH_H_ */
