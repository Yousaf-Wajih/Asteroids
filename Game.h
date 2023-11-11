#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <list>
#include "Entity.h"

class Game {
public:
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static size_t score;

	static sf::SoundBuffer shootSoundBuffer;
	static sf::Sound shootSound;

private:
	static float asteroidSpawnTime;
	static sf::Text scoreText;
	static sf::Font font;

};
