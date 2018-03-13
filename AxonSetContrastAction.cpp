/* originally by Simon Peace
 * Touch Screen Contrast Action
 * VERSION 1.0 10/03/2018
 */
#include "AxonSetContrastAction.h"
#include "AxonTouchScreen.h"
#include "AxonGeneralStorage.h"
#include "Arduino.h"

void AxonSetContrastAction::execute(AxonEvent *event)
{
	uint8_t tmp = AxonGeneralStorage::instance()->readTouchScreenContrast();
	
	AxonTouchScreen::instance()->setContrast( tmp );
}