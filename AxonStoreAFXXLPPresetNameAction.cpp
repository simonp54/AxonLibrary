/* originally by Simon Peace
 * AFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonStoreAFXXLPPresetNameAction.h"
#include "AxonAFXXLPPresetNameEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


void AxonStoreAFXXLPPresetNameAction::execute(AxonEvent *event)
{
	AxonAFXXLPPresetNameEvent *tmp = new AxonAFXXLPPresetNameEvent();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
		AxonAFXXLPPresetNameEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAFXXLPPresetName( tmp2->getPresetName() );
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}