#pragma once
#include "GameState.h"

#include "TileMap.h"
#include "Player.h"

class PlayState :
	public GameState
{
public:

	PlayState(Game& game);
	PlayState(Game& game, unsigned int levelNum);
	~PlayState();

	// Inherited via GameState
	virtual void handleEvent(Game& game, sf::Event& event) override;
	virtual GameState* update(Game& game) override;
	virtual void draw(Game& game) override;

	unsigned int _currentLevel = 0;
private:

	void changeLevel(Level& newLevel);
	void resetPlayer();

	TileMap _tileMap;
	Level _levels[20];


	Player _player;

	bool _winning = false;

	GameState* newState = nullptr;

	sf::Font victoryFont;
	sf::Text victoryText;

	unsigned int _numLevels = 7;
	bool _won = false;
};

