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
	
		void onTunerInfoRxd( AxonAction *action )			{ _AFXXLPTunerInfoDecoder->onSuccess( action ); 			}
		void onFrontPanelChangeRxd( AxonAction *action )	{ _AFXXLPFrontPanelChangeDecoder->onSuccess( action );		}
		void onPresetBlocksDataRxd( AxonAction *action )	{ _AFXXLPPresetBlocksDataDecoder->onSuccess( action ); 		}
		void onPresetNumberRxd( AxonAction *action )		{ _AFXXLPPresetNumberDecoder->onSuccess( action ); 			}
		void onPresetNameRxd( AxonAction *action )			{ _AFXXLPPresetNameDecoder->onSuccess( action ); 			}
		void onSceneNumberRxd( AxonAction *action )			{ _AFXXLPSceneNumberDecoder->onSuccess( action ); 			}
		void onSceneRxd( AxonAction *action )				{ _AFXXLPSceneNumberDecoder->onSceneRxd( action ); 	}
		
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