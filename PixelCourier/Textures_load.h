// apply texture to all assets 

#pragma once

#include <SFML/Graphics.hpp>


class Textures {
public:
	// apply player texture
	sf::Texture player;


	// textures from folder assets (and its subfolders)
	//
	// from map
	sf::Texture map; // Map texture (used as background img)

	// from courier
	sf::Texture front_courier;
	sf::Texture back_courier;
	sf::Texture left_courier;
	sf::Texture right_courier;

	// from buildings
	sf::Texture house_1;
	sf::Texture block_1;
	sf::Texture courier_house;

	// from other
	sf::Texture bush_1;
	sf::Texture sunbed_1;
	sf::Texture blue_umbrella_1;
	sf::Texture tree_1;

	bool LoadAllTextures();
};

// load all textures from files
inline bool Textures::LoadAllTextures() {
	return

		// from player
		player.loadFromFile("assets/courier/front_view_courier.png") &&

		// from map
		map.loadFromFile("assets/map/map.png") &&

		// from courier
		front_courier.loadFromFile("assets/courier/front_view_courier.png") &&
		back_courier.loadFromFile("assets/courier/back_view_courier.png") &&
		left_courier.loadFromFile("assets/courier/left_view_courier.png") &&
		right_courier.loadFromFile("assets/courier/right_view_courier.png") &&

		// from buildings
		house_1.loadFromFile("assets/buildings/house_1.png") &&
		block_1.loadFromFile("assets/buildings/block_1.png") &&
		courier_house.loadFromFile("assets/buildings/courier_house.png") &&

		// from other
		bush_1.loadFromFile("assets/other/bush_1.png") &&
		sunbed_1.loadFromFile("assets/other/sunbed_1.png") &&
		blue_umbrella_1.loadFromFile("assets/other/blue_umbrella_1.png") &&
		tree_1.loadFromFile("assets/other/tree_1.png");
}



