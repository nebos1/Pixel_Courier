// header for applying sprites to textures 
 
#pragma once

#include <SFML/Graphics.hpp>

#include "TexturesLoad.h"

#include <vector> // for collision logic to objects and amount of objects
#include <list>


class Sprites {
public:
	// player sprite
	sf::Sprite player;



	// map 
	sf::Sprite map;



	// courier views (idling)
	sf::Sprite front_courier;
	sf::Sprite back_courier;
	sf::Sprite left_courier;
	sf::Sprite right_courier;
	// courier views (moving)
	sf::Sprite top_moving_courier_1;
	sf::Sprite top_moving_courier_2;
	sf::Sprite bottom_moving_courier_1;
	sf::Sprite bottom_moving_courier_2;
	sf::Sprite left_moving_courier_1;
	sf::Sprite right_moving_courier_1;
	// with package
	sf::Sprite left_moving_courier_with_package_1;
	sf::Sprite left_moving_courier_with_package_2;
	sf::Sprite right_moving_courier_with_package_1;
	sf::Sprite right_moving_courier_with_package_2;
	sf::Sprite top_moving_courier_with_package_1;
	sf::Sprite top_moving_courier_with_package_2;
	sf::Sprite bottom_moving_courier_with_package_1;
	sf::Sprite bottom_moving_courier_with_package_2;

	// dog
	sf::Sprite dog_1;

	sf::Sprite dog_1_running_right_1;
	sf::Sprite dog_1_running_right_2;
	sf::Sprite dog_1_running_left_1;
	sf::Sprite dog_1_running_left_2;
	sf::Sprite dog_1_running_up_1;
	sf::Sprite dog_1_running_up_2;
	sf::Sprite dog_1_running_down_1;
	sf::Sprite dog_1_running_down_2;


	// buildings 
	std::vector<sf::Sprite> house_1;
	std::vector<sf::Sprite> block_1;
	std::vector<sf::Sprite> courier_house;
	std::vector<sf::Sprite> church_1;



	// others 
	std::vector<sf::Sprite> bush_1;
	std::vector<sf::Sprite> sunbed_1;
	std::vector<sf::Sprite> blue_umbrella_1;
	std::vector<sf::Sprite> tree_1;



	// vehicles 
	std::list<sf::Sprite> car_1_left;
	std::list<sf::Sprite> car_1_right;

	std::list<sf::Sprite> car_2_left;
	std::list<sf::Sprite> car_2_right;

	std::list<sf::Sprite> truck_1_left;
	std::list<sf::Sprite> truck_1_right;

	std::list<sf::Sprite> pickup_truck_1_left;
	std::list<sf::Sprite> pickup_truck_1_right;

	std::list<sf::Sprite> bus_1_left;
	std::list<sf::Sprite> bus_1_right;


	// npc-s
	std::list<sf::Sprite> person_1_m1;
	std::list<sf::Sprite> person_1_m2;
	std::list<sf::Sprite> person_2_m1;
	std::list<sf::Sprite> person_2_m2;
	std::list<sf::Sprite> person_3_m1;
	std::list<sf::Sprite> person_3_m2;
	std::list<sf::Sprite> person_4_m1;
	std::list<sf::Sprite> person_4_m2;


	// all objects that should have collision (pointers)
	std::vector<sf::Sprite*> CollisionObjects;

	bool CreateAllSprites(Textures& textures);
};
