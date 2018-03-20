/* originally by Simon Peace
 * Touch Screen Contrast Down Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonContrastDownAction.h"
#include "AxonTouchScreen.h"

void AxonContrastDownAction::execute(AxonEvent *event)
{
	AxonTouchScreen::instance()->contrastDown();
}