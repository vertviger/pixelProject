#include "cGameControl.h"
#include "cScene.h"
#include "cEntity.h"
#include "cAction.h"
#include "cGraphics.h"

#include <memory>

using namespace std;
using namespace sf;

const string& AssetsPath();

cGameControl::cGameControl()
{
	string spritesPath = AssetsPath() + "Visuals/Sprites/";

	const Texture& texture = GetTexture(spritesPath + "uiActionsFrame.png");
	slotsSprite = new Sprite(texture);
	slotsSprite->setPosition({ 100, 500 });
	const Texture& texture1 = GetTexture(spritesPath + "Actions/actionFireball.png");
	Sprite* fireball = new Sprite(texture1);
	fireball->setPosition({ 100, 600 });
	actionSprites[A_FIREBALL] = fireball;
	const Texture& texture2 = GetTexture(spritesPath + "Actions/actionTeleport.png");
	Sprite* teleport = new Sprite(texture2);
	actionSprites[A_TELEPORT] = teleport;
	const Texture& texture3 = GetTexture(spritesPath + "Actions/actionSpeed.png");
	Sprite* speed = new Sprite(texture3);
	actionSprites[A_SPEED] = speed;
	const Texture& texture4 = GetTexture(spritesPath + "Actions/actionTransform.png");
	Sprite* transform = new Sprite(texture4);
	actionSprites[A_TRANSFORM] = transform;
	/*Sprite* action2 = new Sprite(texture2);
	action2->setPosition({});
	const Texture& texture3 = GetTexture(spritesPath + "Actions/actionSpeed.png");
	Sprite* action3 = new Sprite(texture3);
	action3->setPosition({});
	const Texture& texture4 = GetTexture(spritesPath + "Actions/actionTransform.png");
	Sprite* action4 = new Sprite(texture4);
	action4->setPosition({});
	const Texture& texture5 = GetTexture(spritesPath "hpBar.png");
	Sprite* hpBar = new Sprite(texture5);
	hpBar->setPosition({});
	const Texture& texture6 = GetTexture(spritesPath + "hpBar.png");
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

void cGameControl::Quant()
{
	sf::Vector2f moveDirection(0.0f, 0.0f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))		moveDirection.y = -1.0f; // up
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))	moveDirection.y = +1.0f; // down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))		moveDirection.x = -1.0f; // left
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	moveDirection.x = +1.0f; // right
	float l = moveDirection.length();
	if(l > 0.0f)
	{
		moveDirection /= l; // normalize
	}
	controlledEntity->SetMoveDirection(moveDirection);
}

void cGameControl::Draw(RenderWindow& window)
{
	float actionPosX = 24;
	float actionPosY = window.getView().getSize().y - (float)slotsSprite->getTexture().getSize().y;
	slotsSprite->setPosition({0, actionPosY});
	actionPosY += 40;
	for (auto& i : actionSprites)
	{
		window.draw(*i.second);
		i.second->setPosition({actionPosX, actionPosY});
		actionPosX += 74.5;
	}
	window.draw(*slotsSprite);
}

void cGameControl::EventHandle(optional<Event> event)
{
	cActionType action = A_NONE;
	if(auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::Num1: //@to_do selectedAction
			break; 
		}
	}
	if(auto const keyEvent = event->getIf<Event::KeyReleased>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::Num1: //@to_do selectedAction
			break;
		}
	}
	if(action)
	{
		cTarget target; // @to_do select target under mouse cursor
		controlledEntity->StartAction(action, target);
	}
}