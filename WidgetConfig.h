/*
 * WidgetConfig.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 */

#ifndef WIDGETCONFIG_H_
#define WIDGETCONFIG_H_

#define NUMWIDGETS 16

#define BAKCG 0
#define BTIME 1
#define BTIMESET 2
#define BALARM 3
#define BSWATCH 4
#define BPLU 5
#define BMINUS 6
#define BALARMSET 7
#define WAKE 8
#define HRSSTR 9
#define MINSTR 10
#define SECSTR 11
#define TTSSTR 12
#define SEP1STR 13
#define SEP2STR 14
#define SEP3STR 15



//eventi

#define TIMEMODE 0x01
#define TIMESETMODE 0x02
#define ALARMMODE 0x04
#define SWATCHMODE 0x08
#define PLUS 0x10
#define MINUS 0x20
#define ALARMSET 0x40

extern const Widget MyWatchScr[NUMWIDGETS];

#endif /* WIDGETCONFIG_H_ */
