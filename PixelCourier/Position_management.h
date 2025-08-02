// apply positions to all objects on the map using txt file

#pragma once

#include <SFML/Graphics.hpp>

#include "Textures_load.h"
#include "Sprites_load.h"

#include <fstream>
#include <unordered_map>

// TODO: add few more same objects, few more diff + moving cars with collision logic gameover


class PositionManagement {
public:
	std::map<sf::Sprite*, sf::Vector2f> ObjectPositions;

	void PosInit(Sprites& sprites, Textures& textures) {
		std::ifstream file("PixelCourier/position_config.txt");

		if (!file.is_open()) {
			std::cout << "not found the txt!\n";
			return;
		}

		ObjectPositions.clear();

		std::string name;
		float x_coords, y_coords;

		// positions
		std::unordered_map<std::string, sf::Sprite*> NameToSprite = {
			// starting player position
			{"player", &sprites.player},
			// buildings
			{"house_1", &sprites.house_1},
			{"block_1", &sprites.block_1},
			{"courier_house", &sprites.courier_house},
			{"church_1", &sprites.church_1},
			{"bush_1", &sprites.bush_1},
			// others
			{"sunbed_1", &sprites.sunbed_1},
			{"blue_umbrella_1", &sprites.blue_umbrella_1},
			{"tree_1", &sprites.tree_1},
			{"bush_1", &sprites.bush_1}
		};

		
		while (file >> name >> x_coords >> y_coords) {
			// search the name
			auto it = NameToSprite.find(name);
			if (it == NameToSprite.end()) continue;

			sf::Sprite* sprite = it->second;
			sprite->setPosition(x_coords, y_coords);
			ObjectPositions[sprite] = sf::Vector2f(x_coords, y_coords);
		}
		std::cout << "  load positions " << ObjectPositions.size() << "\n";
	}
};