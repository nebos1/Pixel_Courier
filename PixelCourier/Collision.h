// custom collision with every sprite loaded in game

#pragma once
#include <SFML/Graphics.hpp>

#include "Sprites_load.h"

#include <map>


// add the definition of AdjustHitbox function 
// 
// WidthFactor and HeightFactor are the taking factor of the object to remove the collision 
// offset is the moving offset of the colllision figure to be movable

inline sf::FloatRect AdjustHitbox(const sf::Sprite& sprite, float WidthFactor, float HeightFactor, float offset) {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // calculation of the new width and height
    float new_width = bounds.width * WidthFactor;
    float new_height = bounds.height * HeightFactor;

    // shifting 
    bounds.top += bounds.height * offset;

    // centralizing
    bounds.left += (bounds.width - new_width) / 2.0f;

    // apply the new dimensions
    bounds.width = new_width;
    bounds.height = new_height;

    return bounds;
}


class Collision {
public:
	std::map<sf::Sprite*, sf::FloatRect> HitBox;

    // HitBox of the sprite = AdjustHitBox(width, height, offset)

    void Init(Sprites& sprites) {
        HitBox[&sprites.courier_house] = AdjustHitbox(sprites.courier_house, 0.65f, 0.35f, 0.35f);
    }
};