#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>

#include "Textures_load.h"
#include "Sprites_load.h"
#include "Position_management.h"
#include "Movement.h"
#include "Collision.h"


int main() {
    // pixelisation and window used for 2d drawing 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 708), "Pixel Courier");
    window.setFramerateLimit(60);

    // load all textures
    Textures textures;
    if (!textures.LoadAllTextures()) return -1;

    // create the sprites
    Sprites sprites;
    sprites.CreateAllSprites(textures);


    // camera setup
    sf::View camera(sf::FloatRect(0.f, 0.f, 1280.f, 708.f));
    camera.setCenter(sprites.player.getPosition());
    camera.zoom(0.9f);//later to adjust again

    // map size (same as the background)
    const float map_width = 1280.f;
    const float map_height = 708.f;
    
	// collision objects setup
	Collision collision;
	collision.Init(sprites);

	// position objects setup
	PositionManagement position_management;
	position_management.PosInit(sprites, textures);

    while (window.isOpen()) {

        sf::Event event; // basic event creation
        // for window closing btn
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // player movement
        HandlePlayerMovement(sprites.player, 2.0f, map_width, map_height, textures, collision);

        // camera follows the player but stays inside map bounds
        HandleCameraView(sprites.player, camera, map_width, map_height);
        window.setView(camera);

        window.clear();

        // Draw objects
        //
		// draw the map as background
        window.draw(sprites.map);

		// draw the static objects
        //from objects
        window.draw(sprites.house_1);
        window.draw(sprites.block_1);
        window.draw(sprites.courier_house);
        window.draw(sprites.church_1);
        //from others
        window.draw(sprites.tree_1);
        window.draw(sprites.bush_1);
        window.draw(sprites.sunbed_1);
		window.draw(sprites.blue_umbrella_1);

        // draw the vehicles
        window.draw(sprites.car_1_left);
        window.draw(sprites.car_1_right);
        window.draw(sprites.car_2_left);
        window.draw(sprites.car_2_right);
        window.draw(sprites.truck_1_left);
        window.draw(sprites.truck_1_right);
        window.draw(sprites.pickup_truck_1_left);
		window.draw(sprites.pickup_truck_1_right);  
		window.draw(sprites.bus_1_left);
		window.draw(sprites.bus_1_right);

        // draw the player
		window.draw(sprites.player);




		// test draw of the hitboxes for visualization
		collision.DrawHitBoxes(window);


		// test for reloading hitboxes and positions
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            // reload the hitboxes
            collision.Init(sprites);
			// reapply positions
			position_management.PosInit(sprites, textures);
            std::cout << "HitBox.size() = " << collision.HitBox.size() << "\n";
			std::cout << "ObjectPositions.size() = " << position_management.ObjectPositions.size() << "\n";

		}

        window.display();
    }

    return 0;
}
