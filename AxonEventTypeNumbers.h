//AxonEventTypeNumbers.h

#define AXON_EVENT_TYPE			 									0x0001	// 00000000 00000001
	
	#define AXON_SWITCH_EVENT_TYPE									0x0003	// 00000000 00000011
		#define AXON_HARDWARE_SWITCH_EVENT_TYPE						0x0007	// 00000000 00000111
		#define AXON_SOFTWARE_SWITCH_EVENT_TYPE						0x000B	// 00000000 00001011
	
	#define AXON_MIDI_EVENT_TYPE									0x0005	// 00000000 00000101
		#define AXON_CHANNEL_MIDI_EVENT_TYPE						0x000D	// 00000000 00001101
			#define AXON_CC_MIDI_EVENT_TYPE							0x001D	// 00000000 00011101
			#define AXON_PC_MIDI_EVENT_TYPE							0x002D	// 00000000 00101101
		#define AXON_SYSEX_MIDI_EVENT_TYPE							0x0015	// 00000000 00010101
		#define AXON_SONG_SELECT_MIDI_EVENT_TYPE					0x0025	// 00000000 00100101
		
	#define AXON_FAS_EVENT_TYPE										0x0019	// 00000000 00011001
		#define AXON_FAS_TUNER_INFO_EVENT_TYPE						0x0039	// 00000000 00111001
		#define AXON_FAS_FRONT_PANEL_CHANGE_EVENT_TYPE				0x0059  // 00000000 01011001
		#define AXON_FAS_PRESET_BLOCKS_DATA_EVENT_TYPE				0x0099	// 00000000 10011001
		#define AXON_FAS_PRESET_NUMBER_EVENT_TYPE					0x0119	// 00000001 00011001
		#define AXON_FAS_PRESET_NAME_EVENT_TYPE						0x0219	// 00000010 00011001
		#define AXON_FAS_SCENE_NUMBER_EVENT_TYPE					0x0419	// 00000100 00011001