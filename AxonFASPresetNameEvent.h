#ifndef AXONFASPRESETNAMEEVENT_h
#define AXONFASPRESETNAMEEVENT_h

#include "AxonFASEvent.h"
#include "AxonEvent.h"
#include "Arduino.h"

#include "AxonGeneralStorage.h"					// don't like this being the owner of the maximum size stuff...
												// size of a preset name should be an attribute of the data type...
												// need to work on this

class AxonFASPresetNameEvent: public AxonFASEvent
{
	public:
		AxonFASPresetNameEvent( );
		
		void setPresetName( const char *name );
		const char *getPresetName();

		bool exactMatch( AxonEvent *event );
	protected:
	private:
		char _presetName[AxonGeneralStorage::AXEFX_PRESET_NAME_MAXIMUM_SIZE+1];
};

#endif