#include "AxonShowSceneNumberAction.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowSceneNumberAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonTouchScreen::instance()->showAFXSceneNumber();
}