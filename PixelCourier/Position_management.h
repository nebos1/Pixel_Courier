// apply positions to all objects

#pragma once

#include <SFML/Graphics.hpp>
#include "Textures_load.h"
#include "Sprites_load.h"

inline void SetInitialPositions(Sprites& sprites) {
    // map
    sprites.map.setPosition(0.f, 0.f);

    // player
    sprites.player.setPosition(100.f, 620.f);

    // buildings
    sprites.house_1.setPosition(300.f, 200.f);
    sprites.block_1.setPosition(600.f, 150.f);
    sprites.courier_house.setPosition(1000.f, 400.f);

    // objects
    sprites.tree_1.setPosition(250.f, 500.f);
    sprites.bush_1.setPosition(400.f, 520.f);
    sprites.sunbed_1.setPosition(700.f, 580.f);
    sprites.blue_umbrella_1.setPosition(900.f, 600.f);


}