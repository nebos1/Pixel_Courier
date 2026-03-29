#include "SpritesLoad.h"

bool Sprites::CreateAllSprites(Textures& textures) {
	// player sprite
	player.setTexture(textures.front_courier);


	// map sprite (background)
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
	// with package
	left_moving_courier_with_package_1.setTexture(textures.left_moving_courier_with_package_1);
	left_moving_courier_with_package_2.setTexture(textures.left_moving_courier_with_package_2);
	right_moving_courier_with_package_1.setTexture(textures.right_moving_courier_with_package_1);
	right_moving_courier_with_package_2.setTexture(textures.right_moving_courier_with_package_2);
	top_moving_courier_with_package_1.setTexture(textures.top_moving_courier_with_package_1);
	top_moving_courier_with_package_2.setTexture(textures.top_moving_courier_with_package_2);
	bottom_moving_courier_with_package_1.setTexture(textures.bottom_moving_courier_with_package_1);
	bottom_moving_courier_with_package_2.setTexture(textures.bottom_moving_courier_with_package_2);

	// dog moving
	dog_1.setTexture(textures.dog_1_running_left_1);

	dog_1_running_left_1.setTexture(textures.dog_1_running_left_1);
	dog_1_running_left_2.setTexture(textures.dog_1_running_left_2);
	dog_1_running_right_1.setTexture(textures.dog_1_running_right_1);
	dog_1_running_right_2.setTexture(textures.dog_1_running_right_2);
	dog_1_running_up_1.setTexture(textures.dog_1_running_up_1);
	dog_1_running_up_2.setTexture(textures.dog_1_running_up_2);
	dog_1_running_down_1.setTexture(textures.dog_1_running_down_1);
	dog_1_running_down_2.setTexture(textures.dog_1_running_down_2);

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

	// npc-s
	person_1_m1.push_back(sf::Sprite(textures.person_1_m1));
	person_1_m2.push_back(sf::Sprite(textures.person_1_m2));
	person_2_m1.push_back(sf::Sprite(textures.person_2_m1));
	person_2_m2.push_back(sf::Sprite(textures.person_2_m2));
	person_3_m1.push_back(sf::Sprite(textures.person_3_m1));
	person_4_m1.push_back(sf::Sprite(textures.person_4_m1));
	person_4_m2.push_back(sf::Sprite(textures.person_4_m2));


	// Collision objects
	CollisionObjects.clear();
	CollisionObjects.push_back(&player);

	return true;
}