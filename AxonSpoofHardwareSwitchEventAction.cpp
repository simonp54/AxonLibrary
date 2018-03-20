/* originally by Simon Peace
 * AFX Preset Up Action
 * VERSION 1.0 11/03/2018
 */
#include "AxonSpoofHardwareSwitchEventAction.h"
#include "AxonHardwareSwitchEvent.h"
#include "AxonEventManager.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


void AxonSpoofHardwareSwitchEventAction::execute(AxonEvent *event)
{
	AxonHardwareSwitchEvent *newEvent = new AxonHardwareSwitchEvent( _switchNumber );
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	newEvent->setSwitchState( _switchState );
	
	AxonEventManager::instance()->addToQueue( newEvent );
}