/*!	\file	Button.h
 	\author Daniel Casini
 	\date	10/03/2014
	\brief	Button handling file for the watch
*/

#ifndef WIDGET_H_
#define WIDGET_H_

#include "Event.h"
#include "Touch.h"
#include "fonts.h"
#include "ee.h"


typedef enum  {
	BACKGROUND, BUTTONICON, TEXT, IMAGE
} WidgetType;

typedef struct {
	const unsigned char *imageon;
	const unsigned char *imageoff;
} Image;

typedef struct {
	const unsigned char *iconp;
	const unsigned char *iconr;
	const Event	         onpress;
} ButtonIcon;

typedef struct {
	sFONT *font;
	unsigned short int	color;
	unsigned short int  color_selected;
} Text;

typedef struct {
	unsigned short int xl;
	unsigned short int yt;
	unsigned short int xw;
	unsigned short int yh;
	WidgetType wt;
	void     *ws;
} Widget;

#define txtinfo(w) ((Text *)((w)->ws))
#define biconinfo(w) ((ButtonIcon *)((w)->ws))
#define imginfo(w) ((Image *)((w)->ws))

unsigned char OnTouch(const Widget ws[], TPoint *press);
unsigned char DrawInit(const Widget ws[]);
unsigned char DrawOn(const Widget *w);
unsigned char DrawOff(const Widget *w);
unsigned char WPrint(const Widget *w, char *s, EE_UINT8 selected);

#endif /* BUTTON_H_ */
