#include "cGameControl.h"
#include "cScene.h"
#include "cEntity.h"
#include "cAction.h"
#include "cGraphics.h"

#include <memory>
#include <iostream>


using namespace std;
using namespace sf;

std::vector<std::string> actionNames = { "actionFireball", "actionTeleport", "actionHeal", "actionLightning"};
cGameControl::cGameControl()
{
	string spritesPath = AssetsPath() + "Visuals/Sprites/";
	for (auto& action : actionNames)
	{
		const Texture& texture1 = GetTexture(spritesPath + "Actions/" + action + ".png");
		Sprite* actionSprite = new Sprite(texture1);
		actionSprite->setPosition({ 100, 600 });
		actionSprites.push_back(actionSprite);
	}
	const Texture& texture = GetTexture(spritesPath + "uiActionsFrame.png");
	slotsSprite = new Sprite(texture);
	slotsSprite->setPosition({ 100, 500 });
	slotsSprite->setColor(Color(0, 180, 0));
	const Texture& texture5 = GetTexture(spritesPath + "hpBar.png");
	hpBar = new Sprite(texture5);
	hpBar->setPosition({ 100, 500 });
	hpBar->setScale({ 0.5, 0.5 });
	hpBar->setColor(Color(0,200,0));
}

cGameControl::~cGameControl()
{

}

cGameControl* cGameControl::Get()
{
	static cGameControl gameControl;
	return &gameControl;
}

sf::Vector2f MouseToScene(sf::Vector2i mousePosition);

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
	if (action && action->Do(target)) //Do returns true when action is finished
	{
		target = NULL;
		delete action;
		action = NULL;
	}
}

void cGameControl::Draw(RenderWindow& window)
{
	if (action || !GetTarget(Mouse::getPosition(window)))
	{
		window.setMouseCursor(cursorCant);
	}
	else
	{
		window.setMouseCursor(cursorCan);
	}
	Vector2f windowSize = window.getView().getSize();
	if (controlledEntity)
	{
		float part = controlledEntity->HealthPercentage();
		Vector2f firstSize = { 315,13 };
		RectangleShape healthBar = RectangleShape({ firstSize.x * part, firstSize.y });
		healthBar.setOrigin({healthBar.getSize()});
		healthBar.setPosition({ windowSize.x - firstSize.x*0.19f ,windowSize.y - firstSize.y*2.5f });
		healthBar.setFillColor(Color::Red);
		window.draw(healthBar);
	}
	hpBar->setPosition({ windowSize.x - hpBar->getTexture().getSize().x*hpBar->getScale().x, windowSize.y - hpBar->getTexture().getSize().y * hpBar->getScale().y });
	window.draw(*hpBar);
	float actionPosX = 24;
	float actionPosY = windowSize.y - (float)slotsSprite->getTexture().getSize().y;
	slotsSprite->setPosition({5, actionPosY});
	actionPosY += 40;
	for (int i = 0; i < actionSprites.size(); i++)
	{
		auto sprite = actionSprites[i];
		sprite->setColor(i == selectedActionIdx ? Color(255, 255, 255, 255) : Color(255, 255, 255, 127));
		sprite->setPosition({ actionPosX, actionPosY });
		actionPosX += 76.2;
		window.draw(*sprite);
	}
	window.draw(*slotsSprite);
}
void cGameControl::SelectAction(int number)
{
	if(actionSelected) delete actionSelected;
	selectedActionIdx = number;
	actionSelected = new cAction(actionNames[number], controlledEntity);
}
cEntity* cGameControl::GetTarget(const Vector2i& mousePos) const
{
	auto mouseScenePos = MouseToScene(mousePos);
	for (auto e : cScene::Get()->Entities())
	{
		if (e->Bound().contains(mouseScenePos) && actionSelected->Can(e))
		{
			return e;
		}
	}
	return NULL;
}
void cGameControl::EventHandle(optional<Event> event)
{
	if(auto const keyEvent = event->getIf<Event::KeyPressed>())
	{
		switch(keyEvent->code)
		{
		case Keyboard::Key::Num1: SelectAction(0); break;
			case Keyboard::Key::Num2: SelectAction(1); break;
			case Keyboard::Key::Num3: SelectAction(2); break;
			case Keyboard::Key::Num4: SelectAction(3); break;
		}
	}
	if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			if (!action)
			{
				if(target = GetTarget(mouseButtonPressed->position))
				{
					action = new cAction(*actionSelected);
				}
			}
		}
	}
}

void cGameControl::ControledEntity(cEntity* _e)
{
	controlledEntity = _e;
	SelectAction(selectedActionIdx);
}
