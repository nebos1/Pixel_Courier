#include <SFML/Graphics.hpp>

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

    // set positions to all sprites (otherwise all is 0.0f)
    SetInitialPositions(sprites);

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
        HandlePlayerMovement(sprites.player, 2.0f, map_width, map_height, textures, sprites.CollisionObjects);

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

        window.display();
    }

    return 0;
}
