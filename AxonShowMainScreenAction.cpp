/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#include "AxonShowMainScreenAction.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowMainScreenAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->showMainScreen();
}