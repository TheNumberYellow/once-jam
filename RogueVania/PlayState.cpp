#include "PlayState.h"

#include "Game.h"

#include "MenuState.h"

PlayState::PlayState(Game& game) :
	_tileMap("images/tileset.png", sf::Vector2u(20, 20), sf::Vector2f((float)game.getWindowWidth(), (float)game.getWindowHeight())),
	_player("images/player.png")
{

	victoryFont.loadFromFile("fonts/FREESCPT.TTF");
	victoryText.setFont(victoryFont);

	victoryText.setCharacterSize(game.getWindowWidth() * 0.1f);
	victoryText.setString("You win!");

	sf::FloatRect victoryBounds = victoryText.getGlobalBounds();

	victoryText.setOrigin(sf::Vector2f(victoryBounds.width / 2.0f + victoryBounds.left, victoryBounds.height / 2.0f + victoryBounds.top));
	victoryText.setPosition(sf::Vector2f(game.getWindowWidth() * 0.5f, game.getWindowHeight() * 0.5f));
	victoryText.setFillColor(sf::Color::Cyan);

	_levels[0] = Level(
		{

			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0,	0, 0, 0, 2,	2, 2, 2, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 1,
			3, 3, 3, 3, 3, 3, 3, 3,	3, 3, 3, 3,
		},
		12, 6,
		sf::Vector2i(2, 4),
		sf::Vector2i(9, 2)
		);

	_levels[1] = Level(
		{

			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0,	0, 0, 0, 2,	2, 2, 2, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 1,
			3, 3, 3, 3, 3, 3, 3, 3,	3, 3, 3, 3,
		},
		12, 8,
		sf::Vector2i(2, 6),
		sf::Vector2i(2, 2)
	);

	_levels[2] = Level(
		{

			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 3, 3, 3,	0, 0, 0, 0,	0, 0, 0, 3,	3, 3, 3, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 1,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	2, 2, 2, 2,
		},
		16, 10,
		sf::Vector2i(7, 8),
		sf::Vector2i(13, 2)
	);

	_levels[3] = Level(
		{

			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	2, 2, 2, 2,	2, 2, 2, 2, 2, 2, 2, 2, 2,
			1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 2,	2, 2, 0, 0,	3, 0, 0, 2,	2, 2, 2, 2,	2, 2, 0, 0, 0, 3, 3, 3, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0,	0, 0, 0, 0, 3, 3, 0, 0, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	3, 3, 0, 0,	0, 2, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 2, 2, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 2, 0, 0,	0, 0, 2, 2, 0, 0, 0, 0, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 2,	2, 2, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	2, 2, 0, 0, 0, 0, 0, 0, 1,
			1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 1,
			3, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 2,	2, 2, 2, 0,	0, 0, 0, 0, 0, 0, 0, 0, 3,
			3, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 3,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	2, 2, 2, 2,	2, 2, 2, 2, 2, 2, 2, 2, 2,
		},
		25, 13,
		sf::Vector2i(4, 2),
		sf::Vector2i(22, 2)
	);

	_levels[4] = Level(
		{

			3, 3, 3, 3, 3, 3, 3, 3,
			1, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 2, 2, 2,
			1, 0, 0, 0, 0, 0, 0, 1,
			2, 2, 2, 0, 0, 0, 0, 1,
			0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0,
			3, 3, 3, 3, 3, 3, 3, 3,
		},
		8, 10,
		sf::Vector2i(3, 8),
		sf::Vector2i(6, 2)
	);

	_levels[5] = Level(
		{

			3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	1, 1, 0, 0,	2,
			2, 0, 0, 0, 0, 2, 2, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 1, 1, 1, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 2, 2, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 1, 1, 1, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 2, 2, 2,	0, 0, 0, 0,	2,
			2, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0,	2,
			3, 3, 3, 3, 3, 3, 3, 3,	0, 0, 3, 3,	3,
		},
		13, 15,
		sf::Vector2i(6, 11),
		sf::Vector2i(1, 5)
	);

	_levels[6] = Level(
		{

			0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0,
			0, 0, 0, 0, 2, 2, 2, 2,	0, 0, 0,
			0, 0, 0, 0, 2, 0, 0, 0,	0, 0, 0,
			0, 0, 0, 0, 2, 0, 2, 0,	0, 0, 0,
			0, 0, 0, 0, 2, 0, 2, 2,	2, 0, 0,
			2, 2, 0, 0, 0, 0, 0, 0,	2, 2, 2,
			0, 0, 0, 0, 0, 3, 3, 3,	0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0,	0, 1, 1,
			1, 1, 0, 0, 2, 2, 2, 2,	2, 1, 1,

		},
		11, 10,
		sf::Vector2i(1, 7),
		sf::Vector2i(7, 5)
	);



	_levels[7] = Level(
		{

			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3,
			2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
			2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2,
			2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
		18, 15,
		sf::Vector2i(8, 13),
		sf::Vector2i(16, 2)
	);

	changeLevel(_levels[_currentLevel]);
}

PlayState::PlayState(Game& game, unsigned int levelNum) :
	PlayState(game)
{
	_currentLevel = levelNum;
	if (_currentLevel + 1 > _numLevels) {
		_won = true;
		return;
	}
	changeLevel(_levels[_currentLevel]);
}

PlayState::~PlayState()
{
}

void PlayState::handleEvent(Game& game, sf::Event& event)
{
	switch (event.type) {
	case sf::Event::Closed:
		newState = new MenuState(game);
		return;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Escape) {
			newState = new MenuState(game);
			return;
		}
		if (event.key.code == sf::Keyboard::R) {
			resetPlayer();			
		}
		break;
	}

	_player.handleInput(event);
}

GameState* PlayState::update(Game& game)
{
	if (newState != nullptr) return newState;

	if (_winning) {
		sf::sleep(sf::seconds(0.5f));
		game.resetTimer();
		_winning = false;
	}

	if (_won) {
		return nullptr;
	}

	_player.update(game, _tileMap);
	if (_tileMap.getTilePosFromScreenPos(_player.getScreenPos()) == _tileMap.getEndTilePos()) {
		if (_currentLevel + 1 > _numLevels) {
			_won = true;
		}

		changeLevel(_levels[++_currentLevel]);
		game._furthestLevel = _currentLevel;
		_winning = true;
	}

	return nullptr;
}

void PlayState::draw(Game& game)
{
	game.clearWindow(sf::Color::Black);
	if (!_won) {
		game.drawWindow(_tileMap);
		game.drawWindow(_player);
	}
	else {
		game.drawWindow(victoryText);
	}

	game.displayWindow();
}

void PlayState::changeLevel(Level& newLevel)
{
	_tileMap.setMap(newLevel);
	
	_player.reset(_tileMap);
}

void PlayState::resetPlayer()
{
	_player.reset(_tileMap);
}
