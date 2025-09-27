// applying sprites to textures

#pragma once

#include <SFML/Graphics.hpp>

#include "Textures_load.h"

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



	// all objects that should have collision (pointers)
	std::vector<sf::Sprite*> CollisionObjects;

	void CreateAllSprites(Textures& textures);
};



inline void Sprites::CreateAllSprites(Textures& textures) {
	// player sprite
	player.setTexture(textures.front_courier);


	// map sprite (backgound)
	map.setTexture(textures.map);


	// courier sprites views for directions (idling)
	front_courier.setTexture(textures.front_courier);
	back_courier.setTexture(textures.back_courier);
	left_courier.setTexture(textures.left_courier);
	right_courier.setTexture(textures.right_courier);
	// courier sprites views for moving
	top_moving_courier_1.setTexture(textures.top_moving_courier_1);
	top_moving_courier_2.setTexture(textures.top_moving_courier_2);
	bottom_moving_courier_1.setTexture(textures.bottom_moving_courier_1);
	bottom_moving_courier_2.setTexture(textures.bottom_moving_courier_2);
	left_moving_courier_1.setTexture(textures.left_moving_courier_1);
	right_moving_courier_1.setTexture(textures.right_moving_courier_1);

	// clear all vectors before filling them with new sprites
	// this will load the sprites from Position_management.h
	//
	// buildings
	house_1.clear();
	block_1.clear();
	courier_house.clear();
	church_1.clear();
	// others
	bush_1.clear();
	sunbed_1.clear();
	blue_umbrella_1.clear();
	tree_1.clear();


	// vehicles
	car_1_left.clear();
	car_1_right.clear();

	car_2_left.clear();
	car_2_right.clear();

	truck_1_left.clear();
	truck_1_right.clear();

	pickup_truck_1_left.clear();
	pickup_truck_1_right.clear();

	bus_1_left.clear();
	bus_1_right.clear();


	// apply the texture to the exact sprite
	//
	// buildings
	house_1.push_back(sf::Sprite(textures.house_1));
	block_1.push_back(sf::Sprite(textures.block_1));
	courier_house.push_back(sf::Sprite(textures.courier_house));
	church_1.push_back(sf::Sprite(textures.church_1));

	// others
	bush_1.push_back(sf::Sprite(textures.bush_1));
	sunbed_1.push_back(sf::Sprite(textures.sunbed_1));
	blue_umbrella_1.push_back(sf::Sprite(textures.blue_umbrella_1));
	tree_1.push_back(sf::Sprite(textures.tree_1));

	// vehicles
	car_1_left.push_back(sf::Sprite(textures.car_1_left));
	car_1_right.push_back(sf::Sprite(textures.car_1_right));

	car_2_left.push_back(sf::Sprite(textures.car_2_left));
	car_2_right.push_back(sf::Sprite(textures.car_2_right));

	truck_1_left.push_back(sf::Sprite(textures.truck_1_left));
	truck_1_right.push_back(sf::Sprite(textures.truck_1_right));

	pickup_truck_1_left.push_back(sf::Sprite(textures.pickup_truck_1_left));
	pickup_truck_1_right.push_back(sf::Sprite(textures.pickup_truck_1_right));

	bus_1_left.push_back(sf::Sprite(textures.bus_1_left));
	bus_1_right.push_back(sf::Sprite(textures.bus_1_right));


	// Collision objects
	CollisionObjects.clear();
	CollisionObjects.push_back(&player);

	

	auto AddPointer = [&](std::vector<sf::Sprite>& v) {
		for (auto& s : v) CollisionObjects.push_back(&s);
		};


	// add pointers to all objects for collision
	// buildings
	//
	AddPointer(house_1);
	AddPointer(block_1);
	AddPointer(courier_house);
	AddPointer(church_1);
	//
	// others
	AddPointer(bush_1);
	AddPointer(sunbed_1);
	AddPointer(blue_umbrella_1);
	AddPointer(tree_1);
	//

}