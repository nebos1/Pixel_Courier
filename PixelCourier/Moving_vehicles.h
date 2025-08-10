// start moving the vehicles on the map to simulate traffic

//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include "Sprites_load.h"
//#include "Textures_load.h"
//
//#include <vector>
//#include <ctime>
//#include <fstream>
//#include <string>
//#include <iostream>


//struct VehicleMovement {
	//float X_Axis, Y_Axis; // starting (X) + ending (Y) points
	//float speed = 0; // moving speed of the vehicles
	//float length = 0; // length of the path for moving
	//float distance_traveled = 0; 

	/*void setSpeed(float new_speed) {
		speed = new_speed;
	}*/
//	void setLength(float new_length) {
//		length = new_length;
//	}
//	void move(float delta_time) {
//		distance_traveled += speed * delta_time;
//		if (distance_traveled > length) {
//			distance_traveled = 0; // reset distance traveled when the vehicle reaches the end of its path
//		}
//	}
//	void draw(sf::RenderWindow& window, sf::Sprite& sprite) {
//		sprite.setPosition(X_Axis + distance_traveled, Y_Axis);
//		window.draw(sprite);
//	}
//};
//VehicleMovement VehicleMovement_OBJ;

//class HandleMovementVehicles {
//public:
//	std::map<sf::Sprite*, VehicleMovement> DirectionMovementVehicle;
//	void PosInit(Sprites& sprites, Textures& textures) {
//		std::fstream file("PixelCourier/vehicle_movement_config.txt");

		/*if (file.is_open()) {
			std::cout << "loading vehicle movement config...\n";
		}
		else if (!file.is_open()) {
			std::cerr << "not found the txt!\n";
			return;
		}*/

		//DirectionMovementVehicle.clear();

		//std::string name;
		//// all left moving vehicles
		//std::unordered_map<std::string, sf::Sprite*> NameToVehicleMovement = {
		//	{"car_1_left", &sprites.car_1_left},
		//	{"car_2_left", &sprites.car_2_left},
		//	{"truck_1_left", &sprites.truck_1_left},
		//	{"pickup_truck_1_left", &sprites.pickup_truck_1_left},
		//	{"bus_1_left", &sprites.bus_1_left},
		//};
		//// all right moving vehicles
		//std::unordered_map<std::string, sf::Sprite*> NameToVehicleMovementRight = {
		//	{"car_1_right", &sprites.car_1_right},
		//	{"car_2_right", &sprites.car_2_right},
		//	{"truck_1_right", &sprites.truck_1_right},
		//	{"pickup_truck_1_right", &sprites.pickup_truck_1_right},
		//	{"bus_1_right", &sprites.bus_1_right},
		//};
		//// TODO: all logic to up and down moving vehicles
		////
		////
		//while (file >> name >> VehicleMovement_OBJ.X_Axis >> VehicleMovement_OBJ.Y_Axis >> VehicleMovement_OBJ.speed >> VehicleMovement_OBJ.length) {
		//	// search the vehicle name
		//	auto it = NameToVehicleMovement.find(name);
		//	if (it == NameToVehicleMovement.end()) continue;

		//	sf::Sprite* sprite = it->second;
		//	sprite->setPosition(VehicleMovement_OBJ.X_Axis, VehicleMovement_OBJ.Y_Axis);
		//	
		//	VehicleMovement movement;
		//	movement.X_Axis = VehicleMovement_OBJ.X_Axis;
		//	movement.Y_Axis = VehicleMovement_OBJ.Y_Axis;
		//	movement.setSpeed(VehicleMovement_OBJ.speed);
		//	movement.setLength(VehicleMovement_OBJ.length);

			//DirectionMovementVehicle[sprite] = movement;
		/*}
	}
	void Update(float delta_time, sf::RenderWindow& window) {
		for (auto& pair : DirectionMovementVehicle) {
			sf::Sprite* sprite = pair.first;
			VehicleMovement& movement = pair.second;
			movement.move(delta_time);
			movement.draw(window, *sprite);
		}
	}
	void Draw(sf::RenderWindow& window) {
		for (auto& pair : DirectionMovementVehicle) {
			sf::Sprite* sprite = pair.first;
			window.draw(*sprite);
		}
	}
};*/