#ifndef AXON_AXEFXSYSEXEVENTCLIENT_h
#define AXON_AXEFXSYSEXEVENTCLIENT_h

#include "AxonEventClient.h"
#include "AxonAction.h"
#include "AxonEvent.h"


class AxonAxeFXSysExEventClient : public AxonEventClient
{
	public:
		void onFrontPanelChangeRxd( AxonAction *action ) { _onFrontPanelChangeRxdAction = action; }
		void onPresetNumberRxd( AxonAction *action ) { _onPresetNumberRxdAction = action; }
		void onPresetNameRxd( AxonAction *action ) { _onPresetNameRxdAction = action; }
		void onSceneNumberRxd( AxonAction *action ) { _onSceneNumberRxdAction = action; }
		void onPresetBlocksDataRxd( AxonAction *action ) { _onPresetDataBlocksDataRxdAction = action; }
		void onTunerInfoRxd( AxonAction *action ) { _onTunerInfoRxdAction = action; }
		
		virtual void event( AxonEvent *event );
		
	private:
		AxonAction *_onFrontPanelChangeRxdAction = 0;
		AxonAction *_onPresetNumberRxdAction = 0;
		AxonAction *_onPresetNameRxdAction = 0;
		AxonAction *_onSceneNumberRxdAction = 0;
		AxonAction *_onPresetDataBlocksDataRxdAction = 0;
		AxonAction *_onTunerInfoRxdAction = 0;
};

#endif