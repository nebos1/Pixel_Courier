#pragma once
#include <SFML/Graphics.hpp>

#include "Collision.h"

class GameOver : public sf::Drawable{
public:
	sf::Font font;
	sf::Text game_over_text;

	GameOver() {
		font.loadFromFile("fonts/DynaPuff-Bold.ttf");
		game_over_text.setFont(font);
		game_over_text.setCharacterSize(100);
		game_over_text.setFillColor(sf::Color::White);
		game_over_text.setStyle(sf::Text::Bold);
		game_over_text.setString("Game Over!");
		game_over_text.setPosition(640.f, 360.f); // center the text in 1280x720 window // FIX IT WITH GETTING THE CURRENT SCREEN SIZE / 2 TO BE EXACTLY ON HALF PLACED
	}


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(game_over_text, states);
	}
};

GameOver CGameOverOBJ_UI;