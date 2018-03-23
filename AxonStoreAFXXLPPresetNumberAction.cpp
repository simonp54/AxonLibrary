/* originally by Simon Peace
 * AFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonStoreAFXXLPPresetNumberAction.h"
#include "AxonAFXXLPPresetNumberEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


void AxonStoreAFXXLPPresetNumberAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonAFXXLPPresetNumberEvent *tmp = new AxonAFXXLPPresetNumberEvent();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
		AxonAFXXLPPresetNumberEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAFXXLPPresetNumber( tmp2->getPresetNumber() );
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}