#ifndef AXON_AXEFX_XL_PLUS_TUNER_INFO_ACTION_h
#define AXON_AXEFX_XL_PLUS_TUNER_INFO_ACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"

class AxonAxeFXXLPlusTunerInfoAction: public AxonAction
{
	public:
		void execute(AxonEvent *event);									// the execute method
	protected:
};

#endif