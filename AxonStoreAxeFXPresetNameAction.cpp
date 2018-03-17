/* originally by Simon Peace
 * AxeFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonStoreAxeFXPresetNameAction.h"
#include "AxonFASPresetNameEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonStoreAxeFXPresetNameAction::execute(AxonEvent *event)
{
	AxonFASPresetNameEvent *tmp = new AxonFASPresetNameEvent();

	if (event->sameType(tmp))
	{
		AxonFASPresetNameEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAxeFXPresetName( tmp2->getPresetName() );
	}
	
	delete tmp;
}