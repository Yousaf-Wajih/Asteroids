#include "Game.h"
#include "Asteroid.h"
#include "Player.h"

std::vector<Entity*> Game::entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

sf::SoundBuffer Game::shootSoundBuffer{};
sf::Sound Game::shootSound{};

size_t Game::score{};
float Game::asteroidSpawnTime{};

sf::Text Game::scoreText{};
sf::Font Game::font{};

void Game::begin() {
	font.loadFromFile("font.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(40, 20));
	scoreText.setCharacterSize(48);

	entities.push_back(new Player());
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;

	shootSoundBuffer.loadFromFile("shoot.wav");
	shootSound.setBuffer(shootSoundBuffer);
}

void Game::update(sf::RenderWindow& window, float deltaTime) {
	toAddList.clear();
	toRemoveList.clear();
	window.clear();

	asteroidSpawnTime -= deltaTime;

	for (size_t i = 0; i < entities.size(); i++) {
		entities[i]->update(deltaTime);
		entities[i]->render(window);
	}

	for (const auto& it : toRemoveList) {
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : toAddList) {
		entities.push_back(ptr);
	}

	if (asteroidSpawnTime <= 0.0f) {
		entities.push_back(new Asteroid());
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	}

	scoreText.setString(std::to_string(score));
	window.draw(scoreText);
}
