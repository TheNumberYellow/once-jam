#pragma once
#include "GameState.h"

#include "MenuButton.h"

class Game;

class MenuState :
	public GameState
{
public:
	MenuState(Game& game);
	virtual ~MenuState();

	virtual void handleEvent(Game& game, sf::Event& event);
	virtual GameState* update(Game& game);
	virtual void draw(Game& game);


private:

	MenuButton newGameButton;
	MenuButton continueButton;
	MenuButton optionsButton;
	MenuButton closeButton;

	sf::Font menuFont;
	sf::Texture menuButtonTexture;
	sf::Texture menuButtonHoverTexture;
	sf::Texture menuButtonClickTexture;

	sf::Font titleFont;
	sf::Text titleText;

	sf::Font subtitleFont;
	sf::Text subtitleText;
	sf::Text tutorialText;

	GameState* newState = nullptr;
};

