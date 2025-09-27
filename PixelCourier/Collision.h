// apply collision border to the object using txt file
// and apply collision logic to the object

#pragma once
#include <SFML/Graphics.hpp>

#include "Sprites_load.h"
#include "Moving_vehicles.h"

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


struct VehicleHitBoxConfig {
    float width_factor;
    float height_factor;
    float y_offset;
    float x_offset;
};
VehicleHitBoxConfig VehicleHitBoxConfigOBJ;


class Collision {
public:
    // all static hitboxes
    std::map<sf::Sprite*, sf::FloatRect> StaticHitBox;

    std::map<std::string, VehicleHitBoxConfig> VehicleConfig;

    // used for all dynamic objects drawing a hitbox
    // here only makes the visualization of the hitbox for vehicles, no intersection logic
    static void DrawVehicleHitBox(sf::RenderTarget& rt, const std::list<sf::Sprite>& list, const std::string& TypeName,
        std::map<std::string, VehicleHitBoxConfig>& config) {

        // searching if the vehicle type exists in the config map
        std::map<std::string, VehicleHitBoxConfig>::const_iterator c_i_1 = config.find(TypeName);
        if (c_i_1 == config.end()) return; // type not found, exit the function

        const VehicleHitBoxConfig& vhbc = c_i_1->second;

        std::list<sf::Sprite>::const_iterator c_i_2 = list.begin();
        for (; c_i_2 != list.end(); ++c_i_2) {
            const sf::Sprite& s = *c_i_2;

            // getting the relative hitbox and global bounds to calculate the actual position of the hitbox
            sf::FloatRect v_relative_bounds = AdjustHitBox(s, vhbc.width_factor, vhbc.height_factor, vhbc.y_offset, vhbc.x_offset);
            sf::FloatRect v_global_bounds = s.getGlobalBounds();
            sf::FloatRect v_box_pos(v_global_bounds.left + v_relative_bounds.left, v_global_bounds.top + v_relative_bounds.top,
                v_relative_bounds.width, v_relative_bounds.height);

            // drawing a test rect 
            sf::RectangleShape shape(sf::Vector2f(v_box_pos.width, v_box_pos.height));
            shape.setPosition(v_box_pos.left, v_box_pos.top);
            shape.setFillColor(sf::Color(0, 0, 255, 80)); // blue rect // LATER FIX THIS for transparent background
            shape.setOutlineThickness(1.f);
            rt.draw(shape);
        }

    }

    void AddHitBox(Sprites& sprites) {
        std::ifstream file("PixelCourier/hitbox_config.txt");

        StaticHitBox.clear();


        std::string name;
        float width, height, y_offset, x_offset;

        while (file >> name >> width >> height >> y_offset >> x_offset) {
            // FOR STATIC DRAWABLE OBJECTS ONLY
            // 
            //player collision box
            if (name == "player") {
                StaticHitBox[&sprites.player] = AdjustHitBox(sprites.player, width, height, y_offset, x_offset);
            }
            // for building collision boxes
            else if (name == "block_1") {
                for (auto& sprite : sprites.block_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "house_1") {
                for (auto& sprite : sprites.house_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "church_1") {
                for (auto& sprite : sprites.church_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "courier_house") {
                for (auto& sprite : sprites.courier_house) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            // for other objects collision boxes
            else if (name == "bush_1") {
                for (auto& sprite : sprites.bush_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "sunbed_1") {
                for (auto& sprite : sprites.sunbed_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "blue_umbrella_1") {
                for (auto& sprite : sprites.blue_umbrella_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            else if (name == "tree_1") {
                for (auto& sprite : sprites.tree_1) {
                    StaticHitBox[&sprite] = AdjustHitBox(sprite, width, height, y_offset, x_offset);
                }
            }
            // for dynamic objects collision boxes
            else if (name.rfind("car_1_left", 0) == 0 || name.rfind("car_1_right", 0) == 0 ||
                name.rfind("car_2_left", 0) == 0 || name.rfind("car_2_right", 0) == 0 ||
                name.rfind("truck_1_left", 0) == 0 || name.rfind("truck_1_right", 0) == 0 ||
                name.rfind("pickup_truck_1_left", 0) == 0 || name.rfind("pickup_truck_1_right", 0) == 0 ||
                name.rfind("bus_1_left", 0) == 0 || name.rfind("bus_1_right", 0) == 0) {
                VehicleHitBoxConfigOBJ.width_factor = width;
                VehicleHitBoxConfigOBJ.height_factor = height;
                VehicleHitBoxConfigOBJ.y_offset = y_offset;
                VehicleHitBoxConfigOBJ.x_offset = x_offset;
                VehicleConfig[name] = VehicleHitBoxConfigOBJ;
            }

        }
    }

    // test function for drawing hitboxes
    void DrawHitBoxes(sf::RenderWindow& window) {
        for (auto it = StaticHitBox.begin(); it != StaticHitBox.end(); ++it) {
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
            shape.setFillColor(sf::Color(255, 0, 0, 80)); // red rect // LATER FIX THIS for transparent background
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



