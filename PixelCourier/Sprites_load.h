// applying sprites to textures

#pragma once

#include <SFML/Graphics.hpp>

#include "Textures_load.h"

#include <vector> // for collision logic to objects

class Sprites {
public:

	// Player sprite
	sf::Sprite player;

	// Map 
	sf::Sprite map;

	// Courier 
	sf::Sprite front_courier;
	sf::Sprite back_courier;
	sf::Sprite left_courier;
	sf::Sprite right_courier;
	sf::Sprite backpack_courier;

	// Buildings 
	sf::Sprite house_1;
	sf::Sprite block_1;
	sf::Sprite courier_house;

	// Others
	sf::Sprite bush_1;
	sf::Sprite sunbed_1;
	sf::Sprite blue_umbrella_1;
	sf::Sprite tree_1;

	// Make vector collecting all sprites and making a collision logic
	std::vector<sf::Sprite*> CollisionObjects;

	void CreateAllSprites(Textures& textures);
};



inline void Sprites::CreateAllSprites(Textures& textures) {
	// create player sprite
	player.setTexture(textures.front_courier); 

	// create map sprit
	map.setTexture(textures.map);

	// create building sprites
	house_1.setTexture(textures.house_1);
	block_1.setTexture(textures.block_1);
	courier_house.setTexture(textures.courier_house);

	// create other sprites
	bush_1.setTexture(textures.bush_1);
	sunbed_1.setTexture(textures.sunbed_1);
	blue_umbrella_1.setTexture(textures.blue_umbrella_1);
	tree_1.setTexture(textures.tree_1);

	// Collision logic
	CollisionObjects = {
		&house_1, &block_1, &courier_house,
		&bush_1, &sunbed_1, &blue_umbrella_1, &tree_1
	};
}