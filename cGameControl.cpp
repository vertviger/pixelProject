#include "cGameControl.h"
#include "cScene.h"
#include "cEntity.h"
#include "cAction.h"
#include "cGraphics.h"

#include <memory>

using namespace std;
using namespace sf;


cGameControl::cGameControl()
{
	const Texture& texture = GetTexture("../Visuals/Sprites/uiActionsFrame.png");
	slotsSprite = new Sprite(texture);
	const Texture& texture1 = GetTexture("../Visuals/Sprites/Actions/actionFireball.png");
	Sprite* fireball = new Sprite(texture1);
	actionSprites[A_FIREBALL] = fireball;
	const Texture& texture2 = GetTexture("../Visuals/Sprites/Actions/actionTeleport.png");
	Sprite* teleport = new Sprite(texture2);
	actionSprites[A_TELEPORT] = teleport;
	/*const Texture& texture2 = GetTexture("../Visuals/Sprites/Actions/actionTeleport.png");
	Sprite* action2 = new Sprite(texture2);
	action2->setPosition({});
	const Texture& texture3 = GetTexture("../Visuals/Sprites/Actions/actionSpeed.png");
	Sprite* action3 = new Sprite(texture3);
	action3->setPosition({});
	const Texture& texture4 = GetTexture("../Visuals/Sprites/Actions/actionTransform.png");
	Sprite* action4 = new Sprite(texture4);
	action4->setPosition({});
	const Texture& texture5 = GetTexture("../Visuals/Sprites/hpBar.png");
	Sprite* hpBar = new Sprite(texture5);
	hpBar->setPosition({});
	const Texture& texture6 = GetTexture("../Visuals/Sprites/hpBar.png");
	Sprite* manaBar = new Sprite(texture6);
	manaBar->setPosition({});*/
}

cGameControl::~cGameControl()
{

}

cGameControl* cGameControl::Get()
{
	static cGameControl gameControl;
	return &gameControl;
}

void cGameControl::Draw(RenderWindow& window)
{
	float yPos = (float)window.getSize().y - (float)(slotsSprite->getScale().y * slotsSprite->getTexture().getSize().y);
	slotsSprite->setPosition({ 0.0, yPos });
	slotsSprite->setOrigin({0.0f, (float)(slotsSprite->getScale().y * slotsSprite->getTexture().getSize().y) });
	slotsSprite->setScale({ 0.4, 0.4 });
	window.draw(*slotsSprite);
	actionSprites[A_FIREBALL]->setScale({ 0.15, 0.15 });
	actionSprites[A_FIREBALL]->setPosition({ 25.0, yPos-5 });
	actionSprites[A_TELEPORT]-> setScale({ 0.125, 0.125 });
	actionSprites[A_TELEPORT]->setPosition({ 100.0, yPos-5});
	for (auto& i : actionSprites)
	{
		window.draw(*i.second);
	}
}



void cGameControl::EventHandle(optional<Event> event)
{
	cActionType action = A_NONE;
	if(auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::W: action = A_MOVE_UP;		break;
		case Keyboard::Key::S: action = A_MOVE_DOWN;	break;
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
			action = A_MOVE_STOP_X; 
			break;
		case Keyboard::Key::W:
		case Keyboard::Key::S:
			action = A_MOVE_STOP_Y;
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

