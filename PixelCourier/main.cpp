#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

#include "Textures_load.h"
#include "Sprites_load.h"
#include "Position_management.h"
#include "Movement.h"
#include "Collision.h"
#include "Moving_vehicles.h"

int main() {

    // FIX: those 2 to be applied at final version
    // 
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktop, "Pixel Courier", sf::Style::Default);

    // now using for tests
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pixel Courier");
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

	sf::Clock clock; // for delta time calculation

    // collision objects
    Collision collision;
    collision.AddHitBox(sprites);


    // map size (same as the background)
    const float map_width = 1500.f;
    const float map_height = 1800.f;


    // camera setup
    sf::View camera(sf::FloatRect(0.f, 0.f, 1280.f, 708.f));
    camera.setCenter(sprites.player.getPosition());
    camera.zoom(0.9f);// later to adjust again

    // vehicle movement setup
    Movement movement;
    movement.PosInit(sprites, textures);
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    while (window.isOpen()) {
        sf::Event event; // basic event creation
        // for window closing btn
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float delta_time = clock.restart().asSeconds();
        // player movement
        HandlePlayerMovement(sprites.player, 200.0f, map_width, map_height, textures, collision, Animation_OBJ, delta_time);

        // vehicle movement update
		movement.Update(delta_time, sprites, textures);
        
        // camera follows the player but stays inside map bounds
        HandleCameraView(sprites.player, camera, map_width, map_height);
        window.setView(camera);



        window.clear();

        // draw objects
        //
        // draw the map as background   
        window.draw(sprites.map);

		// collect everything to sort by y_offset of player feet 
        // 
        struct DrawItem { sf::Sprite* sprite; float y_offset; };
        std::vector<DrawItem> drawList;
        //
        // draw the player
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
		// vehicles
        for (auto& car_1_left : sprites.car_1_left) {
			window.draw(car_1_left);
        }
        for (auto& car_1_right : sprites.car_1_right) {
            window.draw(car_1_right);
        }
        for (auto& car_2_left : sprites.car_2_left) {
            window.draw(car_2_left);
		}
        for (auto& car_2_right : sprites.car_2_right) {
            window.draw(car_2_right);
		}
        for (auto& truck_1_left : sprites.truck_1_left) {
            window.draw(truck_1_left);
        }
        for (auto& truck_1_right : sprites.truck_1_right) {
            window.draw(truck_1_right);
		}
        for (auto& pickup_truck_1_left : sprites.pickup_truck_1_left) {
            window.draw(pickup_truck_1_left);
		}
        for (auto& pickup_truck_1_right : sprites.pickup_truck_1_right) {
            window.draw(pickup_truck_1_right);
        }
        for (auto& bus_1_left : sprites.bus_1_left) {
            window.draw(bus_1_left);
		}
        for (auto& bus_1_right : sprites.bus_1_right) {
            window.draw(bus_1_right);
        }



        //TO BE REMOVED ON FINAL RELEASE
        //
        // test draw of the hitboxes for visualization
        collision.DrawHitBoxes(window);
        //
        //
        // test for reloading hitboxes and positions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            // reload positions
            position_management.PosInit(sprites, textures);
            movement.PosInit(sprites, textures);

            // reload the hitboxes
            collision.AddHitBox(sprites);
            std::cout << "ObjectPositions.size() = " << position_management.ObjectPositions.size() << "\n";
            std::cout << "HitBox.size() = " << collision.HitBox.size() << "\n";
        }
        //

        window.display();
    }
    return 0;
}
