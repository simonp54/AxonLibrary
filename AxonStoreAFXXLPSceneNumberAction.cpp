#include "AxonStoreAFXXLPSceneNumberAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


void AxonStoreAFXXLPSceneNumberAction::execute(AxonEvent *event)
{
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
		AxonHardwareSwitchEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAFXSceneNumber( tmp2->getSwitchNumber() - 16 );
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}