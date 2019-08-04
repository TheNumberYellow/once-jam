#include "Game.h"

#include "GameState.h"
#include "MenuState.h"

#include <fstream>
#include <iterator>

#include <iostream>

int Game::run()
{
	initialize();
	while (_gameRunning) {
		sf::Event event;
		while (_window.pollEvent(event)) {
			currentState->handleEvent(*this, event);
		}
		GameState* newState = currentState->update(*this);
		if (newState != nullptr) {
			switchState(newState);
		}

		_mainClock.restart();

		currentState->draw(*this);
	}
	std::ofstream oFile("saves/save.save", std::ios::binary);
	oFile.write((char*)& _furthestLevel, sizeof(unsigned int));
	_window.close();
	return 0;
}

float Game::getDeltaTime() const
{
	return _mainClock.getElapsedTime().asSeconds();
}

void Game::resetTimer()
{
	_mainClock.restart();
}

void Game::clearWindow(sf::Color clearColour)
{
	_window.clear(clearColour);
}

void Game::drawWindow(sf::Drawable& drawable, const sf::RenderStates& states)
{
	_window.draw(drawable, states);
}

void Game::displayWindow()
{
	_window.display();
}

void Game::close()
{
	_gameRunning = false;
}

void Game::changeWindowSettings(sf::VideoMode newVideoMode, sf::Uint32 newStyle)
{
	_window.create(newVideoMode, windowTitle, newStyle);
	_window.setIcon(20, 20, icon.getPixelsPtr());
	_window.setFramerateLimit(framerateLimit);
	_window.setVerticalSyncEnabled(true);
}

void Game::toggleFullscreen()
{
	if (_fullscreen) {
		changeWindowSettings(defaultVideoMode, sf::Style::Close);
		_fullscreen = false;
	}
	else {
		changeWindowSettings(sf::VideoMode::getDesktopMode(), sf::Style::Fullscreen);
		_fullscreen = true;
	}
}

unsigned int Game::getWindowWidth() const
{
	return _window.getSize().x;
}

unsigned int Game::getWindowHeight() const
{
	return _window.getSize().y;
}

bool Game::isWindowFullscreen() const
{
	return _fullscreen;
}

sf::Vector2i Game::getMousePos() const
{
	return sf::Mouse::getPosition(_window);
}

void Game::initialize()
{
	icon.loadFromFile("images/icon.png");
	
	_window.create(defaultVideoMode, windowTitle, sf::Style::Close);
	_window.setIcon(20, 20, icon.getPixelsPtr());
	_window.setFramerateLimit(framerateLimit);
	_window.setVerticalSyncEnabled(true);




	std::ifstream inFile("saves/save.save");
	
	if (inFile) {
		// save file exists
		unsigned int readNum;
		inFile.read((char*) &readNum, sizeof(unsigned int));
	
		std::cout << "File exists.\n";
		std::cout << "Read number " << readNum << "\n";

		_furthestLevel = readNum;

	}
	else {
		std::ofstream oFile("saves/save.save", std::ios::binary);
		oFile.write((char*)&_furthestLevel, sizeof(unsigned int));

		std::cout << "File doesn't exist. Created.\n";
	}


	currentState = new MenuState(*this);
	_gameRunning = true;

}

void Game::switchState(GameState* newState)
{
	delete currentState;
	currentState = newState;
}
