#include "cGameControl.h"
#include "cScene.h"
#include "cEntity.h"
#include "cAction.h"
#include <memory>

using namespace std;

static cGameControl gameControl;

cGameControl* cGameControl::Get()
{
	return &gameControl;
}

void cGameControl::EventHandle(optional<Event> event)
{
	cActionType action = A_NONE;
	if(auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::W: action = A_JUMP;			break;
		case Keyboard::Key::S: action = A_SNEAK;		break;
		case Keyboard::Key::A: action = A_MOVE_LEFT;	break;
		case Keyboard::Key::D: action = A_MOVE_RIGHT;	break;
			//@to_do selectedAction
		}
	}
	if(auto const keyEvent = event->getIf<Event::KeyReleased>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::A: // no break;	 //stop go right
		case Keyboard::Key::D: 
			action = A_MOVE_STOP; 
			break;
		}
	}
	if(action)
	{
		cEntity* controlledEnt = cScene::Get()->ControlledEntity();
		cTarget target; // @to_do select target under mouse cursor
		controlledEnt->StartAction(action, target);
	}
}

