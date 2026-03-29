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

	// apply dog moving textures
	sf::Texture dog_1_running_left_1;
	sf::Texture dog_1_running_left_2;
	sf::Texture dog_1_running_right_1;
	sf::Texture dog_1_running_right_2;
	sf::Texture dog_1_running_up_1;
	sf::Texture dog_1_running_up_2;
	sf::Texture dog_1_running_down_1;
	sf::Texture dog_1_running_down_2;

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
