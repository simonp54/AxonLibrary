/* originally by Simon Peace
 * a wrapper for "keyscanner" driver chip on the Axon
 * VERSION 1.0 28/02/2018
 */

#include "AxonCheckMem.h"

#include "AxonDebugDefines.h"

AxonCheckMem *AxonCheckMem::_instance = 0;

AxonCheckMem *AxonCheckMem::instance()
{
	if (!_instance)
	{
		_instance = new AxonCheckMem();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
//AxonCheckMem::instance()->check();
// cant really do this here LOL
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonCheckMem::AxonCheckMem()
{
	_lastCheckMillis = millis();
}


/*
 *  CALLED BY THE CLIENT TO SERVICE THE KEYBOARD (AS FREQUENTLY AS POSSIBLE)
 *  BUT internally limited to the fastest that seems stable (20ms)
 */
void AxonCheckMem::check()
{
	if ( _lastCheckMillis + _QUICKEST_RECHECK_INTERVAL > millis() )
	{
		return;			// do nothing... its too soon.
	}

/* This function places the current value of the heap and stack pointers in the
   variables. You can call it from any place in your code and save the data for
   outputting or displaying later. This allows you to check at different parts of
   your program flow.
   The stack pointer starts at the top of RAM and grows downwards. The heap pointer
   starts just above the static variables etc. and grows upwards. SP should always
   be larger than HP or you'll be in big trouble! The smaller the gap, the more
   careful you need to be. Julian Gall 6-Feb-2009.
*/

	_stackptr = (uint8_t *)malloc(4);          // use stackptr temporarily
	_heapptr = _stackptr;                     // save value of heap pointer
	free(_stackptr);      // free up the memory again (sets stackptr to 0)
	_stackptr =  (uint8_t *)(SP);           // save value of stack pointer

	if (_heapptr > _heapmax) {_heapmax = _heapptr;}
	if (_heapptr < _heapmin) {_heapmin = _heapptr;}
	if (_stackptr > _stackmax) {_stackmax = _stackptr;}
	if (_stackptr < _stackmin) {_stackmin = _stackptr;}
	
#ifdef DEBUG_OBJECT_CREATE_DESTROY
	Serial.printf( "%d %d %d %d %d %d\n", _heapmax, _heapptr, _heapmin, _stackmax, _stackptr, _stackmin);
#endif
	
	_lastCheckMillis = millis();			// store the "last time" we ran this service routine
}