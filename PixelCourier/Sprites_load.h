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

	// Buildings 
	sf::Sprite house_1;
	sf::Sprite block_1;
	sf::Sprite courier_house;
	sf::Sprite church_1;

	// Others
	sf::Sprite bush_1;
	sf::Sprite sunbed_1;
	sf::Sprite blue_umbrella_1;
	sf::Sprite tree_1;

	// from vehicles
	sf::Sprite car_1_left;
	sf::Sprite car_1_right;
	sf::Sprite car_2_left;
	sf::Sprite car_2_right;
	sf::Sprite truck_1_left;
	sf::Sprite truck_1_right;
	sf::Sprite pickup_truck_1_left;
	sf::Sprite pickup_truck_1_right;
	sf::Sprite bus_1_left;
	sf::Sprite bus_1_right;


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
	church_1.setTexture(textures.church_1);

	// create other sprites
	bush_1.setTexture(textures.bush_1);
	sunbed_1.setTexture(textures.sunbed_1);
	blue_umbrella_1.setTexture(textures.blue_umbrella_1);
	tree_1.setTexture(textures.tree_1);

	// create vehicle sprites
	car_1_left.setTexture(textures.car_1_left);
	car_1_right.setTexture(textures.car_1_right);
	car_2_left.setTexture(textures.car_2_left);
	car_2_right.setTexture(textures.car_2_right);
	truck_1_left.setTexture(textures.truck_1_left);
	truck_1_right.setTexture(textures.truck_1_right);
	pickup_truck_1_left.setTexture(textures.pickup_truck_1_left);
	pickup_truck_1_right.setTexture(textures.pickup_truck_1_right);


	// Collision logic
	CollisionObjects = {
		// player
		&player,
		// buildings
		&house_1, &block_1, &courier_house, &church_1,
		// other objects
		&bush_1, &sunbed_1, &blue_umbrella_1, &tree_1,
		// vehicles
		&car_1_left, &car_1_right, &car_2_left, &car_2_right,
		&truck_1_left, &truck_1_right, &pickup_truck_1_left, &pickup_truck_1_right
	};
}