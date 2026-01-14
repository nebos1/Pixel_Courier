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
#include "Player_movement.h"
#include "Collision.h"
#include "Moving_vehicles.h"
#include "Game_over.h"

int main() {

    // FIX: those 2 to be applied at final version
    // 
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktop, "Pixel Courier", sf::Style::Default);

    // now using for tests


    // RENDERING WINDOW FOR VISUALIZATION
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pixel Courier");
    window.setFramerateLimit(60);
    //

    // FOR DELTA TIME CALCULATION
    sf::Clock clock;
    //


    //          LOADING RESOURCES
    //
    // 
    // LOAD ALL TEXTURES
    Textures textures;
    if (!textures.LoadAllTextures()) return -1;
    //

    // CREATE ALL SPRITES
    Sprites sprites;
    sprites.CreateAllSprites(textures);
    //

    // LOAD ALL POSITIONS OF THE OBJECTS
    PositionManagement position_management;
    position_management.PosInit(sprites, textures);
    //
    //
    //          END OF LOADING RESOURCES




    // GAME OVER LOGIC
    bool game_over = false; // flag to check if game is over
    int score = 0; // player score // TOFIX: to be updated in real time
	sf::RectangleShape black_screen(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    black_screen.setFillColor(sf::Color::Black);
    //

    // COLLISION LOGIC
    Collision collision;
    collision.AddHitBox(sprites);
    //

    // MAP SIZE (SAME AS BACKGROUND)
    const float map_width = 1500.f;
    const float map_height = 1800.f;
    //

    // CAMERA VIEW SETUP
    sf::View camera(sf::FloatRect(0.f, 0.f, 1280.f, 708.f));
    camera.setCenter(sprites.player.getPosition());
    camera.zoom(0.9f);// later to adjust again
    //

    // VEHICLE MOVEMENT SETUP
    Movement movement;
    movement.PosInit(sprites, textures);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    //





    // MAIN GAME LOOP
    //
    while (window.isOpen()) {
        sf::Event event; // used as main event handler
        // for window closing btn
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u NewSize(event.size.width, event.size.height);
                if (game_over == true) {
                    UI_GameOver_OBJ.relayout(window.getSize());
                    black_screen.setSize(sf::Vector2f(static_cast<float>(NewSize.x), static_cast<float>(NewSize.y)));
				}
            }
            else if (game_over == true) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
        }

        float delta_time = clock.restart().asSeconds();

        if (game_over == false) {

            // player movement
            HandlePlayerMovement(sprites.player, 180.0f, map_width, map_height, textures, collision, Animation_OBJ, delta_time);

            // vehicle movement update
            movement.Update(delta_time, sprites, textures);

            // camera follows the player but stays inside map bounds
            HandleCameraView(sprites.player, camera, map_width, map_height);

            sf::FloatRect player_box = collision.GetPlayerBox(sprites, collision);

            // player intersection with non-static objects
            bool hit =
                collision.PlayerHitsAnyVehicle(sprites.car_1_left, "car_1_left", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.car_1_right, "car_1_right", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.car_2_left, "car_2_left", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.car_2_right, "car_2_right", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.truck_1_left, "truck_1_left", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.truck_1_right, "truck_1_right", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.pickup_truck_1_left, "pickup_truck_1_left", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.pickup_truck_1_right, "pickup_truck_1_right", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.bus_1_left, "bus_1_left", collision.VehicleConfig, player_box) ||
                collision.PlayerHitsAnyVehicle(sprites.bus_1_right, "bus_1_right", collision.VehicleConfig, player_box);


            if (hit) {
                game_over = true;
                window.setView(window.getDefaultView());
                UI_GameOver_OBJ.setScore(score);
                UI_GameOver_OBJ.relayout(window.getSize());
				UI_GameOver_OBJ.UpdatePositions(window.getSize());


                // clear all old events
                while (window.pollEvent(event)) {}
            }

        }

        window.clear();

            if (game_over == false) {
                window.setView(camera);
                // drawing order
                window.draw(sprites.map);
                window.draw(sprites.player);

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

                // DRAW THE STATIC HITBOXES
                //
                collision.DrawHitBoxes(window);
                //
                // TOFIX: TO BE REMOVED ON FINAL RELEASE!!!



                // TO BE REMOVED LATER!!!!
                //
                // TEST FOR RELOADING EVERYTHING
                // 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
                    // reload positions
                    position_management.PosInit(sprites, textures);
                    movement.PosInit(sprites, textures);
                    // reload the hitboxes
                    collision.AddHitBox(sprites);
                }
            }
            else {
                window.setView(window.getDefaultView());
                window.draw(black_screen);
                window.draw(UI_GameOver_OBJ);
            }

        // to vizualize everything                                                      
        window.display();
    }
}
