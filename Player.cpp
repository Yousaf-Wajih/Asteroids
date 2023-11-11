#include "Player.h"
#include "Bullet.h"
#include "Global.h"
#include "Game.h"

Player::Player()
	: Entity(sf::Vector2f(500, 500), 0), array(sf::LinesStrip, 5), shootTimer() {
	array[0].position = sf::Vector2f(20, 0);
	array[1].position = sf::Vector2f(-30, -20);
	array[2].position = sf::Vector2f(-15, 0);
	array[3].position = sf::Vector2f(-30, 20);
	array[4].position = array[0].position;

	for (size_t i = 0; i < array.getVertexCount(); i++) {
		array[i].color = sf::Color::White;
	}
}

void Player::update(float deltaTime) {
	shootTimer -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= TURN_SPEED * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += TURN_SPEED * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		float radians = angle * (M_PI / 180.0f);

		position.x += cos(radians) * PLAYER_SPEED * deltaTime;
		position.y += sin(radians) * PLAYER_SPEED * deltaTime;

		position.x = std::min(std::max(position.x, PLAYER_W / 2.0f),
			SCREEN_WIDTH - PLAYER_W / 2.0f);
		position.y = std::min(std::max(position.y, PLAYER_H / 2.0f),
			SCREEN_HEIGHT - PLAYER_H / 2.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
		Game::shootSound.play();
		shootTimer = SHOOT_DELAY;

		float radians = angle * (M_PI / 180.0f);

		Game::toAddList.push_back(
			new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
	}
}

void Player::render(sf::RenderWindow& window) {
	window.draw(array, sf::Transform().translate(position).rotate(angle));
}
