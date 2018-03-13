/* originally by Simon Peace
 * Touch Screen Contrast Down Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonContrastDownAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonContrastDownAction::execute(AxonEvent *event)
{
	uint8_t tmp = AxonGeneralStorage::instance()->readTouchScreenContrast();
	
	if (tmp > 0)
	{
		tmp--;
	}
	else
	{
		tmp = 15;
	}
	
	AxonGeneralStorage::instance()->writeTouchScreenContrast( tmp );
}