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
		void clientDeregister( AxonEventClient *client, AxonEvent *event );
		
		void addToQueue( AxonEvent *event );
		
		void processQueue();
	protected:
		AxonEventManager();
	
	private:
		static AxonEventManager *_instance;
		
		void removeTopQueue();
		
		static const uint8_t _MAX_CLIENT_REGISTRATIONS = 88;
		static const uint16_t _MAX_QUEUE_SIZE = 22;
		
		uint8_t _clientCount = 0;
		AxonEventClient *_clients[_MAX_CLIENT_REGISTRATIONS];
		AxonEvent *_eventFilters[_MAX_CLIENT_REGISTRATIONS];
		
		AxonEvent *_eventList[_MAX_QUEUE_SIZE];
		uint16_t _eventListCount = 0;
		
};

#endif