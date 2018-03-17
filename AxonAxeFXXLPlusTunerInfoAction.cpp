#include "AxonAxeFXXLPlusTunerInfoAction.h"
#include "AxonFASTunerInfoEvent.h"
#include "AxonTouchScreen.h"

void AxonAxeFXXLPlusTunerInfoAction::execute(AxonEvent *event)
{
	AxonFASTunerInfoEvent *tmp = new AxonFASTunerInfoEvent();
	
	if ( event->sameType(tmp) )
	{
		AxonFASTunerInfoEvent *tmp2 = event;
		
		AxonTouchScreen::instance()->setTunerNote( tmp2->getNote() );
		AxonTouchScreen::instance()->setTunerString( tmp2->getString() );
		AxonTouchScreen::instance()->setTunerData( tmp2->getData() );
	}
	
	delete tmp;
}