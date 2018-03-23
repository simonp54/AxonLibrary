/* originally by Simon Peace
 * Show the Tuner Screen
 * VERSION 1.0 10/03/2018
 */
#include "AxonShowPresetNameAction.h"
#include "AxonTouchScreen.h"

void AxonShowPresetNameAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->showAFXXLPPresetName();
}