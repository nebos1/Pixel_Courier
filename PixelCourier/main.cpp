#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <exception>

#include "TexturesLoad.h"
#include "SpritesLoad.h"
#include "PositionManagement.h"
#include "PlayerMovement.h"
#include "Collision.h"
#include "MovingVehicles.h"
#include "GameOver.h"
#include "Clock.h"
#include "Timer.h"
#include "Score.h"
#include "NpcsSpawn.h"
#include "PackageCollect.h"
#include "PackageDelivery.h"
#include "StartupErrorLogs.h"

int main() {
    StartupFatalErrorLogsOBJ.CollectFatalStartupErrorLogs();
    StartupWarningErrorLogsOBJ.CollectWarningStartupErrorLogs();

    // create standard render window with different visualizations dependable on diff states
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pixel Courier");
    window.setFramerateLimit(60);

    // track the current win siz
    sf::View UIView(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));


    enum class GameState {
        StartupFatalScreen,
        StartupWarningScreen,
        Running,
        Exit
    };
    GameState GameStateENUM;


    // determine initial state based on startup errors
    if (!fatal_errors.empty()) {
        GameStateENUM = GameState::StartupFatalScreen;
        for (size_t i = 0; i < fatal_errors.size(); i++) {
            std::cerr << fatal_errors[i] << std::endl;
        }
    }
    else if (!warning_errors.empty()) {
        GameStateENUM = GameState::StartupWarningScreen;
        for (size_t i = 0; i < warning_errors.size(); i++) {
            std::cerr << warning_errors[i] << std::endl;
        }
    }
    else {
        GameStateENUM = GameState::Running;
    }

    // font + texts for startup error screens
    sf::Font error_text;
    error_text.loadFromFile("fonts/DynaPuff-Bold.ttf");

    std::vector<sf::Text> startup_error_texts;
    sf::Text error_text_hint_enter;
    error_text_hint_enter.setFont(error_text);
    error_text_hint_enter.setFillColor(sf::Color::White);
    error_text_hint_enter.setCharacterSize(20);

    if (GameStateENUM == GameState::StartupFatalScreen) {
        for (size_t i = 0; i < fatal_errors.size(); i++) {
            sf::Text line;
            line.setFont(error_text);
            line.setFillColor(sf::Color::Red);
            line.setCharacterSize(18);
            line.setString("FATAL ERROR: " + fatal_errors[i]);
            line.setPosition(30.f, 30.f + static_cast<float>(i) * 30.f);
            startup_error_texts.push_back(line);
        }
        error_text_hint_enter.setString("Game will not start! Press 'Enter' to exit! ");
        error_text_hint_enter.setPosition(30.f, 30.f + static_cast<float>(fatal_errors.size()) * 30.f + 30.f);
    }
    else if (GameStateENUM == GameState::StartupWarningScreen) {
        for (size_t i = 0; i < warning_errors.size(); i++) {
            sf::Text line;
            line.setFont(error_text);
            line.setFillColor(sf::Color::Yellow);
            line.setCharacterSize(18);
            line.setString("WARNING ERROR: " + warning_errors[i]);
            line.setPosition(30.f, 30.f + static_cast<float>(i) * 30.f);
            startup_error_texts.push_back(line);
        }
        error_text_hint_enter.setString("Game will start! Press 'Enter' to continue! ");
        error_text_hint_enter.setPosition(30.f, 30.f + static_cast<float>(warning_errors.size()) * 30.f + 30.f);
    }


    sf::Music music_buffer_game_loop;

    sf::SoundBuffer sound_buffer_game_over;
    sf::SoundBuffer sound_buffer_package_collected;
    sf::SoundBuffer sound_buffer_package_delivered;

    sf::Sound sound_game_over;
    sf::Sound sound_package_collected;
    sf::Sound sound_package_delivered;

    // load audio files into main's buffers
    music_buffer_game_loop.openFromFile("sounds/game_loop.ogg");
    sound_buffer_game_over.loadFromFile("sounds/game_over.wav");
    sound_buffer_package_collected.loadFromFile("sounds/package_collected.wav");
    sound_buffer_package_delivered.loadFromFile("sounds/package_delivered.wav");

    if (GameStateENUM == GameState::Running) {
        music_buffer_game_loop.setLoop(true);
        music_buffer_game_loop.setVolume(50.0f);
        music_buffer_game_loop.play();

        sound_game_over.setBuffer(sound_buffer_game_over);
        sound_game_over.setVolume(100.0f);

        sound_package_collected.setBuffer(sound_buffer_package_collected);
        sound_package_collected.setLoop(false);
        sound_package_collected.setVolume(100.0f);

        sound_package_delivered.setBuffer(sound_buffer_package_delivered);
        sound_package_delivered.setLoop(false);
        sound_package_delivered.setVolume(100.0f);
    }



    // game over
    bool game_over = false;
    int score = 0;
    bool package_collected = false;
    bool package_delivered = false;

    sf::RectangleShape black_screen(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    black_screen.setFillColor(sf::Color::Black);


    sf::Clock clock;
    float delta_time = clock.restart().asSeconds();

    Collision collision;
    Sprites sprites;
    Textures textures;
    Movement movement;
    PositionManagement position_management;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // load game data into main objects (startup check already verified these succeed)
    if (fatal_errors.empty()) {
        textures.LoadAllTextures();
        sprites.CreateAllSprites(textures);
        position_management.PosInit(sprites, textures);
        collision.AddHitBox(sprites);
        movement.PosInit(sprites, textures);
    }

    NpcSpawnSystem npc_spawn;
    PackageCollectSystem package_collect;
    PackageDeliverySystem package_delivery;

    // map size
    const float map_width = 1500.f;
    const float map_height = 1800.f;


    // camera view
    sf::View camera(sf::FloatRect(0.f, 0.f, 1280.f, 708.f));
    camera.setCenter(sprites.player.getPosition());
    camera.zoom(0.9f);

    // clock with time
    ClockDisplay_OBJ.Resize(window.getSize());
    ClockDisplay_OBJ.StartCountdown(); // start with 300 sec

    // score
    ScoreDisplay_OBJ.Resize(window.getSize());


    // MAIN GAME LOOP
    //
    while (window.isOpen()) {
        delta_time = clock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            // win closing btn
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // win resize 
            else if (event.type == sf::Event::Resized) {
                sf::Vector2u NewSize(event.size.width, event.size.height);
                UIView.setSize(static_cast<float>(NewSize.x), static_cast<float>(NewSize.y));
                UIView.setCenter(static_cast<float>(NewSize.x) / 2.f, static_cast<float>(NewSize.y) / 2.f);
                black_screen.setSize(sf::Vector2f(static_cast<float>(NewSize.x), static_cast<float>(NewSize.y)));

                if (game_over == true) {
                    UI_GameOver_OBJ.relayout(NewSize);
                    UI_GameOver_OBJ.UpdatePositions(NewSize);
                }
                ClockDisplay_OBJ.Resize(NewSize);
                ScoreDisplay_OBJ.Resize(NewSize);
            }
            // startup fatal screen -> Enter exits program
            else if (GameStateENUM == GameState::StartupFatalScreen) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
            // startup warning screen -> Enter continues to game
            else if (GameStateENUM == GameState::StartupWarningScreen) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    GameStateENUM = GameState::Running;

                    // set up audio now that we're entering the Running state
                    music_buffer_game_loop.setLoop(true);
                    music_buffer_game_loop.setVolume(50.0f);
                    music_buffer_game_loop.play();

                    sound_game_over.setBuffer(sound_buffer_game_over);
                    sound_game_over.setVolume(100.0f);

                    sound_package_collected.setBuffer(sound_buffer_package_collected);
                    sound_package_collected.setLoop(false);
                    sound_package_collected.setVolume(100.0f);

                    sound_package_delivered.setBuffer(sound_buffer_package_delivered);
                    sound_package_delivered.setLoop(false);
                    sound_package_delivered.setVolume(100.0f);
                }
            }
            else if (game_over == true) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
        }

        if (GameStateENUM == GameState::Running && game_over == false) {

            // player movement (NOTE: last parameter controls "carrying package" textures)
            HandlePlayerMovement(sprites.player, 180.0f, map_width, map_height, textures, collision, Animation_OBJ, delta_time, package_collected);

            // vehicle movement update
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
            ScoreDisplay_OBJ.UpdateScore(score);

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
                window.setView(UIView);
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

        // startup error screens (fatal or warning)
        if (GameStateENUM == GameState::StartupFatalScreen || GameStateENUM == GameState::StartupWarningScreen) {
            window.setView(UIView);
            window.draw(black_screen);
            for (const auto& text : startup_error_texts) window.draw(text);
            window.draw(error_text_hint_enter);
        }
        else if (game_over == false) {
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
            window.setView(UIView);
            window.draw(ClockDisplay_OBJ);
            window.draw(ScoreDisplay_OBJ);
        }
        else {
            window.setView(UIView);
            window.draw(black_screen);
            window.draw(UI_GameOver_OBJ);
        }
        // to visualize everything
        window.display();

    }
    return 0;
}