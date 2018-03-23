/* originally by Simon Peace
 * Macro Action Class
 * VERSION 1.0 19/02/2018
 */
#ifndef AXON_MACROACTION_h
#define AXON_MACROACTION_h

#include "AxonAction.h"
#include "AxonEvent.h"
#include "Arduino.h"

class AxonMacroAction: public AxonAction
{
	public:
		void add(AxonAction *action);						// Add an action to the list (if space) need to resolve whether to "error" if full later
		void remove(AxonAction *action);					// Remove an action from the list.  This is done by pointer comparison
		
		void execute( AxonAction *sender, AxonEvent *event);						// this iterates through the list calling the Execute methods for each embedded action.
	protected:
		static const uint8_t _MAX_MACRO_ITEMS = 30;			// arbitary number of items
		uint8_t _count = 0;									// internal counter
		AxonAction *_list[_MAX_MACRO_ITEMS];				// internal list of pointers to AxonActions
};

#endif