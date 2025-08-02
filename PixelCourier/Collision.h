// apply collision border to the object using txt file
// and apply collision logic to the object

#pragma once
#include <SFML/Graphics.hpp>

#include "Sprites_load.h"

#include <map>
#include <fstream>
#include <string>


// add the definition of AdjustHitBox function 
// 
// WidthFactor and HeightFactor are the taking factor of the object to remove/apply the collision to the object in a proper more realistic way 
// x_offset, y_offset are the coordinates of the object to adjust the hitbox position

inline sf::FloatRect AdjustHitBox(const sf::Sprite& sprite, float WidthFactor, float HeightFactor, float y_offset, float x_offset) {
    sf::FloatRect global_bounds = sprite.getGlobalBounds();

    sf::FloatRect relative_bounds;
    relative_bounds.width = global_bounds.width * WidthFactor;
    relative_bounds.height = global_bounds.height * HeightFactor;
	relative_bounds.left = global_bounds.width * x_offset; 
	relative_bounds.top = global_bounds.height * y_offset;  
    return relative_bounds;
}


class Collision {
public:
    std::map<sf::Sprite*, sf::FloatRect> HitBox;

    void Init(Sprites& sprites) {
        std::ifstream file("PixelCourier/hitbox_config.txt");


        if (!file.is_open()) {
            std::cout << "not found the txt!\n";
            return;
        }

        HitBox.clear();

        std::string name;
		float width, height, y_offset, x_offset;

        while (file >> name >> width >> height >> y_offset >> x_offset) {

			
            // TODO: sprites to be z_index 1, map z_index 0, player z-index 2       where no collision with top parts of buildings and objects
            // TODO: player to be able to go from z-index 2 to z-index 0 (because of top parts of buildings) [he goes behind em]

            //player collision box
            if (name == "player") {
                HitBox[&sprites.player] = AdjustHitBox(sprites.player, width, height, y_offset, x_offset);
            }
			// building collision boxes
			else if (name == "block_1") {
				HitBox[&sprites.block_1] = AdjustHitBox(sprites.block_1, width, height, y_offset, x_offset);
			}
			else if (name == "house_1") {
				HitBox[&sprites.house_1] = AdjustHitBox(sprites.house_1, width, height, y_offset, x_offset);
			}
            else if (name == "church_1") {
                HitBox[&sprites.church_1] = AdjustHitBox(sprites.church_1, width, height, y_offset, x_offset);
			}
			else if (name == "courier_house") {
				HitBox[&sprites.courier_house] = AdjustHitBox(sprites.courier_house, width, height, y_offset, x_offset);
			}
			// other objects collision boxes
			else if (name == "bush_1") {
				HitBox[&sprites.bush_1] = AdjustHitBox(sprites.bush_1, width, height, y_offset, x_offset);
			}
			else if (name == "sunbed_1") {
				HitBox[&sprites.sunbed_1] = AdjustHitBox(sprites.sunbed_1, width, height, y_offset, x_offset);
			}
			else if (name == "blue_umbrella_1") {
				HitBox[&sprites.blue_umbrella_1] = AdjustHitBox(sprites.blue_umbrella_1, width, height, y_offset, x_offset);
			}
			else if (name == "tree_1") {
				HitBox[&sprites.tree_1] = AdjustHitBox(sprites.tree_1, width, height, y_offset, x_offset);
			}

			// vehicles collision boxes
            else if (name == "car_1_left") {
                HitBox[&sprites.car_1_left] = AdjustHitBox(sprites.car_1_left, width, height, y_offset, x_offset);
            }
            else if (name == "car_1_right") {
                HitBox[&sprites.car_1_right] = AdjustHitBox(sprites.car_1_right, width, height, y_offset, x_offset);
            }
            else if (name == "car_2_left") {
                HitBox[&sprites.car_2_left] = AdjustHitBox(sprites.car_2_left, width, height, y_offset, x_offset);
            }
            else if (name == "car_2_right") {
                HitBox[&sprites.car_2_right] = AdjustHitBox(sprites.car_2_right, width, height, y_offset, x_offset);
            }
            else if (name == "truck_1_left") {
                HitBox[&sprites.truck_1_left] = AdjustHitBox(sprites.truck_1_left, width, height, y_offset, x_offset);
            }
            else if (name == "truck_1_right") {
                HitBox[&sprites.truck_1_right] = AdjustHitBox(sprites.truck_1_right, width, height, y_offset, x_offset);
            }
            else if (name == "pickup_truck_1_left") {
                HitBox[&sprites.pickup_truck_1_left] = AdjustHitBox(sprites.pickup_truck_1_left, width, height, y_offset, x_offset);
            }
            else if (name == "pickup_truck_1_right") {
                HitBox[&sprites.pickup_truck_1_right] = AdjustHitBox(sprites.pickup_truck_1_right, width, height, y_offset, x_offset);
            } 
            else if (name == "bus_1_left") {
                HitBox[&sprites.bus_1_left] = AdjustHitBox(sprites.bus_1_left, width, height, y_offset, x_offset);
            }
            else if (name == "bus_1_right") {
                HitBox[&sprites.bus_1_right] = AdjustHitBox(sprites.bus_1_right, width, height, y_offset, x_offset);
			}

			// TODO: add copy of building and others sprites with different positions 
        }   
		// test output for visualization of loaded hitboxes
        std::cout << "  load hitboxes " << HitBox.size() << "\n";
    }

	// test function for drawing hitboxes
    void DrawHitBoxes(sf::RenderWindow& window) {
        for (auto it = HitBox.begin(); it != HitBox.end(); ++it) {
            sf::Sprite* sprite = it->first;
            sf::FloatRect rect = it->second;

            // actualization of position of hitbox
            sf::FloatRect global_bounds = sprite->getGlobalBounds(); // position + size
            sf::FloatRect updated;
            updated.left = global_bounds.left + rect.left;   // rect is relative offset
            updated.top = global_bounds.top + rect.top;
            updated.width = rect.width;
            updated.height = rect.height;


            // drawing a test rect
            sf::RectangleShape shape;
            shape.setPosition(updated.left, updated.top);
            shape.setSize(sf::Vector2f(updated.width, updated.height));
            shape.setFillColor(sf::Color(255, 0, 0, 80)); // red rect
            shape.setOutlineThickness(1.f);
            shape.setOutlineColor(sf::Color::Red);

            window.draw(shape);
        }
    }

	// collision logic for map borders
    bool CheckCollisionWithMapBorders(sf::Sprite& player, float map_width, float map_height) {
        sf::FloatRect player_bounds = player.getGlobalBounds();
        // Check if the player is outside the map boundaries
        if (player_bounds.left < 0.0f || player_bounds.top < 0.0f ||
            player_bounds.left + player_bounds.width > map_width ||
            player_bounds.top + player_bounds.height > map_height) {
            return true; // Collision with map borders
        }
        return false; // No collision
	}
};