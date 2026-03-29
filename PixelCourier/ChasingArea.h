// header for dog chasing arrea - left from church_1

#pragma once

/*
#include <SFML/Graphics.hpp>

#include "Sprites_load.h"
#include "Textures_load.h"
#include "Collision.h"
#include "Player_movement.h"


struct DogAnimation {
    bool is_moving = false; // flag for moving animation
    float fps = 8.0f; // frames per second for animation to change the texture
    float elapsed_time = 0.0f; // time elapsed since last frame change
    bool frame_swap = false; // flag for frame swap

	enum DogPositions {
		UP,
		DOWN,
		LEFT,
		RIGHT
	}
	last_direction = LEFT; // setting default direction to LEFT
};
DogAnimation DogChasing_OBJ;

class CreateDogChasingArea {
	sf::FloatRect dog_chasing_area; // zone where dog activates for chasing

	CreateDogChasingArea() = default;
};
CreateDogChasingArea CreateDogChasingArea_OBJ;

// dog movement and animation update
inline void HandleDogMovement(sf::Sprite& dog, float speed, float delta_time, float chasing_area_width, float chasing_area_height, Textures& textures,
							  Collision& collision, DogAnimation& dog_animation, const sf::FloatRect church_area) {
	sf::Vector2f movement(0.0, 0.0);
	if (!dog_animation.is_moving) return; // if dog is not moving -> exit the function
	// dog movement logic based on last direction
	switch (dog_animation.last_direction) {
		case DogAnimation::LEFT:movement.x -= speed * delta_time;
			break;
		case DogAnimation::RIGHT:movement.x += speed * delta_time;
			break;
		case DogAnimation::UP:movement.y -= speed * delta_time;
			break;
		case DogAnimation::DOWN:movement.y += speed * delta_time;
			break;
	}
	// move the dog
	dog.move(movement);
	
	// update animation
	if(dog_animation.is_moving) { // if dog is actually moving
		dog_animation.elapsed_time += delta_time;
		if (dog_animation.elapsed_time >= 1.0f / dog_animation.fps) {
			dog_animation.elapsed_time -= 1.0f / dog_animation.fps; // reset elapsed time
			dog_animation.frame_swap = !dog_animation.frame_swap; // swap frame
		}
		// add 4 cases depending on which direction dog is moving to apply the texture
		switch (dog_animation.last_direction) {
			case DogAnimation::LEFT:
				dog.setTexture(dog_animation.frame_swap ? textures.dog_1_running_left_1 : textures.dog_1_running_left_2);
				break;
			case DogAnimation::RIGHT:
				dog.setTexture(dog_animation.frame_swap ? textures.dog_1_running_right_1 : textures.dog_1_running_right_2);
				break;
			case DogAnimation::UP:
				dog.setTexture(dog_animation.frame_swap ? textures.dog_1_running_up_1 : textures.dog_1_running_up_2);
				break;
			case DogAnimation::DOWN:
				dog.setTexture(dog_animation.frame_swap ? textures.dog_1_running_down_1 : textures.dog_1_running_down_2);
				break;
		}
	}
}

// activation logic for dog chasing the player when player is in the chasing area
inline void DogChasing(const sf::FloatRect player_box) {

}
*/