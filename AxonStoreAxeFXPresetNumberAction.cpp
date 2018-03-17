/* originally by Simon Peace
 * AxeFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonStoreAxeFXPresetNumberAction.h"
#include "AxonFASPresetNumberEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonStoreAxeFXPresetNumberAction::execute(AxonEvent *event)
{
	AxonFASPresetNumberEvent *tmp = new AxonFASPresetNumberEvent();

	if (event->sameType(tmp))
	{
		AxonFASPresetNumberEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAxeFXPresetNumber( tmp2->getPresetNumber() );
	}
	
	delete tmp;
}