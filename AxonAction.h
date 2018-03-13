/* originally by Simon Peace
 * Base AxonAction Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_ACTION_h
#define AXON_ACTION_h

#include "AxonEvent.h"
#include "Arduino.h"

class AxonAction						// the generic definition of an AxonAction (doesn't ever exist but is the base type for generic coding)
{
	public:
		virtual void execute(AxonEvent *event) = 0;		// pure virtual function definition of the Execute method (aka doesn't exist here and never will)
};

#endif