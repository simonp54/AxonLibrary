/*
 * A singleton class to "route" events between EventClients.  Each client registers interest in specific or group events
 */

#ifndef AXON_EVENTMANAGER_h
#define AXON_EVENTMANAGER_h

#include "AxonEventClient.h"
#include "AxonEvent.h"

class AxonEventClient;

class AxonEventManager
{
	public:
		static AxonEventManager *instance();				// singleton
	
		void clientRegister( AxonEventClient *client, AxonEvent *event );
		void clientDeregister( AxonEventClient *client );
		
		void addToQueue( AxonEvent *event );
		
		void processQueue();
	protected:
		AxonEventManager();
	
	private:
		static AxonEventManager *_instance;
		
		void removeTopQueue();
		
		static const uint8_t _MAX_CLIENTS = 255;
		
		uint8_t _clientCount = 0;
		AxonEventClient *_clients[_MAX_CLIENTS];
		AxonEvent *_eventFilters[_MAX_CLIENTS];
		
		AxonEvent *_eventList[_MAX_CLIENTS];
		uint8_t _eventListCount = 0;
		
};

#endif