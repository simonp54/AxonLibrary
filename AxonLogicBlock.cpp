#include "AxonLogicBlock.h"
#include "AxonActionManager.h"

void AxonLogicBlock::setOnAction( uint16_t actionNumber )
{
	if (_onActionCount < _maxActions)
	{
		_onAction[_onActionCount] = actionNumber;
		_onActionCount++;
	}
}

void AxonLogicBlock::executeOnActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _onActionCount; i++ )
	{
		AxonActionManager::instance()->executeAction( _onAction[i], event );
	}
}

void AxonLogicBlock::setOffAction( uint16_t actionNumber )
{
	if (_offActionCount < _maxActions)
	{
		_offAction[_offActionCount] = actionNumber;
		_offActionCount++;
	}
}

void AxonLogicBlock::executeOffActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _offActionCount; i++ )
	{
		AxonActionManager::instance()->executeAction( _offAction[i], event );
	}
}

void AxonLogicBlock::setChangeAction( uint16_t actionNumber )
{
	if (_changeActionCount < _maxActions)
	{
		_changeAction[_changeActionCount] = actionNumber;
		_changeActionCount++;
	}
}

void AxonLogicBlock::executeChangeActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _changeActionCount; i++ )
	{
		AxonActionManager::instance()->executeAction( _changeAction[i], event );
	}
}

void AxonLogicBlock::clearAllActions()
{
	_onActionCount = 0;
	_offActionCount = 0;
	_changeActionCount = 0;
}