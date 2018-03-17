#include "AxonStoreAxeFXSceneNumberAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonStoreAxeFXSceneNumberAction::execute(AxonEvent *event)
{
	AxonHardwareSwitchEvent *tmp = new AxonHardwareSwitchEvent( 0 );

	if (event->sameType(tmp))
	{
		AxonHardwareSwitchEvent *tmp2 = event;
		
		AxonGeneralStorage::instance()->writeAxeFXSceneNumber( tmp2->getSwitchNumber() - 16 );
	}
	
	delete tmp;
}