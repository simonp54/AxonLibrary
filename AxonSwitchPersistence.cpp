#include "AxonSwitchPersistence.h"
#include "AxonStorage.h"



#include "AxonContrastDownAction.h"
#include "AxonContrastSetAction.h"
#include "AxonContrastUpAction.h"
#include "AxonLabelDisplayAction.h"
#include "AxonLatchingSwitchAction.h"
#include "AxonMacroAction.h"
#include "AxonMomentarySwitchAction.h"
#include "AxonRadioSwitchAction.h"
#include "AxonRadioSwitchGroupAction.h"
#include "AxonShowMainScreenAction.h"
#include "AxonU2BabyMemoryMapAction.h"

#include "AxonSendMidiCCAction.h"
#include "AxonSendMidiFixedCCAction.h"
#include "AxonSendMidiPCAction.h"

#include "AxonAFXXLPPresetBlocksDataRequestAction.h"
#include "AxonAFXXLPPresetDownAction.h"
#include "AxonAFXXLPPresetNameRequestAction.h"
#include "AxonAFXXLPPresetNumberRequestAction.h"
#include "AxonAFXXLPPresetUpAction.h"
#include "AxonAFXXLPSceneNumberRequestAction.h"
#include "AxonAFXXLPSysExAction.h"
#include "AxonAFXXLPTunerInfoAction.h"
#include "AxonShowPresetNameAction.h"
#include "AxonShowPresetNumberAction.h"
#include "AxonShowSceneNumberAction.h"
#include "AxonShowTunerScreenAction.h"
#include "AxonStoreAFXXLPPresetNameAction.h"
#include "AxonStoreAFXXLPPresetNumberAction.h"
#include "AxonStoreAFXXLPSceneNumberAction.h"



#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

/*
 *  CONSTRUCTOR FOR CLASS
 */
AxonSwitchPersistence::AxonSwitchPersistence()
{
//	Serial.println( F("AxonSwitchPersistence::ctor") );
}

uint32_t AxonSwitchPersistence::getSize()
{
//	Serial.print( F("AxonSwitchPersistence::getSize=") );
//	Serial.println( _size );
	return _size;
}

void AxonSwitchPersistence::format()
{
	Serial.println( F("AxonSwitchPersistence::format") );
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("  from address 0x") );
		Serial.print( _baseAddress, HEX );
		Serial.print( F(" filling with 0x00 for 0x") );
		Serial.print( getSize(), HEX );
		Serial.println( F(" bytes") );
#endif
		
		// set my stuff to zeros
		AxonStorage::instance()->format( _baseAddress, 0x00, getSize() );
	}
}

void AxonSwitchPersistence::setBaseAddress( uint32_t baseAddress )
{
	_baseAddress = baseAddress;
	_contextOK = true;
}

void AxonSwitchPersistence::defineLogic( uint8_t logicType )
{
	if ( _contextOK )
	{
		// CHECK THE LOGIC TYPE!
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSwitchPersistence::defineLogic at ") );
		Serial.println( _baseAddress, HEX );
#endif
		AxonStorage::instance()->write( _baseAddress, logicType );
#ifdef DEBUG_SURFACES
Serial.print("writing logictype=");
Serial.println( logicType );
#endif
	}
	else
	{
		Serial.println( F("AxonSwitchPersistence::defineLogic - baseAddress NOT SET") );
	}
}

void AxonSwitchPersistence::defineAction( uint8_t type, uint8_t param1 = 0x00, uint8_t param2 = 0x00, uint8_t param3 = 0x00, uint8_t param4 = 0x00 )
{
	if ( _contextOK )
	{
		if ( _actionCount < _maxActionsPerSwitch )
		{
			// CHECK TYPES AND PARAMS ETC...
#ifdef DEBUG_SURFACES
			Serial.print( F("AxonSwitchPersistence::defineAction at ") );
			Serial.println( _baseAddress + (_actionCount * sizeof(_actionMap)) + sizeof(_logicType), HEX );
#endif
			_actionMap.type = type;
			_actionMap.param1 = param1;
			_actionMap.param2 = param2;
			_actionMap.param3 = param3;
			_actionMap.param4 = param4;
			
			AxonStorage::instance()->write( _baseAddress + (_actionCount * sizeof(_actionMap)) + sizeof(_logicType), &_actionMap, sizeof(_actionMap) );
			_actionCount++;
		}
		else
		{
			Serial.println( F("AxonSwitchPersistence::defineAction NO SPACE for ACTION") );
		}
	}
	else
	{
		Serial.println( F("AxonSwitchPersistence::defineAction - baseAddress NOT SET") );
	}
}

void AxonSwitchPersistence::build()
{
	if (_contextOK)
	{
#ifdef DEBUG_SURFACES
		Serial.print( F("AxonSwitchPersistence::build from ") );
		Serial.println( _baseAddress, HEX );
#endif
		
		buildLogic();

		buildActions();
	}
	else
	{
		Serial.println( F("AxonSwitchPersistence::build - baseAddress NOT SET") );
	}
}



bool AxonSwitchPersistence::buildLogic()
{
#ifdef DEBUG_SURFACES
	Serial.println( F("AxonSwitchPersistence::buildLogic") );
#endif
	AxonStorage::instance()->read( _baseAddress, &_logicType, sizeof(_logicType) );

	if (_logic)
	{
#ifdef DEBUG_SURFACES
Serial.println(" clearing up old logic");
#endif
		delete _logic;
	}				// if _logic already points somewhere, then we need to delete that and start again

#ifdef DEBUG_SURFACES
Serial.print("_logicType = ");
Serial.println(_logicType);
#endif
	switch (_logicType)
	{
		case 0x00:
			Serial.println( F(" ERROR: _logicType not specified") );
			return true;
			break;
		case AxonLatchingSwitchAction_t:
			_logic = new AxonLatchingSwitchAction();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			break;
		case AxonMomentarySwitchAction_t:
		_logic = new AxonMomentarySwitchAction();		
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		break;
//		case AxonRadioSwitchAction_t:
//			_logic = new AxonRadioSwitchAction();
//			break;
		default:
			Serial.println( F(" ERROR: _logicType not supported") );
			return false;
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			break;
	}
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
#ifdef DEBUG_SURFACES
Serial.println("logic created");
#endif
	return true;
}

bool AxonSwitchPersistence::buildActions()
{		
#ifdef DEBUG_SURFACES
	Serial.println( F("AxonSwitchPersistence::buildActions") );
#endif
	uint32_t offset = sizeof( _logicType );

	for( uint8_t i = 0; i < _maxActionsPerSwitch; i++ )
	{
		AxonStorage::instance()->read( _baseAddress + offset, &_actionMap, sizeof(_actionMap) );
		offset += sizeof( _actionMap );

		if (_actionMap.type == 0x00) { break; }

		if ( i < _maxActionsPerSwitch )
		{
			if ( _actionList[i] )
			{
#ifdef DEBUG_SURFACES
Serial.println("   clearing up old action");
#endif
				delete _actionList[i];
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			}
			
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			switch ((_actionMap.type & _actionMask))			// gives us the type but not where to connect it
			{
				case 0x00: Serial.println( F("   ERROR: _actionMap.type not specified") ); return true; break;

				case AxonContrastDownAction_t:					_actionList[i] = new AxonContrastDownAction();																					break;
				case AxonContrastSetAction_t:					_actionList[i] = new AxonContrastSetAction();																					break;
				case AxonContrastUpAction_t:					_actionList[i] = new AxonContrastUpAction();																					break;
				case AxonLabelDisplayAction_t:					_actionList[i] = new AxonLabelDisplayAction(_actionMap.param1, _actionMap.param2, _actionMap.param3, _actionMap.param4 );		break;
				case AxonLatchingSwitchAction_t:				_actionList[i] = new AxonLatchingSwitchAction();																				break;
				case AxonMacroAction_t:							_actionList[i] = new AxonMacroAction();																							break;
				case AxonMomentarySwitchAction_t:				_actionList[i] = new AxonMomentarySwitchAction();																				break;
				case AxonRadioSwitchAction_t:					_actionList[i] = new AxonRadioSwitchAction();																					break;
				case AxonRadioSwitchGroupAction_t:				_actionList[i] = new AxonRadioSwitchGroupAction();																				break;
				case AxonShowMainScreenAction_t:				_actionList[i] = new AxonShowMainScreenAction();																				break;
				case AxonU2BabyMemoryMapAction_t:				_actionList[i] = new AxonU2BabyMemoryMapAction();																				break;
	
				case AxonSendMidiCCAction_t:					_actionList[i] = new AxonSendMidiCCAction( _actionMap.param1, _actionMap.param2, _actionMap.param3 );							break;
				case AxonSendMidiFixedCCAction_t:				_actionList[i] = new AxonSendMidiFixedCCAction( _actionMap.param1, _actionMap.param2, _actionMap.param3, _actionMap.param4);	break;
				case AxonSendMidiPCAction_t:					_actionList[i] = new AxonSendMidiPCAction( _actionMap.param1, _actionMap.param2, _actionMap.param3 );							break;

				case AxonAFXXLPPresetBlocksDataRequestAction_t: _actionList[i] = new AxonAFXXLPPresetBlocksDataRequestAction( _actionMap.param1 );												break;
				case AxonAFXXLPPresetDownAction_t:				_actionList[i] = new AxonAFXXLPPresetDownAction();																				break;
				case AxonAFXXLPPresetNameRequestAction_t:		_actionList[i] = new AxonAFXXLPPresetNameRequestAction( _actionMap.param1 );													break;
				case AxonAFXXLPPresetNumberRequestAction_t:		_actionList[i] = new AxonAFXXLPPresetNumberRequestAction( _actionMap.param1, _actionMap.param2 );								break;
				case AxonAFXXLPPresetUpAction_t:				_actionList[i] = new AxonAFXXLPPresetUpAction();																				break;
				case AxonAFXXLPSceneNumberRequestAction_t:		_actionList[i] = new AxonAFXXLPSceneNumberRequestAction( _actionMap.param1 );													break;
				case AxonAFXXLPSysExAction_t:					_actionList[i] = new AxonAFXXLPSysExAction();																					break;
				case AxonAFXXLPTunerInfoAction_t:				_actionList[i] = new AxonAFXXLPTunerInfoAction();																				break;
				case AxonShowPresetNameAction_t:				_actionList[i] = new AxonShowPresetNameAction();																				break;
				case AxonShowPresetNumberAction_t:				_actionList[i] = new AxonShowPresetNumberAction();																				break;
				case AxonShowSceneNumberAction_t:				_actionList[i] = new AxonShowSceneNumberAction();																				break;
				case AxonShowTunerScreenAction_t:				_actionList[i] = new AxonShowTunerScreenAction();																				break;
				case AxonStoreAFXXLPPresetNameAction_t:			_actionList[i] = new AxonStoreAFXXLPPresetNameAction();																			break;
				case AxonStoreAFXXLPPresetNumberAction_t:		_actionList[i] = new AxonStoreAFXXLPPresetNumberAction();																		break;
				case AxonStoreAFXXLPSceneNumberAction_t:		_actionList[i] = new AxonStoreAFXXLPSceneNumberAction();																		break;

				default:   Serial.println( F("   ERROR: _actionMap.type not supported") ); return false;	break;
			}
#ifdef DEBUG_SURFACES
Serial.println("  action created");
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			if ( (_actionMap.type & AxonOnActionHook_t) == AxonOnActionHook_t )				{ _logic->setOnAction( _actionList[i] ); }
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			if ( (_actionMap.type & AxonOffActionHook_t) == AxonOffActionHook_t )			{ _logic->setOffAction( _actionList[i] ); }
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
			if ( (_actionMap.type & AxonChangeActionHook_t) == AxonChangeActionHook_t )		{ _logic->setChangeAction( _actionList[i] );	}
#ifdef DEBUG_SURFACES
Serial.println("  action mapped");
#endif
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
		}
	}

	return true;
}



