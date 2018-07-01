/* originally by Simon Peace
 * Previous Surface Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonPreviousSurfaceAction.h"
#include "AxonSurfaceManager.h"

void AxonPreviousSurfaceAction::execute( AxonAction *sender, AxonEvent *event)
{
	uint8_t surfaceNumber = AxonSurfaceManager::instance()->getSurfaceNumber();
	
	if (surfaceNumber > 1)
	{
		AxonSurfaceManager::instance()->qSurface( surfaceNumber - 1);
	}
	else
	{
		AxonSurfaceManager::instance()->qSurface( AxonSurfaceManager::maxSurfaceItems );
	}
}