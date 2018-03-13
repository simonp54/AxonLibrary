/* originally by Simon Peace
 * Midi object wrapping Class
 * VERSION 1.0 08/03/2018
 */
#include "AxonMidiImpl1.h"
#include "MIDI.h"
#include "Arduino.h"

#define DUMMYCLASSNAME		AxonMidiImpl1
#define DUMMYMIDI			MIDI1
#define DUMMYSERIALPORT		Serial2

#define INCLUDE_FOR_MIDI_NETWORK_ONE

#include "AxonMIDIcode.txt"
