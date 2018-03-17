/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#include "AxonShowPresetNumberAction.h"
#include "AxonFASPresetNumberEvent.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowPresetNumberAction::execute(AxonEvent *event)
{
	AxonTouchScreen::instance()->showAxeFXPresetNumber();
}