/* originally by Simon Peace
 * Touch Screen Contrast Up Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonContrastUpAction.h"
#include "AxonTouchScreen.h"

void AxonContrastUpAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->contrastUp();
}