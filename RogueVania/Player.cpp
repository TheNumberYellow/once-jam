#include "Player.h"

#include "Game.h"
#include "TileMap.h"

#include <iostream>

Player::Player(std::string spriteFilePath) 
{
	_texture.loadFromFile(spriteFilePath);
	_textureLeft.loadFromFile("images/playerLeft.png");
	_textureRight.loadFromFile("images/playerRight.png");

	_impactSound.loadFromFile("sounds/impactSound.FLAC");


	_sprite.setTexture(_texture);

	sf::FloatRect spriteBounds = _sprite.getLocalBounds();

	_sprite.setOrigin(sf::Vector2f(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f));
}

void Player::update(Game& game, const TileMap& tileMap)
{
	

	float deltaTime = game.getDeltaTime();

	float inputVec = 0.0f;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && _canGoRight) {
		_wentRight = true;
		_sprite.setTexture(_textureRight);
		if (_wentLeft) {
			_canGoLeft = false;
		}
		inputVec += deltaTime * _walkAccel;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && _canGoLeft) {
		_wentLeft = true;
		_sprite.setTexture(_textureLeft);
		if (_wentRight) {
			_canGoRight = false;
		}
		inputVec -= deltaTime * _walkAccel;
	}

	
	_velocity.x += inputVec;

	if (_velocity.x > _walkSpeed) _velocity.x = _walkSpeed;
	if (_velocity.x < -_walkSpeed) _velocity.x = -_walkSpeed;

	if (inputVec == 0.0f) {
		float frictionForce = _friction * _velocity.x;
		_velocity.x -= frictionForce;
	}

	_velocity += sf::Vector2f(0, _gravityAccel) * deltaTime;
	
	if (_jumped) {
		_jumped = false;
		if (_onGround) {
			_velocity.y = -_jumpVelocity;
		}
	}

	sf::Vector2f movement = _velocity * deltaTime;

	_onGround = false;

	move(game, movement, tileMap);
}

void Player::handleInput(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space && !_pressingSpace) {
			_pressingSpace = true;
			_jumped = true;
		}
		
	}
	if (event.type == sf::Event::KeyReleased) {
		_pressingSpace = false;
	}
}

void Player::changeSize(sf::Vector2f newSize)
{
	sf::Vector2f textureSize = sf::Vector2f(_texture.getSize());

	_sprite.setScale(sf::Vector2f(newSize.x / textureSize.x, newSize.y / textureSize.y));

	_gravityAccel = _baseGravityAccel * newSize.y;
	_jumpVelocity = _baseJumpVelocity * newSize.y;
	_walkSpeed = _baseWalkSpeed * newSize.x;
	_walkAccel = _baseWalkAccel * newSize.x;
}

void Player::setPosition(sf::Vector2f newPos)
{
	_sprite.setPosition(newPos);
}

void Player::setVelocity(sf::Vector2f newVelocity)
{
	_velocity = newVelocity;
}

void Player::reset(const TileMap& tileMap)
{
	changeSize(tileMap.getTileSize() * 0.90f);
	setPosition(tileMap.getSpawnPosition() + (tileMap.getTileSize() / 2.0f));
	setVelocity(sf::Vector2f(0, 0));

	_wentLeft = false;
	_wentRight = false;

	_canGoLeft = true;
	_canGoRight = true;

	_sprite.setTexture(_texture);
}

sf::Vector2f Player::getSize() const
{
	return sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

sf::Vector2f Player::getScreenPos() const
{
	return _sprite.getPosition();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void Player::move(Game& game, sf::Vector2f movementVector, const TileMap& tileMap)
{
	static const float MIN_SEPERATION = 0.001f;
	static const unsigned int MAX_PHYSICS_ITERATIONS = 5;

	sf::Vector2f playerExtents = sf::Vector2f(_sprite.getGlobalBounds().width / 2.0f, _sprite.getGlobalBounds().height / 2.0f);

	float remainingT = 1.0f;

	for (int k = 0; k < MAX_PHYSICS_ITERATIONS && remainingT > 0.0f; k++) {
		sf::Vector2f startPos = _sprite.getPosition();
		sf::Vector2f endPos = _sprite.getPosition() + movementVector;

		sf::Vector2f minMovement = movementVector;
		float minT = remainingT;
		
		// Check tilemap boundaries
		Edge topBoundary(sf::Vector2f(tileMap.getLevelBounds().left, tileMap.getLevelBounds().top), sf::Vector2f(tileMap.getLevelBounds().left + tileMap.getLevelBounds().width, tileMap.getLevelBounds().top));
		Edge botBoundary(sf::Vector2f(tileMap.getLevelBounds().left + tileMap.getLevelBounds().width, tileMap.getLevelBounds().top + tileMap.getLevelBounds().height), sf::Vector2f(tileMap.getLevelBounds().left, tileMap.getLevelBounds().top + tileMap.getLevelBounds().height));
		Edge leftBoundary(sf::Vector2f(tileMap.getLevelBounds().left, tileMap.getLevelBounds().top + tileMap.getLevelBounds().height), sf::Vector2f(tileMap.getLevelBounds().left, tileMap.getLevelBounds().top));
		Edge rightBoundary(sf::Vector2f(tileMap.getLevelBounds().left + tileMap.getLevelBounds().width, tileMap.getLevelBounds().top), sf::Vector2f(tileMap.getLevelBounds().left + tileMap.getLevelBounds().width, tileMap.getLevelBounds().top + tileMap.getLevelBounds().height));

		sf::Vector2f boundaryIntersection;
		
		float playerT;
		float boundaryT;

		bool looped = false;

		bool hitBottom = false;

		if (lineIntersect(Edge{ startPos, endPos }, topBoundary, boundaryIntersection, &playerT, &boundaryT)) {
			if (playerT < minT) {
				minMovement = sf::Vector2f(boundaryIntersection.x, tileMap.getLevelBounds().top + tileMap.getLevelBounds().height) + (topBoundary.normal * MIN_SEPERATION) - startPos;
				looped = true;
			}
		}
		if (lineIntersect(Edge{ startPos, endPos }, botBoundary, boundaryIntersection, &playerT, &boundaryT)) {
			if (playerT < minT) {
				minMovement = sf::Vector2f(boundaryIntersection.x, tileMap.getLevelBounds().top) + (botBoundary.normal * MIN_SEPERATION) - startPos;
				looped = true;
			}
		}
		if (lineIntersect(Edge{ startPos, endPos }, leftBoundary, boundaryIntersection, &playerT, &boundaryT)) {
			if (playerT < minT) {
				minMovement = sf::Vector2f(tileMap.getLevelBounds().left + tileMap.getLevelBounds().width, boundaryIntersection.y) + (leftBoundary.normal * MIN_SEPERATION) - startPos;
				looped = true;
			}
		}
		if (lineIntersect(Edge{ startPos, endPos }, rightBoundary, boundaryIntersection, &playerT, &boundaryT)) {
			if (playerT < minT) {
				minMovement = sf::Vector2f(tileMap.getLevelBounds().left, boundaryIntersection.y) + (rightBoundary.normal * MIN_SEPERATION) - startPos;
				looped = true;
			}
		}


		sf::Vector2i startTilePos = tileMap.getTilePosFromScreenPos(_sprite.getPosition());
		sf::Vector2i endTilePos = tileMap.getTilePosFromScreenPos(_sprite.getPosition() + movementVector);

		sf::Vector2i topLeftTilePos = sf::Vector2i(startTilePos.x < endTilePos.x ? startTilePos.x : endTilePos.x, startTilePos.y < endTilePos.y ? startTilePos.y : endTilePos.y) - sf::Vector2i(1, 1);
		sf::Vector2i botRightTilePos = sf::Vector2i(startTilePos.x > endTilePos.x ? startTilePos.x : endTilePos.x, startTilePos.y > endTilePos.y ? startTilePos.y : endTilePos.y) + sf::Vector2i(1, 1);

		bool collided = false;
		sf::Vector2f collisionNormal;

		for (int i = topLeftTilePos.x; i != botRightTilePos.x + 1; i++) {
			for (int j = topLeftTilePos.y; j != botRightTilePos.y + 1; j++) {
				if (i < 0 || j < 0 || i >= tileMap.getNumCols() || j >= tileMap.getNumRows()) continue; // Out of tilemap bounds (will want to loop later)

				char tile = tileMap.getTile(sf::Vector2i(i, j));

				if (tile == 0) continue;

				// Check each tile side against movement vector
				Edge topEdge(tileMap.getScreenPosFromTilePos(sf::Vector2i(i, j)) - playerExtents, tileMap.getScreenPosFromTilePos(sf::Vector2i(i + 1, j)) + sf::Vector2f(playerExtents.x, -playerExtents.y));
				Edge botEdge(tileMap.getScreenPosFromTilePos(sf::Vector2i(i + 1, j + 1)) + playerExtents, tileMap.getScreenPosFromTilePos(sf::Vector2i(i, j + 1)) + sf::Vector2f(-playerExtents.x, playerExtents.y));
				Edge leftEdge(tileMap.getScreenPosFromTilePos(sf::Vector2i(i, j + 1)) + sf::Vector2f(-playerExtents.x, playerExtents.y), tileMap.getScreenPosFromTilePos(sf::Vector2i(i, j)) - playerExtents);
				Edge rightEdge(tileMap.getScreenPosFromTilePos(sf::Vector2i(i + 1, j)) + sf::Vector2f(playerExtents.x, -playerExtents.y), tileMap.getScreenPosFromTilePos(sf::Vector2i(i + 1, j + 1)) + playerExtents);


				sf::Vector2f intersectionPoint;
				float nearestT;

				if (lineIntersect(Edge{ startPos, endPos }, topEdge, intersectionPoint, &nearestT, nullptr)) {
					_onGround = true;
					if (nearestT < minT) {
						hitBottom = true;

						looped = false;
						collided = true;
						collisionNormal = topEdge.normal;
						minT = nearestT;
						minMovement = intersectionPoint + (topEdge.normal * MIN_SEPERATION) - startPos;
					}
				}
				if (lineIntersect(Edge{ startPos, endPos }, botEdge, intersectionPoint, &nearestT, nullptr)) {
					if (nearestT < minT) {
						hitBottom = false;

						looped = false;
						collided = true;
						collisionNormal = botEdge.normal;
						minT = nearestT;
						minMovement = intersectionPoint + (botEdge.normal * MIN_SEPERATION) - startPos;
					}
				}
				if (lineIntersect(Edge{ startPos, endPos }, leftEdge, intersectionPoint, &nearestT, nullptr)) {
					if (nearestT < minT) {
						hitBottom = false;

						looped = false;
						collided = true;
						collisionNormal = leftEdge.normal;
						minT = nearestT;
						minMovement = intersectionPoint + (leftEdge.normal * MIN_SEPERATION) - startPos;
					}
				}
				if (lineIntersect(Edge{ startPos, endPos }, rightEdge, intersectionPoint, &nearestT, nullptr)) {
					if (nearestT < minT) {
						hitBottom = false;

						looped = false;
						collided = true;
						collisionNormal = rightEdge.normal;
						minT = nearestT;
						minMovement = intersectionPoint + (rightEdge.normal * MIN_SEPERATION) - startPos;
					}
				}


			}
		}

		if (hitBottom) {
			if (_velocity.y > game.getWindowHeight() * 0.15f) {
				_sound.setBuffer(_impactSound);
				_sound.setVolume(25.f);
				_sound.play();

			}

		}


		_sprite.move(minMovement);
		if (!looped) {
			movementVector = movementVector - (collisionNormal * (dotProduct(movementVector, collisionNormal)));
			_velocity = _velocity - (collisionNormal * (dotProduct(_velocity, collisionNormal)));
		}
		movementVector = movementVector - (collisionNormal * (dotProduct(movementVector, collisionNormal)));
		_velocity = _velocity - (collisionNormal * (dotProduct(_velocity, collisionNormal)));
		remainingT -= minT;
	}
	
}

bool lineIntersect(Edge a, Edge b, sf::Vector2f& intersectPoint, float* aT, float* bT) {
	float tAA = (b.a.y - b.b.y) * (a.a.x - b.a.x) + (b.b.x - b.a.x) * (a.a.y - b.a.y);
	float tAB = (b.b.x - b.a.x) * (a.a.y - a.b.y) - (a.a.x - a.b.x) * (b.b.y - b.a.y);

	float tBA = (a.a.y - a.b.y) * (a.a.x - b.a.x) + (a.b.x - a.a.x) * (a.a.y - b.a.y);
	float tBB = (b.b.x - b.a.x) * (a.a.y - a.b.y) - (a.a.x - a.b.x) * (b.b.y - b.a.y);

	if (tAB == 0.0f || tBB == 0.0f) {
		return false;
	}
	float tA = tAA / tAB;
	float tB = tBA / tBB;

	if (tA >= 0.0f && tA <= 1.0f && tB >= 0.0f && tB <= 1.0f) {

		intersectPoint = a.a + tA * (a.b - a.a);

		if (aT != nullptr) {
			*aT = tA;
		}
		if (bT != nullptr) {
			*bT = tB;
		}

		return true;
	}
	else {
		return false;
	}
}

inline Edge::Edge() {

}

inline Edge::Edge(sf::Vector2f a, sf::Vector2f b) : a(a), b(b)
{
	normal = sf::Vector2f((b - a).y, -(b - a).x);

	float len = vecLength(normal);

	normal /= len;
}
