/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#include "AxonShowTunerScreenAction.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowTunerScreenAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->showTunerScreen();
}