#include "AxonMultiOnOffChangeAction.h"

void AxonMultiOnOffChangeAction::setOnAction( AxonAction *action )
{
	if (_onActionCount < _maxActions)
	{
		_onAction[_onActionCount] = action;
		_onActionCount++;
	}
}

void AxonMultiOnOffChangeAction::executeOnActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _onActionCount; i++ )
	{
		_onAction[i]->execute( sender, event );
	}
}

void AxonMultiOnOffChangeAction::setOffAction( AxonAction *action )
{
	if (_offActionCount < _maxActions)
	{
		_offAction[_offActionCount] = action;
		_offActionCount++;
	}
}

void AxonMultiOnOffChangeAction::executeOffActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _offActionCount; i++ )
	{
		_offAction[i]->execute( sender, event );
	}
}

void AxonMultiOnOffChangeAction::setChangeAction( AxonAction *action )
{
	if (_changeActionCount < _maxActions)
	{
		_changeAction[_changeActionCount] = action;
		_changeActionCount++;
	}
}

void AxonMultiOnOffChangeAction::executeChangeActions( AxonAction *sender, AxonEvent *event )
{
	for( uint8_t i = 0; i < _changeActionCount; i++ )
	{
		_changeAction[i]->execute( sender, event );
	}
}

void AxonMultiOnOffChangeAction::clearAllActions()
{
	_onActionCount = 0;
	_offActionCount = 0;
	_changeActionCount = 0;
}