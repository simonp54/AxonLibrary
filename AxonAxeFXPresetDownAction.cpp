/* originally by Simon Peace
 * Touch Screen Contrast Down Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonAxeFXPresetDownAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonAxeFXPresetDownAction::execute(AxonEvent *event)
{
	uint16_t tmp = AxonGeneralStorage::instance()->readAxeFXPresetNumber();
	
	if (tmp > 0)
	{
		tmp--;
	}
	else
	{
		tmp = 767;
	}
	
	AxonGeneralStorage::instance()->writeAxeFXPresetNumber( tmp );
}