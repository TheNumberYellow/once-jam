#include "OptionState.h"

#include "MenuState.h"
#include "Game.h"

OptionState::OptionState(Game& game)
{
	menuFont.loadFromFile("fonts/ROCC____.TTF");
	menuButtonTexture.loadFromFile("images/menuButton.png");
	menuButtonHoverTexture.loadFromFile("images/menuHoverButton.png");
	menuButtonClickTexture.loadFromFile("images/menuClickButton.png");


	backButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.9f), "BACK", &menuFont,
		&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
	);

	if (game.isWindowFullscreen()) {
		toggleFullscreenButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.875f, game.getWindowHeight() * 0.9f), "FULLSCREEN ON", &menuFont,
			&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
		);
	}
	else {
		toggleFullscreenButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.875f, game.getWindowHeight() * 0.9f), "FULLSCREEN OFF", &menuFont,
			&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
		);
	}

}

void OptionState::handleEvent(Game& game, sf::Event& event)
{
	switch(event.type) {
	case sf::Event::Closed:
		game.close();
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Escape) {
			newState = new MenuState(game);
		}
		break;
	case sf::Event::MouseButtonPressed:
		backButton.clickDown(game.getMousePos());
		toggleFullscreenButton.clickDown(game.getMousePos());
		break;

	case sf::Event::MouseButtonReleased:
		if (backButton.clickUp(game.getMousePos())) {
			newState = new MenuState(game);
		}
		if (toggleFullscreenButton.clickUp(game.getMousePos())) {
			game.toggleFullscreen();

			// TODO: allow button changing size/text/dimensions

			backButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.125f, game.getWindowHeight() * 0.9f), "BACK", &menuFont,
				&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
			);
			
			if (game.isWindowFullscreen()) {
				toggleFullscreenButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.875f, game.getWindowHeight() * 0.9f), "FULLSCREEN ON", &menuFont,
					&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
				);
			}
			else {
				toggleFullscreenButton = MenuButton(sf::Vector2f(game.getWindowWidth() * 0.875f, game.getWindowHeight() * 0.9f), "FULLSCREEN OFF", &menuFont,
					&menuButtonTexture, &menuButtonHoverTexture, &menuButtonClickTexture, game.getWindowWidth() / 1080.0f
				);
			}


		}
		break;
	}
}

GameState* OptionState::update(Game& game)
{
	if (newState != nullptr) {
		return newState;
	}

	toggleFullscreenButton.update(game);
	backButton.update(game);

	return nullptr;
}

void OptionState::draw(Game& game)
{
	game.clearWindow(sf::Color::Black);

	game.drawWindow(toggleFullscreenButton);
	game.drawWindow(backButton);

	game.displayWindow();
}
