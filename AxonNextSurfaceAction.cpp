/* originally by Simon Peace
 * Touch Screen Contrast Up Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonNextSurfaceAction.h"
#include "AxonSurfaceManager.h"

void AxonNextSurfaceAction::execute( AxonAction *sender, AxonEvent *event)
{
	uint8_t surfaceNumber = AxonSurfaceManager::instance()->getSurfaceNumber();
	
	if (surfaceNumber < AxonSurfaceManager::maxSurfaceItems)
	{
		AxonSurfaceManager::instance()->loadSurface( surfaceNumber + 1);
	}
	else
	{
		AxonSurfaceManager::instance()->loadSurface( 1 );
	}
}