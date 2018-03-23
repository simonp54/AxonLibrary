/* originally by Simon Peace
 * Macro Action Class
 * VERSION 1.0 19/02/2018
 */
#include "AxonMacroAction.h"
#include "Arduino.h"

void AxonMacroAction::add(AxonAction *action)		// add an action to the list
{
	if (_count < _MAX_MACRO_ITEMS)				// if space available
	{
		_list[_count] = action;					// store pointer to action in list structure
		_count++;								// increment the count
	}
}

void AxonMacroAction::remove(AxonAction *action)	// remove an action from the list
{
	bool found = false;								// found? (duh!)
	for( uint8_t i = 0; i < _count; i++ )			// iterate through the list
	{
		if (found)									// if we have already found the item we need to move the remaining items "up the list"
		{
			_list[i] = _list[i+1];					// move the next item into this space
		}
		else if (_list[i] == action)				// if the list item pointer matches the search item pointer
		{
			found = true;							// then we found it
			_list[i] = _list[i+1];					// move the next item into this space
			_count--;								// decrement the count
		}
	}
}

void AxonMacroAction::execute( AxonAction *sender, AxonEvent *event)		// iterate through the actions "executing" their Execute methods
{
	for( uint8_t i = 0; i < _count; i++ )			// as above...
	{
		_list[i]->execute(this, event);
	}
}