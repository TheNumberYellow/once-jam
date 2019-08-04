#pragma once
#include "SFML/Window.hpp"

class Game;

class GameState
{
public:
	
	virtual ~GameState() {}
	
	virtual void handleEvent(Game& game, sf::Event& event) = 0;
	virtual GameState* update(Game& game) = 0;
	virtual void draw(Game& game) = 0;

};

