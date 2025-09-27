// player movement + camera vision

#pragma once

#include <SFML/Graphics.hpp>

#include "Sprites_load.h"
#include "Collision.h"

#include <algorithm>



struct Animation {
    bool is_moving = false; // flag for moving animation
    float fps = 8.0f; // frames per second for animation to change the texture
    float elapsed_time = 0.0f; // time elapsed since last frame change
    bool frame_swap = false; // flag for frame swap

    enum direction { // for keeping track of last direction
        UP,
        DOWN,
        LEFT,
        RIGHT
    }
    last_direction = LEFT; // setting default direction to LEFT
    // also used in switch case for animation change depending on last direction
    // NOTE: last_direction uses last know direction of player movement, which does not insta change when another movement kay is pressed
};
Animation Animation_OBJ;

// NOTE: for the player we take
inline void HandlePlayerMovement(sf::Sprite& player, float speed, float map_width, float map_height,
    Textures& textures, Collision& collision, Animation& animation, float delta_time) {

    sf::Vector2f movement(0.0, 0.0);
    animation.is_moving = false; // reset moving flag
    bool moving_up = false, moving_down = false, moving_left = false, moving_right = false;

    // player movement based on key presses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed * delta_time;
        moving_left = true;
        animation.is_moving = true;
        animation.last_direction = Animation::LEFT; // update last direction
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed * delta_time;
        moving_right = true;
        animation.is_moving = true;
        animation.last_direction = Animation::RIGHT; // update last direction
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed * delta_time;
        moving_up = true;
        animation.is_moving = true;
        animation.last_direction = Animation::UP; // update last direction
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed * delta_time;
        moving_down = true;
        animation.is_moving = true;
        animation.last_direction = Animation::DOWN; // update last direction
    }

    // move the player
    player.move(movement);


    // Check for collisions with map borders
    if (collision.CheckCollisionWithMapBorders(player, map_width, map_height)) {
        // If there is a collision, move the player back
        player.move(-movement);
    }


    // update animation 
    if (animation.is_moving) { // if player is actually moving
        // idling (no texture swaps)
        animation.elapsed_time += delta_time;
        if (animation.elapsed_time >= 1.0f / animation.fps) {
            animation.elapsed_time -= 1.0f / animation.fps; // reset elapsed time
            animation.frame_swap = !animation.frame_swap; // swap frame
        }
        // add 4 cases depending on which direction player is moving to apply the texture
        switch (animation.last_direction) {
        case Animation::LEFT:
            player.setTexture(animation.frame_swap ? textures.left_moving_courier_1 : textures.left_courier);
            break;
        case Animation::RIGHT:
            player.setTexture(animation.frame_swap ? textures.right_moving_courier_1 : textures.right_courier);
            break;
        case Animation::UP:
            player.setTexture(animation.frame_swap ? textures.top_moving_courier_1 : textures.top_moving_courier_2);
            break;
        case Animation::DOWN:
            player.setTexture(animation.frame_swap ? textures.bottom_moving_courier_1 : textures.bottom_moving_courier_2);
            break;
        }
    }
    // idling
    else {
        animation.frame_swap = false;
        switch (animation.last_direction) {
        case Animation::LEFT:
            player.setTexture(textures.left_courier);
            break;
        case Animation::RIGHT:
            player.setTexture(textures.right_courier);
            break;
        case Animation::UP:
            player.setTexture(textures.front_courier);
            break;
        case Animation::DOWN:
            player.setTexture(textures.back_courier);
            break;
        }
    }





    // player collision with obj
    for (auto it = collision.StaticHitBox.begin(); it != collision.StaticHitBox.end(); ++it) {
        sf::Sprite* sprite = it->first;

        if (sprite == &player) continue; //skip collision with itself

        sf::FloatRect PlayerRectWorld = player.getGlobalBounds();
        auto PlayerHitBox = collision.StaticHitBox.find(&player);

        if (PlayerHitBox != collision.StaticHitBox.end()) {
            const sf::FloatRect global_bounds = player.getGlobalBounds();  // sprite position 
            const sf::FloatRect hit_box = PlayerHitBox->second;  //relative hitbox for Init()

            // object-hitbox with local bounds
            PlayerRectWorld.left = global_bounds.left + hit_box.left;
            PlayerRectWorld.top = global_bounds.top + hit_box.top;
            PlayerRectWorld.width = hit_box.width;
            PlayerRectWorld.height = hit_box.height;
        }

        for (auto it = collision.StaticHitBox.begin(); it != collision.StaticHitBox.end(); ++it) {
            sf::Sprite* sprite = it->first;
            if (sprite == &player) continue; // skip collision with itself

            const sf::FloatRect hit_box = it->second;
            const sf::FloatRect global_bounds = sprite->getGlobalBounds();

            // object hitbox with local bounds
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