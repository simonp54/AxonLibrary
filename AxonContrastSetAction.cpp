/* originally by Simon Peace
 * Touch Screen Contrast Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonContrastSetAction.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonContrastSetAction::execute(AxonEvent *event)
{
	AxonTouchScreen::instance()->contrastSet( );
}