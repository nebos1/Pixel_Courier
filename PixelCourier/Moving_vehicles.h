// traffic simulation with moving 
// using 2d coordinate system to spawn, move and despawn vehicles

#pragma once

#include "SFML/Graphics.hpp"

#include "Sprites_load.h"
#include "Textures_load.h"

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <random> // for rand()
#include <cmath> // for std::fabs()

// helper function to generate random float for spawn interval
inline float randomize() {
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}
inline float rand_interval(float a, float b) { 
	return a + randomize() * (b - a);
}
// used for deleting the sprite vehicle from the map
template <typename Container>
static bool erase_container(Container& container, sf::Sprite* sprite) {
	typename Container::iterator it = container.begin();
	for (; it != container.end(); ++it) {
		if (&(*it) == sprite) { 
			container.erase(it); return true; 
		}
	}
	return false;
}
// for despawning
static bool DespawnSprite(Sprites& sprites, sf::Sprite* spr) {
	return erase_container(sprites.car_1_left, spr) ||
		   erase_container(sprites.car_1_right, spr) ||
		   erase_container(sprites.car_2_left, spr) ||
		   erase_container(sprites.car_2_right, spr) ||
		   erase_container(sprites.truck_1_left, spr) ||
		   erase_container(sprites.truck_1_right, spr) ||
		   erase_container(sprites.pickup_truck_1_left, spr) ||
		   erase_container(sprites.pickup_truck_1_right, spr) ||
		   erase_container(sprites.bus_1_left, spr) ||
		   erase_container(sprites.bus_1_right, spr);
}

// here are the required configs for vehicles and lanes 
struct LaneConfig {
	int lane; // 1,2,3...16			every road has 2 lanes
	float starting_x; // starting x coords pos
	float ending_x; // ending x coords pos
	float position_y; // position depending on y coords
	float speed; // pixels per second
	std::string direction;
	float spawn_interval = rand_interval(0.5f, 1.7f);
	float accumulator = 0.0f; // accumulated time
	bool has_lane = false; // falg to check if the lane exist
};
LaneConfig LaneConfigOBJ;


// function to group the vehicles by 2 groups -> left and right moving
// randomly to take a vehicles from one of the 2 groups, giving it starting_x + position_y and returning a pointer 
sf::Sprite* RandomSpawningVehicles(Sprites& sprites, Textures& textures, float startX, float posY, const std::string& dir) {


	int random_vehicle = rand() % 5; // random vehicle type 0,1,2,3,4

	if (dir == "left") {
		switch (random_vehicle) {
		case 0: // car_1_left
			sprites.car_1_left.emplace_back(textures.car_1_left);
			sprites.car_1_left.back().setPosition(startX, posY);
			return &sprites.car_1_left.back();
		case 1:
			// car_2_left
			sprites.car_2_left.emplace_back(textures.car_2_left);
			sprites.car_2_left.back().setPosition(startX, posY);
			return &sprites.car_2_left.back();
		case 2:
			// truck_1_left
			sprites.truck_1_left.emplace_back(textures.truck_1_left);
			sprites.truck_1_left.back().setPosition(startX, posY);
			return &sprites.truck_1_left.back();
		case 3:
			// pickup_truck_1_left
			sprites.pickup_truck_1_left.emplace_back(textures.pickup_truck_1_left);
			sprites.pickup_truck_1_left.back().setPosition(startX, posY);
			return &sprites.pickup_truck_1_left.back();
		case 4:
			// bus_1_left
			sprites.bus_1_left.emplace_back(textures.bus_1_left);
			sprites.bus_1_left.back().setPosition(startX, posY);
			return &sprites.bus_1_left.back();
		}
	}
	else if (dir == "right") {
		switch (random_vehicle) {
		case 0: // car_1_right
			sprites.car_1_right.emplace_back(textures.car_1_right);
			sprites.car_1_right.back().setPosition(startX, posY);
			return &sprites.car_1_right.back();
		case 1: // car_2_right
			sprites.car_2_right.emplace_back(textures.car_2_right);
			sprites.car_2_right.back().setPosition(startX, posY);
			return &sprites.car_2_right.back();
		case 2: // truck_1_right
			sprites.truck_1_right.emplace_back(textures.truck_1_right);
			sprites.truck_1_right.back().setPosition(startX, posY);
			return &sprites.truck_1_right.back();
		case 3: // pickup_truck_1_right
			sprites.pickup_truck_1_right.emplace_back(textures.pickup_truck_1_right);
			sprites.pickup_truck_1_right.back().setPosition(startX, posY);
			return &sprites.pickup_truck_1_right.back();
		case 4: // bus_1_right
			sprites.bus_1_right.emplace_back(textures.bus_1_right);
			sprites.bus_1_right.back().setPosition(startX, posY);
			return &sprites.bus_1_right.back();
		}
	}
	return nullptr; // if something wrong happens
}


// class with constructor (spawner) and destructor (despawner) for in game spawn, despawn and moving the vehicles across the map
class ActiveVehicles {
private:
	sf::Sprite* sprite{ nullptr }; 
	float speed;
	float ending_x;
	float starting_x;
	int int_direction { +1 }; // +1 right moving, -1 left moving

	sf::FloatRect v_hitbox; // vehicle hitbox for collision detection
public:
	ActiveVehicles(sf::Sprite* s, float spd, float startx, float endx, int int_dir) : 
		sprite(s), speed(spd), starting_x(startx), ending_x(endx), int_direction(int_dir) {

	}


	~ActiveVehicles() {}

	// return the pointer to the exact sprite 
	// used for deleting the exact sprite of the vehicle when reaches ending_x
	sf::Sprite* spritePtr() const { return sprite; }


	// func to update the position of the vehicle based on its speed and direction in real time with each frame
	void update(float delta_time) {
		if (!sprite) return;
		sprite->move(int_direction * speed * delta_time, 0.f);

	}

	// boolean to check if the vehicle has reached its ending x position for despawn
	bool ReachedEnd() const {
		if (!sprite) return true;
		float get_x_pos = sprite->getPosition().x;
		return (int_direction > 0) ? (get_x_pos >= ending_x) : (get_x_pos <= ending_x);
	}
};


// class for calling the class ActiveVehicles and the func RandomSpawningVehicles
// here reads the txt file with params in it for every lane, creates the vehicles on the map and starts moving them
// to simulate traffic
class Movement {
public:
	Movement() = default;

	// reading a txt file for getting 1st which lane 
	void PosInit(Sprites& sprites, Textures& textures) {
		std::ifstream file("PixelCourier/vehicle_movement.txt");

		// clear the sprites before filling them with new ones
		sprites.car_1_left.clear();  
		sprites.car_1_right.clear(); 
		sprites.car_2_left.clear();  
		sprites.car_2_right.clear(); 
		sprites.truck_1_left.clear();  
		sprites.truck_1_right.clear(); 
		sprites.pickup_truck_1_left.clear();  
		sprites.pickup_truck_1_right.clear(); 
		sprites.bus_1_left.clear(); 
		sprites.bus_1_right.clear();

		active.clear();

		// traverse the arr of lanes starting from the 1st lane
		for (int i = 1; i <= 16; ++i) lanes[i] = LaneConfig{};


		while (file >> LaneConfigOBJ.lane >> LaneConfigOBJ.starting_x >> LaneConfigOBJ.ending_x >> 
					   LaneConfigOBJ.position_y >> LaneConfigOBJ.speed >> LaneConfigOBJ.direction) {

			
			if (LaneConfigOBJ.lane == 1) {
				lanes[1] = LaneConfigOBJ; lanes[1].has_lane = true;
				lanes[1].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[1].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[1].starting_x, lanes[1].position_y, lanes[1].direction)) {
					int int_dir = (lanes[1].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[1].speed,lanes[1].starting_x, lanes[1].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 2) {
				lanes[2] = LaneConfigOBJ; lanes[2].has_lane = true;
				lanes[2].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[2].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[2].starting_x, lanes[2].position_y, lanes[2].direction)) {
					int int_dir = (lanes[2].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[2].speed, lanes[2].starting_x, lanes[2].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 3) {
				lanes[3] = LaneConfigOBJ; lanes[3].has_lane = true;
				lanes[3].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[3].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[3].starting_x, lanes[3].position_y, lanes[3].direction)) {
					int int_dir = (lanes[3].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[3].speed, lanes[3].starting_x, lanes[3].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 4) {
				lanes[4] = LaneConfigOBJ; lanes[4].has_lane = true;
				lanes[4].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[4].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[4].starting_x, lanes[4].position_y, lanes[4].direction)) {
					int int_dir = (lanes[4].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[4].speed,
					lanes[4].starting_x, lanes[4].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 5) {
				lanes[5] = LaneConfigOBJ; lanes[5].has_lane = true;
				lanes[5].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[5].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[5].starting_x, lanes[5].position_y, lanes[5].direction)) {
					int int_dir = (lanes[5].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[5].speed, lanes[5].starting_x, lanes[5].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 6) {
				lanes[6] = LaneConfigOBJ; lanes[6].has_lane = true;
				lanes[6].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[6].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[6].starting_x, lanes[6].position_y, lanes[6].direction)) {
					int int_dir = (lanes[6].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[6].speed, lanes[6].starting_x, lanes[6].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 7) {
				lanes[7] = LaneConfigOBJ; lanes[7].has_lane = true;
				lanes[7].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[7].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[7].starting_x, lanes[7].position_y, lanes[7].direction)) {
					int int_dir = (lanes[7].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[7].speed, lanes[7].starting_x, lanes[7].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 8) {
				lanes[8] = LaneConfigOBJ; lanes[8].has_lane = true;
				lanes[8].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[8].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[8].starting_x, lanes[8].position_y, lanes[8].direction)) {
					int int_dir = (lanes[8].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[8].speed, lanes[8].starting_x, lanes[8].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 9) {
				lanes[9] = LaneConfigOBJ; lanes[9].has_lane = true;
				lanes[9].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[9].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[9].starting_x, lanes[9].position_y, lanes[9].direction)) {
					int int_dir = (lanes[9].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[9].speed, lanes[9].starting_x, lanes[9].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 10) {
				lanes[10] = LaneConfigOBJ; lanes[10].has_lane = true;
				lanes[10].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[10].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[10].starting_x, lanes[10].position_y, lanes[10].direction)) {
					int int_dir = (lanes[10].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[10].speed, lanes[10].starting_x, lanes[10].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 11) {
				lanes[11] = LaneConfigOBJ; lanes[11].has_lane = true;
				lanes[11].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[11].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[11].starting_x, lanes[11].position_y, lanes[11].direction)) {
					int int_dir = (lanes[11].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[11].speed, lanes[11].starting_x, lanes[11].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 12) {
				lanes[12] = LaneConfigOBJ; lanes[12].has_lane = true;
				lanes[12].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[12].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[12].starting_x, lanes[12].position_y, lanes[12].direction)) {
					int int_dir = (lanes[12].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[12].speed, lanes[12].starting_x, lanes[12].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 13) {
				lanes[13] = LaneConfigOBJ; lanes[13].has_lane = true;
				lanes[13].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[13].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[13].starting_x, lanes[13].position_y, lanes[13].direction)) {
					int int_dir = (lanes[13].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[13].speed, lanes[13].starting_x, lanes[13].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 14) {
				lanes[14] = LaneConfigOBJ; lanes[14].has_lane = true;
				lanes[14].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[14].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[14].starting_x, lanes[14].position_y, lanes[14].direction)) {
					int int_dir = (lanes[14].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[14].speed, lanes[14].starting_x, lanes[14].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 15) {
				lanes[15] = LaneConfigOBJ; lanes[15].has_lane = true;
				lanes[15].spawn_interval = rand_interval(0.5f, 1.7f); 
				lanes[15].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[15].starting_x, lanes[15].position_y, lanes[15].direction)) {
					int int_dir = (lanes[15].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[15].speed, lanes[15].starting_x, lanes[15].ending_x, int_dir);
				}
			}
			else if (LaneConfigOBJ.lane == 16) {
				lanes[16] = LaneConfigOBJ; lanes[16].has_lane = true;
				lanes[16].spawn_interval = rand_interval(0.5f, 1.7f); lanes[16].accumulator = 0.f;

				if (sf::Sprite* sprite = RandomSpawningVehicles(sprites, textures,
					lanes[16].starting_x, lanes[16].position_y, lanes[16].direction)) {
					int int_dir = (lanes[16].direction == "left") ? -1 : +1;
					active.emplace_back(sprite, lanes[16].speed, lanes[16].starting_x, lanes[16].ending_x, int_dir);
				}
			}
		}
	}
	void Update(float dt, Sprites& sprites, Textures& textures) {
		if (lanes[1].has_lane) {
			lanes[1].accumulator += dt;
			if (lanes[1].accumulator >= lanes[1].spawn_interval) {
				lanes[1].accumulator = 0.f;
				lanes[1].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[1].starting_x, lanes[1].position_y, lanes[1].direction)) {
					int int_dir = (lanes[1].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[1].speed, lanes[1].starting_x, lanes[1].ending_x, int_dir);
				}
			}
		}
		if (lanes[2].has_lane) {
			lanes[2].accumulator += dt;
			if (lanes[2].accumulator >= lanes[2].spawn_interval) {
				lanes[2].accumulator = 0.f;
				lanes[2].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[2].starting_x, lanes[2].position_y, lanes[2].direction)) {
					int int_dir = (lanes[2].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[2].speed, lanes[2].starting_x, lanes[2].ending_x, int_dir);
				}
			}
		}
		if (lanes[3].has_lane) {
			lanes[3].accumulator += dt;
			if (lanes[3].accumulator >= lanes[3].spawn_interval) {
				lanes[3].accumulator = 0.f;
				lanes[3].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[3].starting_x, lanes[3].position_y, lanes[3].direction)) {
					int int_dir = (lanes[3].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[3].speed, lanes[3].starting_x, lanes[3].ending_x, int_dir);
				}
			}
		}
		if (lanes[4].has_lane) {
			lanes[4].accumulator += dt;
			if (lanes[4].accumulator >= lanes[4].spawn_interval) {
				lanes[4].accumulator = 0.f;
				lanes[4].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[4].starting_x, lanes[4].position_y, lanes[4].direction)) {
					int int_dir = (lanes[4].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[4].speed, lanes[4].starting_x, lanes[4].ending_x, int_dir);
				}
			}
		}
		if (lanes[5].has_lane) {
			lanes[5].accumulator += dt;
			if (lanes[5].accumulator >= lanes[5].spawn_interval) {
				lanes[5].accumulator = 0.f;
				lanes[5].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[5].starting_x, lanes[5].position_y, lanes[5].direction)) {
					int int_dir = (lanes[5].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[5].speed, lanes[5].starting_x, lanes[5].ending_x, int_dir);
				}
			}
		}
		if (lanes[6].has_lane) {
			lanes[6].accumulator += dt;
			if (lanes[6].accumulator >= lanes[6].spawn_interval) {
				lanes[6].accumulator = 0.f;
				lanes[6].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[6].starting_x, lanes[6].position_y, lanes[6].direction)) {
					int int_dir = (lanes[6].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[6].speed, lanes[6].starting_x, lanes[6].ending_x, int_dir);
				}
			}
		}
		if (lanes[7].has_lane) {
			lanes[7].accumulator += dt;
			if (lanes[7].accumulator >= lanes[7].spawn_interval) {
				lanes[7].accumulator = 0.f;
				lanes[7].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[7].starting_x, lanes[7].position_y, lanes[7].direction)) {
					int int_dir = (lanes[7].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[7].speed, lanes[7].starting_x, lanes[7].ending_x, int_dir);
				}
			}
		}
		if (lanes[8].has_lane) {
			lanes[8].accumulator += dt;
			if (lanes[8].accumulator >= lanes[8].spawn_interval) {
				lanes[8].accumulator = 0.f;
				lanes[8].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[8].starting_x, lanes[8].position_y, lanes[8].direction)) {
					int int_dir = (lanes[8].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[8].speed, lanes[8].starting_x, lanes[8].ending_x, int_dir);
				}
			}
		}
		if (lanes[9].has_lane) {
			lanes[9].accumulator += dt;
			if (lanes[9].accumulator >= lanes[9].spawn_interval) {
				lanes[9].accumulator = 0.f;
				lanes[9].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[9].starting_x, lanes[9].position_y, lanes[9].direction)) {
					int int_dir = (lanes[9].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[9].speed, lanes[9].starting_x, lanes[9].ending_x, int_dir);
				}
			}
		}
		if (lanes[10].has_lane) {
			lanes[10].accumulator += dt;
			if (lanes[10].accumulator >= lanes[10].spawn_interval) {
				lanes[10].accumulator = 0.f;
				lanes[10].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[10].starting_x, lanes[10].position_y, lanes[10].direction)) {
					int int_dir = (lanes[10].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[10].speed, lanes[10].starting_x, lanes[10].ending_x, int_dir);
				}
			}
		}
		if (lanes[11].has_lane) {
			lanes[11].accumulator += dt;
			if (lanes[11].accumulator >= lanes[11].spawn_interval) {
				lanes[11].accumulator = 0.f;
				lanes[11].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[11].starting_x, lanes[11].position_y, lanes[11].direction)) {
					int int_dir = (lanes[11].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[11].speed, lanes[11].starting_x, lanes[11].ending_x, int_dir);
				}
			}
		}
		if (lanes[12].has_lane) {
			lanes[12].accumulator += dt;
			if (lanes[12].accumulator >= lanes[12].spawn_interval) {
				lanes[12].accumulator = 0.f;
				lanes[12].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[12].starting_x, lanes[12].position_y, lanes[12].direction)) {
					int int_dir = (lanes[12].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[12].speed, lanes[12].starting_x, lanes[12].ending_x, int_dir);
				}
			}
		}
		if (lanes[13].has_lane) {
			lanes[13].accumulator += dt;
			if (lanes[13].accumulator >= lanes[13].spawn_interval) {
				lanes[13].accumulator = 0.f;
				lanes[13].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[13].starting_x, lanes[13].position_y, lanes[13].direction)) {
					int int_dir = (lanes[13].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[13].speed, lanes[13].starting_x, lanes[13].ending_x, int_dir);
				}
			}
		}
		if (lanes[14].has_lane) {
			lanes[14].accumulator += dt;
			if (lanes[14].accumulator >= lanes[14].spawn_interval) {
				lanes[14].accumulator = 0.f;
				lanes[14].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[14].starting_x, lanes[14].position_y, lanes[14].direction)) {
					int int_dir = (lanes[14].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[14].speed, lanes[14].starting_x, lanes[14].ending_x, int_dir);
				}
			}
		}
		if (lanes[15].has_lane) {
			lanes[15].accumulator += dt;
			if (lanes[15].accumulator >= lanes[15].spawn_interval) {
				lanes[15].accumulator = 0.f;
				lanes[15].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[15].starting_x, lanes[15].position_y, lanes[15].direction)) {
					int int_dir = (lanes[15].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[15].speed, lanes[15].starting_x, lanes[15].ending_x, int_dir);
				}
			}
		}
		if (lanes[16].has_lane) {
			lanes[16].accumulator += dt;
			if (lanes[16].accumulator >= lanes[16].spawn_interval) {
				lanes[16].accumulator = 0.f;
				lanes[16].spawn_interval = rand_interval(0.5f, 1.7f);
				if (auto* s = RandomSpawningVehicles(sprites, textures, lanes[16].starting_x, lanes[16].position_y, lanes[16].direction)) {
					int int_dir = (lanes[16].direction == "left") ? -1 : +1;
					active.emplace_back(s, lanes[16].speed, lanes[16].starting_x, lanes[16].ending_x, int_dir);
				}
			}
		}
		// this moves the vehicles 
		for (std::size_t i = 0; i < active.size(); ++i) {
			active[i].update(dt);
		}
		// this despawns the vehicles when they reach their ending_x pos
		std::size_t i = 0;
		while (i < active.size()) {
			if (active[i].ReachedEnd()) {
				sf::Sprite* s = active[i].spritePtr();
				DespawnSprite(sprites, s);            
				active.erase(active.begin() + i);      
			}
			else {
				++i;
			}
		}

	}
private:
	LaneConfig lanes[17]; // 1..16 
	std::vector<ActiveVehicles> active; // vector of active vehicles on the map
public:
	// getter to get access to the active vehicles 
	std::vector<ActiveVehicles>& getActiveVehicles()  { return active; }
};
Movement MovementOBJ;
