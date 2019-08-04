#pragma once
#include "GameState.h"

#include "MenuButton.h"

class Game;

class OptionState :
	public GameState
{
public:
	OptionState(Game& game);

	// Inherited via GameState
	virtual void handleEvent(Game& game, sf::Event& event) override;
	virtual GameState* update(Game& game) override;
	virtual void draw(Game& game) override;


private:
	MenuButton toggleFullscreenButton;
	MenuButton backButton;

	sf::Font menuFont;
	sf::Texture menuButtonTexture;
	sf::Texture menuButtonHoverTexture;
	sf::Texture menuButtonClickTexture;

	GameState* newState = nullptr;
};

