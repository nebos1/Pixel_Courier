// header for applying texture to all assets 

#pragma once

#include <SFML/Graphics.hpp>


class Textures {
public:
	// apply player texture
	sf::Texture player;


	// textures from folder assets (and its subfolders)
	//
	// from map
	sf::Texture map; // map texture (used as background img)

	// from courier (apply idling textures based on position)
	sf::Texture front_courier;
	sf::Texture back_courier;
	sf::Texture left_courier;
	sf::Texture right_courier;
	// apply moving sprites of the courier based on position
	sf::Texture top_moving_courier_1;
	sf::Texture top_moving_courier_2;
	sf::Texture bottom_moving_courier_1;
	sf::Texture bottom_moving_courier_2;
	sf::Texture left_moving_courier_1;
	sf::Texture right_moving_courier_1;
	// with package
	sf::Texture left_moving_courier_with_package_1;
	sf::Texture left_moving_courier_with_package_2;
	sf::Texture right_moving_courier_with_package_1;
	sf::Texture right_moving_courier_with_package_2;
	sf::Texture top_moving_courier_with_package_1;
	sf::Texture top_moving_courier_with_package_2;
	sf::Texture bottom_moving_courier_with_package_1;
	sf::Texture bottom_moving_courier_with_package_2;

	// from buildings
	sf::Texture house_1;
	sf::Texture block_1;
	sf::Texture courier_house;
	sf::Texture church_1;

	// from other
	sf::Texture bush_1;
	sf::Texture sunbed_1;
	sf::Texture blue_umbrella_1;
	sf::Texture tree_1;

	// from vehicles
	sf::Texture car_1_left;
	sf::Texture car_1_right;
	sf::Texture car_2_left;
	sf::Texture car_2_right;
	sf::Texture truck_1_left;
	sf::Texture truck_1_right;
	sf::Texture pickup_truck_1_left;
	sf::Texture pickup_truck_1_right;
	sf::Texture bus_1_left;
	sf::Texture bus_1_right;

	// from npc-s
	sf::Texture person_1_m1;
	sf::Texture person_1_m2;
	sf::Texture person_2_m1;
	sf::Texture person_2_m2;
	sf::Texture person_3_m1;
	sf::Texture person_3_m2;
	sf::Texture person_4_m1;
	sf::Texture person_4_m2;

	bool LoadAllTextures();

};

// load all textures from files
inline bool Textures::LoadAllTextures() {
	bool success = true;

	// from player
	if (!player.loadFromFile("assets/courier/front_view_courier.png")) return success = false;

	// from map
	if (!map.loadFromFile("assets/map/map.png")) return success = false;

	// from courier (apply idling textures based on position)
	if (!front_courier.loadFromFile("assets/courier/front_view_courier.png")) return success = false;
	if (!back_courier.loadFromFile("assets/courier/back_view_courier.png")) return success = false;
	if (!left_courier.loadFromFile("assets/courier/left_view_courier.png")) return success = false;
	if (!right_courier.loadFromFile("assets/courier/right_view_courier.png")) return success = false;

	// apply moving sprites of the courier based on position
	if (!top_moving_courier_1.loadFromFile("assets/courier/top_moving_courier_1.png")) return success = false;
	if (!top_moving_courier_2.loadFromFile("assets/courier/top_moving_courier_2.png")) return success = false;
	if (!bottom_moving_courier_1.loadFromFile("assets/courier/bottom_moving_courier_1.png")) return success = false;
	if (!bottom_moving_courier_2.loadFromFile("assets/courier/bottom_moving_courier_2.png")) return success = false;
	if (!left_moving_courier_1.loadFromFile("assets/courier/left_moving_courier_1.png")) return success = false;
	if (!right_moving_courier_1.loadFromFile("assets/courier/right_moving_courier_1.png")) return success = false;

	// with package
	if (!left_moving_courier_with_package_1.loadFromFile("assets/courier/left_moving_courier_with_package_1.png")) return success = false;
	if (!left_moving_courier_with_package_2.loadFromFile("assets/courier/left_moving_courier_with_package_2.png")) return success = false;
	if (!right_moving_courier_with_package_1.loadFromFile("assets/courier/right_moving_courier_with_package_1.png")) return success = false;
	if (!right_moving_courier_with_package_2.loadFromFile("assets/courier/right_moving_courier_with_package_2.png")) return success = false;
	if (!top_moving_courier_with_package_1.loadFromFile("assets/courier/top_moving_courier_with_package_1.png")) return success = false;
	if (!top_moving_courier_with_package_2.loadFromFile("assets/courier/top_moving_courier_with_package_2.png")) return success = false;
	if (!bottom_moving_courier_with_package_1.loadFromFile("assets/courier/bottom_moving_courier_with_package_1.png")) return success = false;
	if (!bottom_moving_courier_with_package_2.loadFromFile("assets/courier/bottom_moving_courier_with_package_2.png")) return success = false;

	// from buildings
	if (!house_1.loadFromFile("assets/buildings/house_1.png")) return success = false;
	if (!block_1.loadFromFile("assets/buildings/block_1.png")) return success = false;
	if (!courier_house.loadFromFile("assets/buildings/courier_house.png")) return success = false;
	if (!church_1.loadFromFile("assets/buildings/church_1.png")) return success = false;

	// from other
	if (!bush_1.loadFromFile("assets/other/bush_1.png")) return success = false;
	if (!sunbed_1.loadFromFile("assets/other/sunbed_1.png")) return success = false;
	if (!blue_umbrella_1.loadFromFile("assets/other/blue_umbrella_1.png")) return success = false;
	if (!tree_1.loadFromFile("assets/other/tree_1.png")) return success = false;

	// from vehicles
	if (!car_1_left.loadFromFile("assets/vehicles/car_1_left.png")) return success = false;
	if (!car_1_right.loadFromFile("assets/vehicles/car_1_right.png")) return success = false;
	if (!car_2_left.loadFromFile("assets/vehicles/car_2_left.png")) return success = false;
	if (!car_2_right.loadFromFile("assets/vehicles/car_2_right.png")) return success = false;
	if (!truck_1_left.loadFromFile("assets/vehicles/truck_1_left.png")) return success = false;
	if (!truck_1_right.loadFromFile("assets/vehicles/truck_1_right.png")) return success = false;
	if (!pickup_truck_1_left.loadFromFile("assets/vehicles/pickup_truck_1_left.png")) return success = false;
	if (!pickup_truck_1_right.loadFromFile("assets/vehicles/pickup_truck_1_right.png")) return success = false;
	if (!bus_1_left.loadFromFile("assets/vehicles/bus_1_left.png")) return success = false;
	if (!bus_1_right.loadFromFile("assets/vehicles/bus_1_right.png")) return success = false;

	// from npc-s
	if (!person_1_m1.loadFromFile("assets/npc-s/person_1_m1.png")) return success = false;
	if (!person_1_m2.loadFromFile("assets/npc-s/person_1_m2.png")) return success = false;
	if (!person_2_m1.loadFromFile("assets/npc-s/person_2_m1.png")) return success = false;
	if (!person_2_m2.loadFromFile("assets/npc-s/person_2_m2.png")) return success = false;
	if (!person_3_m1.loadFromFile("assets/npc-s/person_3_m1.png")) return success = false;
	if (!person_3_m2.loadFromFile("assets/npc-s/person_3_m2.png")) return success = false;
	if (!person_4_m1.loadFromFile("assets/npc-s/person_4_m1.png")) return success = false;
	if (!person_4_m2.loadFromFile("assets/npc-s/person_4_m2.png")) return success = false;

	return success;
}
