/* originally by Simon Peace
 * Touch Screen Contrast Up Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonContrastUpAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonContrastUpAction::execute(AxonEvent *event)
{
	uint8_t tmp = AxonGeneralStorage::instance()->readTouchScreenContrast();
	
	if (tmp < 15)
	{
		tmp++;
	}
	else
	{
		tmp = 0;
	}
	
	AxonGeneralStorage::instance()->writeTouchScreenContrast( tmp );
}