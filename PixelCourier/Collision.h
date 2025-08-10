// custom collision with every sprite loaded in game

#pragma once
#include <SFML/Graphics.hpp>

#include "Sprites_load.h"

#include <map>


// add the definition of AdjustHitbox function 
// 
// WidthFactor and HeightFactor are the taking factor of the object to remove the collision 
// offset is the moving offset of the colllision figure to be movable

inline sf::FloatRect AdjustHitbox(const sf::Sprite& sprite, float WidthFactor, float HeightFactor, float offset) {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // calculation of the new width and height
    float new_width = bounds.width * WidthFactor;
    float new_height = bounds.height * HeightFactor;

    // shifting 
    bounds.top += bounds.height * offset;

    // centralizing
    bounds.left += (bounds.width - new_width) / 2.0f;

    void Init(Sprites& sprites) {
        std::ifstream file("PixelCourier/hitbox_config.txt");

    return bounds;
}


class Collision {
public:
	std::map<sf::Sprite*, sf::FloatRect> HitBox;

        while (file >> name >> width >> height >> y_offset >> x_offset) {
			
            // TODO: sprites to be z_index 1, map z_index 0, player z-index 2       where no collision with top parts of buildings and objects
            // TODO: player to be able to go from z-index 2 to z-index 0 (because of top parts of buildings) [he goes behind em]

            //player collision box
            if (name == "player") {
                HitBox[&sprites.player] = AdjustHitBox(sprites.player, width, height, y_offset, x_offset);
            }
			// building collision boxes
			else if (name == "block_1") {
				for(auto& sprite : sprites.block_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
				}
			}
			else if (name == "house_1") {
                for(auto& sprite : sprites.house_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "church_1") {
                for(auto& sprite : sprites.church_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
			else if (name == "courier_house") {
                                for(auto& sprite : sprites.courier_house) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
			}
			// other objects collision boxes
			else if (name == "bush_1") {
                for(auto& sprite : sprites.bush_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
			}
			else if (name == "sunbed_1") {
            	for(auto& sprite : sprites.sunbed_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
			}
			else if (name == "blue_umbrella_1") {
                for(auto& sprite : sprites.blue_umbrella_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
			}
			else if (name == "tree_1") {
                for(auto& sprite : sprites.tree_1) {
                    HitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
			}

			//// FIX: fix the vehicle collision boxes 
			//// vehicles collision boxes
   //         else if (name == "car_1_left") {
   //             HitBox[&sprites.car_1_left] = AdjustHitBox(sprites.car_1_left, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "car_1_right") {
   //             HitBox[&sprites.car_1_right] = AdjustHitBox(sprites.car_1_right, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "car_2_left") {
   //             HitBox[&sprites.car_2_left] = AdjustHitBox(sprites.car_2_left, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "car_2_right") {
   //             HitBox[&sprites.car_2_right] = AdjustHitBox(sprites.car_2_right, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "truck_1_left") {
   //             HitBox[&sprites.truck_1_left] = AdjustHitBox(sprites.truck_1_left, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "truck_1_right") {
   //             HitBox[&sprites.truck_1_right] = AdjustHitBox(sprites.truck_1_right, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "pickup_truck_1_left") {
   //             HitBox[&sprites.pickup_truck_1_left] = AdjustHitBox(sprites.pickup_truck_1_left, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "pickup_truck_1_right") {
   //             HitBox[&sprites.pickup_truck_1_right] = AdjustHitBox(sprites.pickup_truck_1_right, width, height, y_offset, x_offset);
   //         } 
   //         else if (name == "bus_1_left") {
   //             HitBox[&sprites.bus_1_left] = AdjustHitBox(sprites.bus_1_left, width, height, y_offset, x_offset);
   //         }
   //         else if (name == "bus_1_right") {
   //             HitBox[&sprites.bus_1_right] = AdjustHitBox(sprites.bus_1_right, width, height, y_offset, x_offset);
			//}

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