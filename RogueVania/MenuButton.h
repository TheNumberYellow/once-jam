#pragma once
#include "SFML/Graphics.hpp"

class Game;

class MenuButton : public sf::Drawable
{
public:
	MenuButton();
	MenuButton(sf::Vector2f buttonCenter, std::string buttonString, sf::Font* buttonTextFont, sf::Texture* buttonTexture, sf::Texture* buttonHoverTexture, sf::Texture* buttonClickTexture, float scale = 1.0f);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	void clickDown(sf::Vector2i mousePos);
	bool clickUp(sf::Vector2i mousePos);

	void update(Game& game);

	void setEnabled(bool newEnabled);
	void setString(std::string newString);
private:

	sf::Sprite buttonSprite;
	sf::Texture* buttonTexture;
	sf::Texture* buttonHoverTexture;
	sf::Texture* buttonClickTexture;

	sf::FloatRect buttonRect;

	sf::Text buttonText;
	
	bool clicking;
	bool enabled;
};

