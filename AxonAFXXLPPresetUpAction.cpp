/* originally by Simon Peace
 * AFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonAFXXLPPresetUpAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonAFXXLPPresetUpAction::execute(AxonEvent *event)
{
	uint16_t tmp = AxonGeneralStorage::instance()->readAFXXLPPresetNumber();
	
	if (tmp < 767)
	{
		tmp++;
	}
	else
	{
		tmp = 0;
	}
	
	AxonGeneralStorage::instance()->writeAFXXLPPresetNumber( tmp );
}