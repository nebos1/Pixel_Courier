// layers on all objects applying

//#pragma once

//#include <SFML/Graphics.hpp>
//
//#include "Sprites_load.h"
//#include "Textures_load.h"

//#include <fstream>
//#include <vector>
//#include <string>
//#include <iostream>


//class Layers {
//public:
//	std::map<sf::Sprite*, sf::FloatRect> TopLayerBox; 
//	std::map<sf::Sprite*, sf::FloatRect> BottomLayerBox; 
//
//	void AddLayerBoxes(Sprites& sprites) {
//		std::fstream file("PixelCourier/layers.txt");
//		
//		if(!file.is_open()) {
//			std::cout << "not found the txt!\n";
//			return;
//		}
//
//	TopLayerBox.clear();
//	BottomLayerBox.clear();
//
//
//
//	std::string name;
//	int layer; // higher layer lvl -> more visible the object is
//	// x and y are coordinates of the layer box positions
//	// width_top and height_top are dimensions of the top layer box
//	// width_bottom and height_bottom are dimensions of the bottom layer box
//	float top_layer_x, top_layer_y, bottom_layer_x, bottom_layer_y, width_top, height_top, width_bottom, height_bottom;

	//	while (file >> name >> layer >> top_layer_x >> top_layer_y >> bottom_layer_x >> bottom_layer_y >> width_top >> height_top >> width_bottom >> height_bottom) {

	//		sf::FloatRect top_rect(top_layer_x, top_layer_y, width_top, height_top );
	//		sf::FloatRect bottom_rect(bottom_layer_x, bottom_layer_y, width_bottom, height_bottom);
	//			


	//		// TOFIX

	//		
	//		// player layers
	//		if (name == "player_1") {
	//			TopLayerBox[&sprites.player] = sprites.player.setPosition(top_layer_x, top_layer_y, width_top, height_top);
	//			BottomLayerBox[&sprites.player] = sprites.player.setPosition(bottom_layer_x, bottom_layer_y, width_bottom, height_bottom);
	//		}
	//		else if (name) {
	//			sprites.player.setPosition(top_layer_x, top_layer_y); 
	//		}
	//		else if (layer == 0) { 
	//			
	//		}
	//		else if (layer == 1) {

	//		}
	//	}
	//}

	//TO FIX: BOTH
	// test function for drawing top layer boxes
//    void DrawTopLayerBox(sf::RenderWindow& window, const sf::FloatRect& box) {
//        for(std::map<sf::Sprite*, sf::FloatRect>::iterator it = TopLayerBox.begin(); it != TopLayerBox.end(); ++it) {
//			sf::Sprite* sprite = it->first;
//			sf::FloatRect rect = it->second;
//
//			// actualization of position top layer box
//			sf::RectangleShape top_layer(sf::Vector2f(rect.width, rect.height));
//            top_layer.setPosition(it->second.left, it->second.top);
//            top_layer.setFillColor(sf::Color(0, 0, 255, 100)); // blue
//            window.draw(top_layer);
//
//			
//        }
//
//	// TO ADD: logix for layers
//	}
//};