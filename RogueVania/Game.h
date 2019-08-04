#pragma once
#include "SFML/Graphics.hpp"

class GameState;

class Game
{
public:
	int run();

	float getDeltaTime() const;
	void resetTimer();

	void clearWindow(sf::Color clearColour);
	void drawWindow(sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	void displayWindow();

	void close();

	void changeWindowSettings(sf::VideoMode newVideoMode, sf::Uint32 newStyle = sf::Style::Close);

	void toggleFullscreen();

	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;

	bool isWindowFullscreen() const;

	sf::Vector2i getMousePos() const;

	unsigned int _furthestLevel = 0;

private:
	void initialize();
	void switchState(GameState* newState);

	sf::RenderWindow _window;
	sf::Clock _mainClock;

	bool _gameRunning = false;

	bool _fullscreen = false;

	GameState* currentState = nullptr;

	// Defaults - maybe load this from text file later
	sf::VideoMode defaultVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
	std::string windowTitle = "There and Back Again";
	unsigned int framerateLimit = 60;

	sf::Image icon;
};

