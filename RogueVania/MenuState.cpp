#include "MenuState.h"

#include "OptionState.h"
#include "PlayState.h"

#include "Game.h"

#include <iostream>

MenuState::MenuState(Game& game)
{
	menuFont.loadFromFile("fonts/ROCC____.TTF");
	menuButtonTexture.loadFromFile("images/menuButton.png");
	menuButtonHoverTexture.loadFromFile("images/menuHoverButton.png");
	menuButtonClickTexture.loadFromFile("images/menuClickButton.png");

	titleFont.loadFromFile("fonts/FREESCPT.TTF");
	titleText.setFont(titleFont);
	
	titleText.setCharacterSize(game.getWindowWidth() * 0.1f);
	titleText.setString("There and Back Again");
	
	sf::FloatRect titleBounds = titleText.getGlobalBounds();
	
	titleText.setOrigin(sf::Vector2f(titleBounds.width / 2.0f + titleBounds.left, titleBounds.height / 2.0f + titleBounds.top));
	titleText.setPosition(sf::Vector2f(game.getWindowWidth() * 0.5f, game.getWindowHeight() * 0.2f));
	titleText.setFillColor(sf::Color::Cyan);

	subtitleFont.loadFromFile("fonts/LCALLIG.TTF");
	subtitleText.setFont(subtitleFont);

	subtitleText.setCharacterSize(game.getWindowWidth() * 0.025f);
	subtitleText.setString("You can only change your \n horizontal direction once.");

	sf::FloatRect subtitleBounds = subtitleText.getGlobalBounds();

	subtitleText.setOrigin(sf::Vector2f(subtitleBounds.width / 2.0f + subtitleBounds.left, subtitleBounds.height / 2.0f + subtitleBounds.top));
	subtitleText.setPosition(sf::Vector2f(game.getWindowWidth() * 0.5f, game.getWindowHeight() * 0.4f));
	subtitleText.setFillColor(sf::Color(255, 138, 154));

	tutorialText.setFont(subtitleFont);
	tutorialText.setCharacterSize(game.getWindowWidth() * 0.02f);
	tutorialText.setString("Arrow keys/WASD to move \n       Space bar to jump \n            R to reset");

	sf::FloatRect tutorialBounds = tutorialText.getGlobalBounds();

	tutorialText.setOrigin(sf::Vector2f(tutorialBounds.width / 2.0f + tutorialBounds.left, tutorialBounds.height / 2.0f + tutorialBounds.top));
	tutorialText.setPosition(sf::Vector2f(game.getWindowWidth() * 0.5f, game.getWindowHeight() * 0.6f));
	tutorialText.setFillColor(sf::Color(0, 255, 255));


	newGameButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.6f), "NEW GAME", &menuFont,
		&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
	);

	continueButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.7f), "CONTINUE", &menuFont,
		&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
	);

	if (game._furthestLevel == 0) {
		continueButton.setEnabled(false);
	}

	optionsButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.8f), "OPTIONS", &menuFont,
		&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
	);

	
	closeButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.9f), "CLOSE", &menuFont, 
		&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
	);

}

MenuState::~MenuState()
{

}

void MenuState::handleEvent(Game& game, sf::Event& event)
{
	switch (event.type) {
	case sf::Event::Closed:
		game.close();
		return;
	case sf::Event::MouseButtonPressed:
		newGameButton.clickDown(game.getMousePos());
		continueButton.clickDown(game.getMousePos());
		optionsButton.clickDown(game.getMousePos());
		closeButton.clickDown(game.getMousePos());
		break;
	case sf::Event::MouseButtonReleased:
		if (newGameButton.clickUp(game.getMousePos())) {
			newState = new PlayState(game);
		}
		if (continueButton.clickUp(game.getMousePos())) {
			newState = new PlayState(game, game._furthestLevel);
		}
		if (optionsButton.clickUp(game.getMousePos())) {
			newState = new OptionState(game);
		}
		if (closeButton.clickUp(game.getMousePos())) {
			game.close();
			return;
		}
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Escape) {
			game.close();
			return;
		}
	}
}

GameState* MenuState::update(Game& game)
{
	if (newState != nullptr) {
		return newState;
	}
	newGameButton.update(game);
	continueButton.update(game);
	optionsButton.update(game);
	closeButton.update(game);
	return nullptr;
}

void MenuState::draw(Game& game)
{
	game.clearWindow(sf::Color(76, 82, 112));

	game.drawWindow(newGameButton);
	game.drawWindow(continueButton);
	game.drawWindow(optionsButton);
	game.drawWindow(closeButton);
	game.drawWindow(titleText);
	game.drawWindow(subtitleText);
	game.drawWindow(tutorialText);

	game.displayWindow();
}
