#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

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
#include "Clock.h"
#include "Timer.h"
#include "Score.h"
#include "Npc-s_spawn.h"
#include "Package_collect.h"
#include "Package_delivery.h"


int main() {
    // RENDERING WINDOW FOR VISUALIZATION
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pixel Courier");
    window.setFramerateLimit(60);
    //

    // ICON ON RENDERING WINDOW
    sf::Image icon;
    if (icon.loadFromFile("assets/icon/icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    //

    // FOR DELTA TIME CALCULATION
    sf::Clock clock;
    //

    // LOADING RESOURCES //
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
    
    // LOAD ALL AUDIOS
    //
    sf::Music music_buffer_game_loop;


    sf::SoundBuffer sound_buffer_game_over;
    sf::SoundBuffer sound_buffer_package_collected;
    sf::SoundBuffer sound_buffer_package_delivered;

    sf::Sound sound_game_over;
    sf::Sound sound_package_collected;
    sf::Sound sound_package_delivered;

    sound_buffer_game_over.loadFromFile("sounds/game_over.wav");
    sound_buffer_package_collected.loadFromFile("sounds/package_collected.wav");
    sound_buffer_package_delivered.loadFromFile("sounds/package_delivered.wav");

    sound_game_over.setBuffer(sound_buffer_game_over);
    sound_game_over.setVolume(100.0f);

    sound_package_collected.setBuffer(sound_buffer_package_collected);
    sound_package_collected.setLoop(false);
    sound_package_collected.setVolume(100.0f);

    sound_package_delivered.setBuffer(sound_buffer_package_delivered);
    sound_package_delivered.setLoop(false);
    sound_package_delivered.setVolume(100.0f);

    music_buffer_game_loop.openFromFile("sounds/game_loop.ogg");
    music_buffer_game_loop.setLoop(true);
    music_buffer_game_loop.setVolume(50.0f);
    music_buffer_game_loop.play();
    //
    //
    // END OF LOADING RESOURCES // 


    // GAME OVER LOGIC
    bool game_over = false; // flag to check if game is over
    int score = 0;          // player score
    bool package_collected = false; // courier can carry ONLY 1 package at a time
    bool package_delivered = false; // checks if package courier is holding is delivered 

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
    camera.zoom(0.4f);// later to adjust again
    //

    // VEHICLE MOVEMENT SETUP
    Movement movement;
    movement.PosInit(sprites, textures);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    //

    // CLOCK WITH REMAINING TIME DISPLAY
    ClockDisplay_OBJ.Resize(window.getSize());
    ClockDisplay_OBJ.StartCountdown(); // start with 300 sec
    //

    // SCORE DISPLAY (TOP-RIGHT)
    ScoreDisplay_OBJ.Resize(window);
	ScoreDisplay_OBJ.SetScore(score, window);
    //

    // NPC / PACKAGE SYSTEMS
    NpcSpawnSystem npc_spawn;                // spawns and animates NPCs
    PackageCollectSystem package_collect;    // courier -> npc pickup logic
    PackageDeliverySystem package_delivery;  // courier_house delivery logic
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

                ClockDisplay_OBJ.Resize(NewSize);
                ScoreDisplay_OBJ.Resize(window);

                if (game_over == true) {
                    UI_GameOver_OBJ.relayout(NewSize);
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

            // player movement (NOTE: last parameter controls "carrying package" textures)
            HandlePlayerMovement(sprites.player, 180.0f, map_width, map_height, textures, collision, Animation_OBJ, delta_time, package_collected);

            // vehicle movement update
            movement.Update(delta_time, sprites, textures);

            // camera follows the player but stays inside map bounds
            HandleCameraView(sprites.player, camera, map_width, map_height);

            // player hitbox (configured in hitbox_config.txt)
            sf::FloatRect player_box = collision.GetPlayerBox(sprites, collision);

            // NPC spawn + idle animation + expiration penalties
            npc_spawn.Update(delta_time, sprites, textures);


            bool play_collect_sound = false;
            // collect package (hold inside NPC zone for 2 sec)
            package_collect.Update(delta_time, player_box, npc_spawn, package_collected, play_collect_sound);

            // deliver package (hold inside courier_house zone for 2 sec)
            package_delivery.Update(delta_time, player_box, sprites, package_collected, package_delivered, score);

            // update UI text
            ClockDisplay_OBJ.UpdateText();
            ScoreDisplay_OBJ.SetScore(score, window);

            if (play_collect_sound == true) {
                sound_package_collected.play();
            }
            if (package_delivered) {
                sound_package_delivered.play();
            }


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


            if (hit || ClockDisplay_OBJ.TimesUp()) {
                game_over = true;
                window.setView(window.getDefaultView());
                UI_GameOver_OBJ.setScore(score);
                UI_GameOver_OBJ.relayout(window.getSize());
                UI_GameOver_OBJ.UpdatePositions(window.getSize());
                music_buffer_game_loop.stop();
                sound_game_over.play();

                // return func calling black screen and music 
            }

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

        window.clear();

        // draw on the old buffer to replace it
        if(game_over == false) {
            window.setView(camera);

            // drawing order
            window.draw(sprites.map);

            // player
            window.draw(sprites.player);

            for (auto& car_1_left : sprites.car_1_left) window.draw(car_1_left);
            for (auto& car_1_right : sprites.car_1_right) window.draw(car_1_right);
            for (auto& car_2_left : sprites.car_2_left) window.draw(car_2_left);
            for (auto& car_2_right : sprites.car_2_right) window.draw(car_2_right);
            for (auto& truck_1_left : sprites.truck_1_left) window.draw(truck_1_left);
            for (auto& truck_1_right : sprites.truck_1_right) window.draw(truck_1_right);
            for (auto& pickup_truck_1_left : sprites.pickup_truck_1_left) window.draw(pickup_truck_1_left);
            for (auto& pickup_truck_1_right : sprites.pickup_truck_1_right) window.draw(pickup_truck_1_right);
            for (auto& bus_1_left : sprites.bus_1_left) window.draw(bus_1_left);
            for (auto& bus_1_right : sprites.bus_1_right) window.draw(bus_1_right);

            // buildings/props
            for (auto& house : sprites.house_1) window.draw(house);
            for (auto& block : sprites.block_1) window.draw(block);
            for (auto& courier_house : sprites.courier_house) window.draw(courier_house);
            for (auto& church : sprites.church_1) window.draw(church);
            for (auto& bush : sprites.bush_1) window.draw(bush);
            for (auto& sunbed : sprites.sunbed_1) window.draw(sunbed);
            for (auto& blue_umbrella : sprites.blue_umbrella_1) window.draw(blue_umbrella);
            for (auto& tree : sprites.tree_1) window.draw(tree);

            // NPCs MUST be drawn AFTER buildings (to appear "in front")
            window.draw(npc_spawn);


            // draw the clock + score in screen space
            window.setView(window.getDefaultView());
            window.draw(ClockDisplay_OBJ);
            window.draw(ScoreDisplay_OBJ);
        }
        else {
            window.setView(window.getDefaultView());
            window.draw(black_screen);
            window.draw(UI_GameOver_OBJ);
        }
        // to visualize everything
        window.display();

    }

    return 0;
}
