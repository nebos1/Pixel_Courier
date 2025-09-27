// apply positions to all static objects on the map using txt file
// apply starting position to the player

#pragma once

#include <SFML/Graphics.hpp>

#include "Textures_load.h"
#include "Sprites_load.h"

#include <fstream>
#include <map>
#include <string>


// TODO: add few more same objects, few more diff + moving cars with collision logic gameover


class PositionManagement {
public:
	std::map<sf::Sprite*, sf::Vector2f> ObjectPositions;

	void PosInit(Sprites& sprites, Textures& textures) {
		std::ifstream file("PixelCourier/position_config.txt");


		ObjectPositions.clear();

		// clear the old vectors of all objects before filling them with new sprites and textures for loading
		sprites.house_1.clear();
		sprites.block_1.clear();
		sprites.courier_house.clear();
		sprites.church_1.clear();

		sprites.bush_1.clear();
		sprites.sunbed_1.clear();
		sprites.blue_umbrella_1.clear();
		sprites.tree_1.clear();


		std::string name;
		float x_coords, y_coords;
		while (file >> name >> x_coords >> y_coords) {
			if (name == "player") {
				sprites.player.setTexture(textures.player);
				sprites.player.setPosition(x_coords, y_coords);
				ObjectPositions[&sprites.player] = { x_coords, y_coords };
			}
			else if (name == "house_1") {
				sf::Sprite sprite; sprite.setTexture(textures.house_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.house_1.push_back(sprite);
				ObjectPositions[&sprites.house_1.back()] = { x_coords, y_coords };
			}
			else if (name == "block_1") {
				sf::Sprite sprite; sprite.setTexture(textures.block_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.block_1.push_back(sprite);
				ObjectPositions[&sprites.block_1.back()] = { x_coords, y_coords };
			}
			else if (name == "courier_house") {
				sf::Sprite sprite; sprite.setTexture(textures.courier_house);
				sprite.setPosition(x_coords, y_coords);
				sprites.courier_house.push_back(sprite);
				ObjectPositions[&sprites.courier_house.back()] = { x_coords, y_coords };
			}
			else if (name == "church_1") {
				sf::Sprite sprite; sprite.setTexture(textures.church_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.church_1.push_back(sprite);
				ObjectPositions[&sprites.church_1.back()] = { x_coords, y_coords };
			}
			else if (name == "bush_1") {
				sf::Sprite sprite; sprite.setTexture(textures.bush_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.bush_1.push_back(sprite);
				ObjectPositions[&sprites.bush_1.back()] = { x_coords, y_coords };
			}
			else if (name == "sunbed_1") {
				sf::Sprite sprite; sprite.setTexture(textures.sunbed_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.sunbed_1.push_back(sprite);
				ObjectPositions[&sprites.sunbed_1.back()] = { x_coords, y_coords };
			}
			else if (name == "blue_umbrella_1") {
				sf::Sprite sprite; sprite.setTexture(textures.blue_umbrella_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.blue_umbrella_1.push_back(sprite);
				ObjectPositions[&sprites.blue_umbrella_1.back()] = { x_coords, y_coords };
			}
			else if (name == "tree_1") {
				sf::Sprite sprite; sprite.setTexture(textures.tree_1);
				sprite.setPosition(x_coords, y_coords);
				sprites.tree_1.push_back(sprite);
				ObjectPositions[&sprites.tree_1.back()] = { x_coords, y_coords };
			}
		}

		sprites.CollisionObjects.clear();
		sprites.CollisionObjects.push_back(&sprites.player);

		std::vector<sf::Sprite>::iterator it;

		// buildings
		it = sprites.house_1.begin();
		while (it != sprites.house_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.block_1.begin();
		while (it != sprites.block_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.courier_house.begin();
		while (it != sprites.courier_house.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.church_1.begin();
		while (it != sprites.church_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		// others
		it = sprites.bush_1.begin();
		while (it != sprites.bush_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.sunbed_1.begin();
		while (it != sprites.sunbed_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.blue_umbrella_1.begin();
		while (it != sprites.blue_umbrella_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}

		it = sprites.tree_1.begin();
		while (it != sprites.tree_1.end()) { 
			sprites.CollisionObjects.push_back(&*it); ++it; 
		}
	}
};