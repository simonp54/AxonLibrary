#include "AxonAFXXLPTunerInfoAction.h"
#include "AxonAFXXLPTunerInfoEvent.h"
#include "AxonTouchScreen.h"

void AxonAFXXLPTunerInfoAction::execute(AxonEvent *event)
{
	AxonAFXXLPTunerInfoEvent *tmp = new AxonAFXXLPTunerInfoEvent();
	
	if ( event->sameType(tmp) )
	{
		AxonAFXXLPTunerInfoEvent *tmp2 = event;
		
		AxonTouchScreen::instance()->setTunerNote( tmp2->getNote() );
		AxonTouchScreen::instance()->setTunerString( tmp2->getString() );
		AxonTouchScreen::instance()->setTunerData( tmp2->getData() );
	}
	
	delete tmp;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}