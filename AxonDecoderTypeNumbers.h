//AxonDecoderTypeNumbers.h

#define AXON_DECODER		 													0x0001	// 00000000 00000001

	#define AXON_SYSEX_DECODER													0x0003	// 00000000 00000011

		#define AXON_FAS_MANUFACTURER_DECODER									0x0007	// 00000000 00000111

			#define AXON_AXEFX_XL_PLUS_MODEL_DECODER							0x000F	// 00000000 00001111

				#define AXON_AXEFX_XL_PLUS_CHECKSUM_DECODER        			0x001F  // 00000000 00011111
					#define AXON_AXEFX_XL_PLUS_FRONT_PANEL_CHANGE_DECODER		0x003F  // 00000000 00111111
					#define AXON_AXEFX_XL_PLUS_GET_PRESET_NAME_DECODER			0x005F	// 00000000 01011111
					#define AXON_AXEFX_XL_PLUS_PRESET_NUMBER_DECODER			0x009F  // 00000000 10011111
					#define AXON_AXEFX_XL_PLUS_PRESET_NAME_DECODER				0x011F	// 00000001 00011111
					#define AXON_AXEFX_XL_PLUS_SCENE_NUMBER_DECODER			0x021F	// 00000010 00011111
					
				#define AXON_AXEFX_XL_PLUS_TUNER_INFO_DECODER					0x002F	// 00000000 00101111
				#define AXON_AXEFX_XL_PLUS_PRESET_BLOCKS_DATA_DECODER			0x004F	// 00000000 01001111
				
				
				