/* originally by Simon Peace
 * Touch Screen Contrast Down Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonAFXXLPPresetDownAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonAFXXLPPresetDownAction::execute( AxonAction *sender, AxonEvent *event)
{
	uint16_t tmp = AxonGeneralStorage::instance()->readAFXXLPPresetNumber();
	
	if (tmp > 0)
	{
		tmp--;
	}
	else
	{
		tmp = 767;
	}
	
	AxonGeneralStorage::instance()->writeAFXXLPPresetNumber( tmp );
}