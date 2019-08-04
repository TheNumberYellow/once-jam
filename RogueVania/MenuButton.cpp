#include "MenuButton.h"

#include "Game.h"

MenuButton::MenuButton() :
	buttonTexture(nullptr), buttonHoverTexture(nullptr), buttonClickTexture(nullptr), clicking(false), enabled(true)
{
}

MenuButton::MenuButton(sf::Vector2f buttonCenter, std::string buttonString, sf::Font* buttonTextFont, sf::Texture* buttonTexture, sf::Texture* buttonHoverTexture, sf::Texture* buttonClickTexture, float scale) :
	buttonTexture(buttonTexture), buttonHoverTexture(buttonHoverTexture), buttonClickTexture(buttonClickTexture), clicking(false), enabled(true)
{
	buttonSprite.setTexture(*buttonTexture);
	buttonSprite.setOrigin(sf::Vector2f(buttonSprite.getLocalBounds().width / 2.0f, buttonSprite.getLocalBounds().height / 2.0f));
	buttonSprite.setPosition(buttonCenter);
	buttonSprite.setScale(sf::Vector2f(scale, scale));
	buttonSprite.setColor(sf::Color::Cyan);

	buttonText.setFont(*buttonTextFont);
	buttonText.setString(buttonString);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setCharacterSize((unsigned int)(30 * scale));
	
	sf::FloatRect textBounds = buttonText.getGlobalBounds();
	
	buttonText.setOrigin(sf::Vector2f(textBounds.width / 2.0f + textBounds.left, textBounds.height / 2.0f + textBounds.top));
	buttonText.setPosition(buttonCenter);
	//buttonText.setScale(sf::Vector2f(scale, scale));

	buttonRect = buttonSprite.getGlobalBounds();
}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(buttonSprite);
	target.draw(buttonText);
}

void MenuButton::clickDown(sf::Vector2i mousePos)
{
	if (!enabled) return;

	if (buttonRect.contains(sf::Vector2f(mousePos))) {
		clicking = true;
		buttonSprite.setTexture(*buttonClickTexture);
	}
}

bool MenuButton::clickUp(sf::Vector2i mousePos)
{
	if (!enabled) return false;

	buttonSprite.setTexture(*buttonTexture);

	if (clicking) {
		if (buttonRect.contains(sf::Vector2f(mousePos))) {
			clicking = false;

			return true;
		}
		else {
			clicking = false;
		}
	}
	return false;
}

void MenuButton::update(Game& game)
{
	if (!enabled) return;

	if (buttonRect.contains(sf::Vector2f(game.getMousePos()))) {
		if (!clicking) {
			buttonSprite.setTexture(*buttonHoverTexture);
		}
	}
	else {
		clicking = false;
		buttonSprite.setTexture(*buttonTexture);
	}

}

void MenuButton::setEnabled(bool newEnabled)
{
	enabled = newEnabled;

	if (!enabled) {
		buttonSprite.setColor(sf::Color(255, 255, 255, 127));
		//buttonText.setFillColor(sf::Color(255, 255, 255, 127));
	}
	else {
		buttonSprite.setColor(sf::Color(255, 255, 255, 255));
		//buttonText.setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void MenuButton::setString(std::string newString)
{
	buttonText.setString(newString);
}
