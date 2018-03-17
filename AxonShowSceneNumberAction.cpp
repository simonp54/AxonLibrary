#include "AxonShowSceneNumberAction.h"
#include "AxonTouchScreen.h"
#include "Arduino.h"

void AxonShowSceneNumberAction::execute(AxonEvent *event)
{
	AxonTouchScreen::instance()->showAxeFXSceneNumber();
}