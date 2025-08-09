// applying sprites to textures

#pragma once

#include <SFML/Graphics.hpp>

#include "Textures_load.h"

#include <vector> // for collision logic to objects and amount of objects



class Sprites {
public:
	// player sprite
	sf::Sprite player;



	// map 
	sf::Sprite map;



	// courier views
	sf::Sprite front_courier;
	sf::Sprite back_courier;
	sf::Sprite left_courier;
	sf::Sprite right_courier;



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
	std::vector<sf::Sprite> car_1_left;
	std::vector<sf::Sprite> car_1_right;

	std::vector<sf::Sprite> car_2_left;
	std::vector<sf::Sprite> car_2_right;

	std::vector<sf::Sprite> truck_1_left;
	std::vector<sf::Sprite> truck_1_right;

	std::vector<sf::Sprite> pickup_truck_1_left;
	std::vector<sf::Sprite> pickup_truck_1_right;

	std::vector<sf::Sprite> bus_1_left;
	std::vector<sf::Sprite> bus_1_right;



	// all objects that should have collision (pointers)
	std::vector<sf::Sprite*> CollisionObjects;

	void CreateAllSprites(Textures& textures);
};



inline void Sprites::CreateAllSprites(Textures& textures) {
	// player sprite
	player.setTexture(textures.front_courier);


	// map sprite (backgound)
	map.setTexture(textures.map);


	// courier sprites for directions
	front_courier.setTexture(textures.front_courier);
	back_courier.setTexture(textures.back_courier);
	left_courier.setTexture(textures.left_courier);
	right_courier.setTexture(textures.right_courier);


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

	// tmp is a temporary variable for applying textures to all objects
	sf::Sprite tmp;

	tmp.setTexture(textures.house_1);
	house_1.push_back(tmp);

	tmp.setTexture(textures.block_1);
	block_1.push_back(tmp);

	tmp.setTexture(textures.courier_house);
	courier_house.push_back(tmp);

	tmp.setTexture(textures.church_1);
	church_1.push_back(tmp);

	tmp.setTexture(textures.bush_1);
	bush_1.push_back(tmp);

	tmp.setTexture(textures.sunbed_1);
	sunbed_1.push_back(tmp);

	tmp.setTexture(textures.blue_umbrella_1);
	blue_umbrella_1.push_back(tmp);

	tmp.setTexture(textures.tree_1);
	tree_1.push_back(tmp);

	tmp.setTexture(textures.car_1_left);
	car_1_left.push_back(tmp);

	tmp.setTexture(textures.car_1_right);
	car_1_right.push_back(tmp);

	tmp.setTexture(textures.car_2_left);
	car_2_left.push_back(tmp);

	tmp.setTexture(textures.car_2_right);
	car_2_right.push_back(tmp);

	tmp.setTexture(textures.truck_1_left);
	truck_1_left.push_back(tmp);

	tmp.setTexture(textures.truck_1_right);
	truck_1_right.push_back(tmp);

	tmp.setTexture(textures.pickup_truck_1_left);
	pickup_truck_1_left.push_back(tmp);

	tmp.setTexture(textures.pickup_truck_1_right);
	pickup_truck_1_right.push_back(tmp);

	tmp.setTexture(textures.bus_1_left);
	bus_1_left.push_back(tmp);

	tmp.setTexture(textures.bus_1_right);
	bus_1_right.push_back(tmp);

	
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
	// vehicles
	AddPointer(car_1_left);
	AddPointer(car_1_right);

	AddPointer(car_2_left);
	AddPointer(car_2_right);

	AddPointer(truck_1_left);
	AddPointer(truck_1_right);

	AddPointer(pickup_truck_1_left);
	AddPointer(pickup_truck_1_right);

	AddPointer(bus_1_left);
	AddPointer(bus_1_right);
}