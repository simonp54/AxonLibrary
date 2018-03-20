/*
 * A singleton class to "route" events between EventClients.  Each client registers interest in specific or group events
 */
 
#include "AxonEventManager.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"


AxonEventManager *AxonEventManager::_instance = 0;

AxonEventManager *AxonEventManager::instance()
{
	if (!_instance)
	{
		_instance = new AxonEventManager();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	}
	return _instance;
}

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonEventManager::AxonEventManager()
{
	_clientCount = 0;
	_eventListCount = 0;
}

void AxonEventManager::clientRegister( AxonEventClient *client, AxonEvent *event )
{
	if (_clientCount < _MAX_CLIENTS)
	{
		_clients[_clientCount] = client;
		_eventFilters[_clientCount] = event;
		_clientCount++;
#ifdef DEBUG_EVENT_MANAGER
		Serial.print( F("AxonEventManager::Registered Client (") );
		Serial.print( _clientCount );
		Serial.println( F(") total clients") );
#endif
	}
}

void AxonEventManager::clientDeregister(AxonEventClient *client)				// find the pointer "match" shuffle the list up and lower the count "if found"
{
	bool found = false;
#ifdef DEBUG_EVENT_MANAGER
	Serial.println( F("AxonEventManager::Deregistering Client ") );
#endif
	for( uint8_t i = 0; i < _clientCount; i++ )
	{
		if (found)
		{
			_clients[i] = _clients[i+1];
			_eventFilters[i] = _eventFilters[i+1];
		}
		else if (_clients[i] == client)
		{
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::  found") );
#endif
			found = true;
			_clients[i] = _clients[i+1];
			_eventFilters[i] = _eventFilters[i+1];
			_clientCount--;
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::  and reduce client count (") );
	Serial.print( _clientCount );
	Serial.println( F(")") );
#endif
		}
	}
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::Registered Clients (") );
	Serial.print( _clientCount );
	Serial.println( F(")") );
#endif
}


void AxonEventManager::clientDeregister(AxonEventClient *client, AxonEvent *event)				// find the pointer "match" shuffle the list up and lower the count "if found"
{
	bool found = false;
#ifdef DEBUG_EVENT_MANAGER
	Serial.println( F("AxonEventManager::Deregistering Client +eventmatching ") );
#endif
	for( uint8_t i = 0; i < _clientCount; i++ )
	{
		if (found)
		{
			_clients[i] = _clients[i+1];
			_eventFilters[i] = _eventFilters[i+1];
		}
		else if ((_clients[i] == client) && (_eventFilters[i] == event))
		{
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::  found") );
#endif
			found = true;
			_clients[i] = _clients[i+1];
			_eventFilters[i] = _eventFilters[i+1];
			_clientCount--;
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::  and reduce client count (") );
	Serial.print( _clientCount );
	Serial.println( F(")") );
#endif
		}
	}
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::Registered Clients (") );
	Serial.print( _clientCount );
	Serial.println( F(")") );
#endif
}

void AxonEventManager::addToQueue( AxonEvent *event )
{
	if (_eventListCount < _MAX_CLIENTS)
	{
#ifdef DEBUG_EVENT_MANAGER
		Serial.print( F("AxonEventManager::adding at index ") );
		Serial.println( _eventListCount );
#endif
		_eventList[_eventListCount] = event;
		_eventListCount++;
	}
	else
	{
		delete event;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_WARNINGS
		Serial.println();
		Serial.println( F("AxonEventManager::UNABLE TO ADD TO QUEUE!") );
		Serial.println();
#endif
	}
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::added event to queue ") );
	Serial.print( F("    total queue size: ") );
	Serial.println( _eventListCount );
#endif
}

void AxonEventManager::removeTopQueue()
{
	if (_eventListCount > 0)
	{
#ifdef DEBUG_EVENT_MANAGER
		Serial.print( F("AxonEventManager::Queue size was (") );
		Serial.print( _eventListCount );
		Serial.println( F(")") );
#endif
		_eventListCount--;
		for( uint8_t i = 0; i < _eventListCount; i++ )
		{
			_eventList[i] = _eventList[i+1];
		}
	}
#ifdef DEBUG_EVENT_MANAGER
	Serial.print( F("AxonEventManager::event Queue size now (") );
	Serial.print( _eventListCount );
	Serial.println( F(")") );
#endif
}

void AxonEventManager::processQueue()
{
	if (_eventListCount > 0)
//	while (_eventListCount > 0)
	{

#ifdef DEBUG_EVENT_MANAGER
		Serial.println();
		Serial.println();
		Serial.println( F("AxonEventManager::processList START") );
#endif
		// process top queue item
		AxonEvent *event = _eventList[0];
		
		for( uint8_t i = 0; i < _clientCount; i++ )
		{
			//if filter matches this clients interest...
			if ( event->exactMatch( _eventFilters[i] ) )
			{
#ifdef DEBUG_EVENT_MANAGER
				Serial.print( F("AxonEventManager::processList - found interested client (") );
				Serial.print( i );
				Serial.println( F(")") );
#endif
				_clients[i]->event( event );
			}
		}
		
		removeTopQueue();

		delete( event );
#ifdef DEBUG_EVENT_MANAGER
		Serial.println( F("AxonEventManager::processList END") );
		Serial.println();
		Serial.println();
#endif
#ifdef DEBUG_METRICS
		Serial.println( _eventListCount );
		Serial.print( F(" ") );
#endif
	}
}