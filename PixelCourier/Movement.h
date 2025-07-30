// player movement + camera vision

#pragma once

#include <SFML/Graphics.hpp>

#include "Sprites_load.h"

#include <algorithm>


// function for movement
inline void HandlePlayerMovement(sf::Sprite& player, float speed, float map_width, float map_height, Textures& textures, const std::vector<sf::Sprite*>& CollisionObjects) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;
		player.setTexture(textures.left_courier); // Change texture to left view
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
		player.setTexture(textures.right_courier); // Change texture to right view
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed;
		player.setTexture(textures.back_courier); // Change texture to up view
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;
		player.setTexture(textures.front_courier); // Change texture to down view
    }

    // Move the player
    player.move(movement);

    // Clamp player's position so he cannot leave the map
    sf::Vector2f pos = player.getPosition();
    sf::FloatRect bounds = player.getGlobalBounds();

    // Left and top boundaries
    if (pos.x < 0.f) pos.x = 0.f;
    if (pos.y < 0.f) pos.y = 0.f;

    // Right and bottom boundaries (consider sprite size)
    if (pos.x + bounds.width > map_width) pos.x = map_width - bounds.width;
    if (pos.y + bounds.height > map_height) pos.y = map_height - bounds.height;

    // Apply corrected position
    player.setPosition(pos);

}




// function for camera movement + vision  
inline void HandleCameraView(sf::Sprite& player, sf::View& camera, float map_width, float map_height) {
    sf::Vector2f camera_position = player.getPosition();

    // when player near border, camera to stay in map borders (no outside map vision)
    float inline_width = camera.getSize().x / 2.0f;
    float inline_height = camera.getSize().y / 2.0f;

    if (camera_position.x < inline_width) {
        camera_position.x = inline_width;
    }
    else if (camera_position.x > map_width - inline_width) {
        camera_position.x = map_width - inline_width;
    }

    if (camera_position.y < inline_height) {
        camera_position.y = inline_height;
    }
    else if (camera_position.y > map_height - inline_height) {
        camera_position.y = map_height - inline_height;
    }

    camera.setCenter(camera_position);

}
