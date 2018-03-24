#include "AxonU2BabyMemoryMapAction.h"
#include "AxonSongSelectMidiEvent.h"
#include "AxonStorage.h"
#include "Arduino.h"

#include "AxonMidi.h"

#define PATCH_COUNT 10
#define CTRL_COUNT 4
#define NAME_LENGTH 17
#define SCENE_MAX 8

struct patch_t {
  char name[NAME_LENGTH];
  byte PC[CTRL_COUNT];
  byte guitar;
  byte capo;
  byte scnLabel[SCENE_MAX];
};

void AxonU2BabyMemoryMapAction::execute( AxonAction *sender, AxonEvent *event)
{
	AxonSongSelectMidiEvent *tmp = new AxonSongSelectMidiEvent();			// switch number doesn't matter for the subsequent check here
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	if (event->sameType(tmp))
	{
#ifdef DEBUG_U2BABY_MEMORY_MAP_ACTION
		Serial.println( F("AxonU2BabyMemoryMapAction::recieved SongSelect event ") );
#endif		
		AxonSongSelectMidiEvent *tmp2 = event;

		if ((tmp2->getSongNumber() >= 0) && (tmp2->getSongNumber() <= 127 ))
		{
			patch_t patch;
	
			AxonStorage::instance()->read( tmp2->getSongNumber() * sizeof(patch_t), &patch, sizeof(patch) );
			for (uint8_t i = 1; i < CTRL_COUNT; i++)
			{
				AxonMidi::instance()->sendPC( 0, i, patch.PC[i] );
			}
		}		
	}
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif

	delete tmp;
}