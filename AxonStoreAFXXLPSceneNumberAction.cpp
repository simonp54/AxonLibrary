#include "AxonStoreAFXXLPSceneNumberAction.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


void AxonStoreAFXXLPSceneNumberAction::execute(AxonEvent *event)
{
	AxonAFXXLPSceneNumberEvent *tmp = new AxonAFXXLPSceneNumberEvent( );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
		AxonAFXXLPSceneNumberEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAFXSceneNumber( tmp2->getSceneNumber() );
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}