/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#include "AxonShowPresetNumberAction.h"
#include "AxonAFXXLPPresetNumberEvent.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowPresetNumberAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->showAFXXLPPresetNumber();
}