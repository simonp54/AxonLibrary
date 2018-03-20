#ifndef AXON_AXEFXSYSEXEVENTCLIENT_h
#define AXON_AXEFXSYSEXEVENTCLIENT_h

#include "AxonEventClient.h"
#include "AxonAction.h"
#include "AxonEvent.h"
#include "AxonSysExMidiEvent.h"

#include "AxonAFXXLPTunerInfoDecoder.h"
#include "AxonAFXXLPFrontPanelChangeDecoder.h"
#include "AxonAFXXLPPresetBlocksDataDecoder.h"
#include "AxonAFXXLPPresetNumberDecoder.h"
#include "AxonAFXXLPPresetNameDecoder.h"
#include "AxonAFXXLPSceneNumberDecoder.h"


class AxonAFXXLPSysExEventClient : public AxonEventClient
{
	public:
		AxonAFXXLPSysExEventClient();
		~AxonAFXXLPSysExEventClient();
	
		void onTunerInfoRxd( AxonAction *action )			{ _AFXXLPTunerInfoDecoder->onSuccess( action ); 		}
		void onFrontPanelChangeRxd( AxonAction *action )	{ _AFXXLPFrontPanelChangeDecoder->onSuccess( action );	}
		void onPresetBlocksDataRxd( AxonAction *action )	{ _AFXXLPPresetBlocksDataDecoder->onSuccess( action ); 	}
		void onPresetNumberRxd( AxonAction *action )		{ _AFXXLPPresetNumberDecoder->onSuccess( action ); 		}
		void onPresetNameRxd( AxonAction *action )			{ _AFXXLPPresetNameDecoder->onSuccess( action ); 		}
		void onSceneNumberRxd( AxonAction *action )			{ _AFXXLPSceneNumberDecoder->onSuccess( action ); 		}
		void onScene1Rxd( AxonAction *action )				{ _AFXXLPSceneNumberDecoder->onScene1Rxd( action ); 	}
		void onScene2Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene2Rxd( action ); 	}
		void onScene3Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene3Rxd( action ); 	}
		void onScene4Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene4Rxd( action ); 	}
		void onScene5Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene5Rxd( action ); 	}
		void onScene6Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene6Rxd( action ); 	}
		void onScene7Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene7Rxd( action ); 	}
		void onScene8Rxd( AxonAction *action ) 				{ _AFXXLPSceneNumberDecoder->onScene8Rxd( action ); 	}
		
		virtual void event( AxonEvent *event );
		
	private:
		AxonSysExMidiEvent *_sysExMidiEvent = 0;

		AxonAFXXLPTunerInfoDecoder *_AFXXLPTunerInfoDecoder = 0;
		AxonAFXXLPFrontPanelChangeDecoder *_AFXXLPFrontPanelChangeDecoder = 0;
		AxonAFXXLPPresetBlocksDataDecoder *_AFXXLPPresetBlocksDataDecoder = 0;
		AxonAFXXLPPresetNumberDecoder *_AFXXLPPresetNumberDecoder = 0;
		AxonAFXXLPPresetNameDecoder *_AFXXLPPresetNameDecoder = 0;
		AxonAFXXLPSceneNumberDecoder *_AFXXLPSceneNumberDecoder = 0;
};

#endif