// apply texture to all assets 

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

	bool LoadAllTextures();

};

// load all textures from files
inline bool Textures::LoadAllTextures() {
	bool success = true;
	 
	// from player
	success &= player.loadFromFile("assets/courier/front_view_courier.png");

	// from map
	success &= map.loadFromFile("assets/map/map.png");	

	// from courier (apply idling textures based on position)
	success &= front_courier.loadFromFile("assets/courier/front_view_courier.png");
	success &= back_courier.loadFromFile("assets/courier/back_view_courier.png");
	success &= left_courier.loadFromFile("assets/courier/left_view_courier.png");
	success &= right_courier.loadFromFile("assets/courier/right_view_courier.png");
	// apply moving sprites of the courier based on position
	success &= top_moving_courier_1.loadFromFile("assets/courier/top_moving_courier_1.png");
	success &= top_moving_courier_2.loadFromFile("assets/courier/top_moving_courier_2.png");
	success &= bottom_moving_courier_1.loadFromFile("assets/courier/bottom_moving_courier_1.png");
	success &= bottom_moving_courier_2.loadFromFile("assets/courier/bottom_moving_courier_2.png");
	success &= left_moving_courier_1.loadFromFile("assets/courier/left_moving_courier_1.png");
	success &= right_moving_courier_1.loadFromFile("assets/courier/right_moving_courier_1.png");

	// from buildings
	success &= house_1.loadFromFile("assets/buildings/house_1.png");
	success &= block_1.loadFromFile("assets/buildings/block_1.png");
	success &= courier_house.loadFromFile("assets/buildings/courier_house.png");
	success &= church_1.loadFromFile("assets/buildings/church_1.png");

	// from other
	success &= bush_1.loadFromFile("assets/other/bush_1.png");
	success &= sunbed_1.loadFromFile("assets/other/sunbed_1.png");
	success &= blue_umbrella_1.loadFromFile("assets/other/blue_umbrella_1.png");
	success &= tree_1.loadFromFile("assets/other/tree_1.png");

	// from vehicles
	success &= car_1_left.loadFromFile("assets/vehicles/car_1_left.png");
	success &= car_1_right.loadFromFile("assets/vehicles/car_1_right.png");
	success &= car_2_left.loadFromFile("assets/vehicles/car_2_left.png");
	success &= car_2_right.loadFromFile("assets/vehicles/car_2_right.png");
	success &= truck_1_left.loadFromFile("assets/vehicles/truck_1_left.png");
	success &= truck_1_right.loadFromFile("assets/vehicles/truck_1_right.png");
	success &= pickup_truck_1_left.loadFromFile("assets/vehicles/pickup_truck_1_left.png");
	success &= pickup_truck_1_right.loadFromFile("assets/vehicles/pickup_truck_1_right.png");
	success &= bus_1_left.loadFromFile("assets/vehicles/bus_1_left.png");
	success &= bus_1_right.loadFromFile("assets/vehicles/bus_1_right.png");

	return success;
}



