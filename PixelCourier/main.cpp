#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <algorithm>

#include "Textures_load.h"
#include "Sprites_load.h"
#include "Position_management.h"
#include "Movement.h"


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


	// load all positions of objects
	PositionManagement position_management;
	position_management.PosInit(sprites, textures);


	// collision objects
	Collision collision;
	collision.Init(sprites);


    // map size (same as the background)
    const float map_width = 1500.f;
    const float map_height = 1800.f;

    
    // camera setup
    sf::View camera(sf::FloatRect(0.f, 0.f, 1280.f, 708.f));
    camera.setCenter(sprites.player.getPosition());
    camera.zoom(0.3f);

    // map size (same as the background)
    const float map_width = 1280.f;
    const float map_height = 708.f;
    
    while (window.isOpen()) {

        sf::Event event; // basic event creation
        // for window closing btn
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // player movement
        HandlePlayerMovement(sprites.player, 10.0f, map_width, map_height, textures, collision);

        // camera follows the player but stays inside map bounds
        HandleCameraView(sprites.player, camera, map_width, map_height);
        window.setView(camera);

        window.clear();

        // Draw objects
        window.draw(sprites.map);
        window.draw(sprites.house_1);
        window.draw(sprites.block_1);
        window.draw(sprites.courier_house);
        window.draw(sprites.tree_1);
        window.draw(sprites.bush_1);
        window.draw(sprites.sunbed_1);
        window.draw(sprites.blue_umbrella_1);
        window.draw(sprites.player);


        // draw the buildings + other objects
        //
        // buildings
        for (auto& house : sprites.house_1) {
            window.draw(house);
        }
        for (auto& block : sprites.block_1) {
            window.draw(block);
        }
        for (auto& courier_house : sprites.courier_house) {
            window.draw(courier_house);
        }
        for (auto& church : sprites.church_1) {
            window.draw(church);
        }
        // other objects
        for (auto& bush : sprites.bush_1) {
            window.draw(bush);
        }
        for (auto& sunbed : sprites.sunbed_1) {
            window.draw(sunbed);
        }
        for (auto& blue_umbrella : sprites.blue_umbrella_1) {
            window.draw(blue_umbrella);
        }
        for (auto& tree : sprites.tree_1) {
            window.draw(tree);
        }



        // test draw of the hitboxes for visualization
        collision.DrawHitBoxes(window);
        //
        //
        // test for reloading hitboxes and positions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            // reload positions
            position_management.PosInit(sprites, textures);
            // reload the hitboxes
            collision.Init(sprites);
            std::cout << "ObjectPositions.size() = " << position_management.ObjectPositions.size() << "\n";
            std::cout << "HitBox.size() = " << collision.HitBox.size() << "\n";
        }


        window.display();
    }

    return 0;
}
