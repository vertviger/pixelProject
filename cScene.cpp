#include "cScene.h"
void cScene::draw(sf::RenderWindow& window)
{
	for (auto& e : entities)
	{
		e.draw(window);
	}
}
void cScene::onKeyReleased(sf::Event::KeyReleased key)
{
	//switch
}
