/* originally by Simon Peace
 * AxeFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonAxeFXPresetUpAction.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonAxeFXPresetUpAction::execute(AxonEvent *event)
{
	uint16_t tmp = AxonGeneralStorage::instance()->readAxeFXPresetNumber();
	
	if (tmp < 767)
	{
		tmp++;
	}
	else
	{
		tmp = 0;
	}
	
	AxonGeneralStorage::instance()->writeAxeFXPresetNumber( tmp );
}