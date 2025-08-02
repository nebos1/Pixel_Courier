// player movement + camera vision

#pragma once

#include <SFML/Graphics.hpp>

#include "Sprites_load.h"

#include <algorithm>

#include "Collision.h"


inline void HandlePlayerMovement(sf::Sprite& player, float speed, float map_width, float map_height,     
                                Textures& textures, Collision& collision ) {

    sf::Vector2f movement(0.0, 0.0);

    // player movement based on key presses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed; player.setTexture(textures.left_courier);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed; player.setTexture(textures.right_courier);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed; player.setTexture(textures.back_courier);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed; player.setTexture(textures.front_courier);
    }

    // move the player
    player.move(movement);

	// Check for collisions with map borders
    if (collision.CheckCollisionWithMapBorders(player, map_width, map_height)) {
        // If there is a collision, move the player back
        player.move(-movement);
    }


    // TOFIX: PLAYER COLLISION WITH MAP 

    // player collision with obj
    for (auto it = collision.HitBox.begin(); it != collision.HitBox.end(); ++it) {
        sf::Sprite* sprite = it->first;

        if (sprite == &player) continue; //skip collision with itself

        sf::FloatRect PlayerRectWorld = player.getGlobalBounds();
        auto PlayerHitBox = collision.HitBox.find(&player);

        if (PlayerHitBox != collision.HitBox.end()) {
            const sf::FloatRect global_bounds = player.getGlobalBounds();  // sprite position 
			const sf::FloatRect hit_box = PlayerHitBox->second;  //relative hitbox for Init()

			// object-hitbox with local bounds
            PlayerRectWorld.left = global_bounds.left + hit_box.left;
            PlayerRectWorld.top = global_bounds.top + hit_box.top;
            PlayerRectWorld.width = hit_box.width;
            PlayerRectWorld.height = hit_box.height;
        }

        for (auto it = collision.HitBox.begin(); it != collision.HitBox.end(); ++it) {
            sf::Sprite* sprite = it->first;
			if (sprite == &player) continue; // skip collision with itself

            const sf::FloatRect hit_box = it->second;
            const sf::FloatRect global_bounds = sprite->getGlobalBounds();

            // object-hitbox with local bounds
            sf::FloatRect ObjRectWorld;
            ObjRectWorld.left = global_bounds.left + hit_box.left;
            ObjRectWorld.top = global_bounds.top + hit_box.top;
            ObjRectWorld.width = hit_box.width;
            ObjRectWorld.height = hit_box.height;

            if (PlayerRectWorld.intersects(ObjRectWorld)) {
                player.move(-movement);
                break;
            }
        }
    }
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
