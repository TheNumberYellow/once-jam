#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Game;
class TileMap;

inline float dotProduct(sf::Vector2f a, sf::Vector2f b) {
	return a.x * b.x + a.y * b.y;
}

inline float vecLength(sf::Vector2f vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

struct Edge {
	sf::Vector2f a, b;
	Edge();

	Edge(sf::Vector2f a, sf::Vector2f b);

	sf::Vector2f normal;
};

bool lineIntersect(Edge a, Edge b, sf::Vector2f& intersectPoint, float* aT, float* bT);

class Player : public sf::Drawable
{
public:
	Player(std::string spriteFilePath);

	void update(Game& game, const TileMap& tileMap);
	void handleInput(sf::Event& event);

	void changeSize(sf::Vector2f newSize);
	void setPosition(sf::Vector2f newPos);
	void setVelocity(sf::Vector2f newVelocity);

	void reset(const TileMap& tileMap);

	sf::Vector2f getSize() const;
	sf::Vector2f getScreenPos() const;

protected:

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:

	void move(Game& game, sf::Vector2f movementVector, const TileMap& tileMap);


	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Texture _textureLeft;
	sf::Texture _textureRight;

	const float _baseGravityAccel = 30.0f;
	const float _baseJumpVelocity = 12.0f;
	const float _baseWalkSpeed = 4.0f;
	const float _baseWalkAccel = 20.0f;

	const float _friction = 0.20f;

	float _gravityAccel = 1000.0f;
	float _jumpVelocity = 400.0f;
	float _walkSpeed = 200.0f;
	float _walkAccel = 200.0f;
	
	sf::Vector2f _velocity;

	bool _pressingSpace = false;

	bool _onGround = false;
	bool _jumped = false;

	bool _wentLeft = false;
	bool _wentRight = false;
	bool _canGoLeft = true;
	bool _canGoRight = true;

	sf::Sound _sound;

	sf::SoundBuffer _impactSound;
};

