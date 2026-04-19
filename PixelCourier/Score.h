// header for score visualization

#pragma once

#include <SFML/Graphics.hpp>

#include "Clock.h"

#include <string>

class ScoreDisplay : public sf::Drawable {
private:
	sf::Font font;
	sf::Text score_text;

	void PositionTopLeftBelowClock(sf::Text& text) {
		sf::FloatRect clock_pos = ClockDisplay_OBJ.GetClockPosition(); // get clock pos box

		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left, bounds.top);

		float spacing = 10.f; // space between both rects
		text.setPosition(clock_pos.left, clock_pos.top + clock_pos.height + spacing);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(score_text, states);
	}

public:
	ScoreDisplay() {
		font.loadFromFile("fonts/DynaPuff-Bold.ttf");
		score_text.setFont(font);
		score_text.setFillColor(sf::Color::White);
		score_text.setCharacterSize(32);
		score_text.setString("SCORE: 0");
		PositionTopLeftBelowClock(score_text);
	}

	void UpdateScore(int score) {
		score_text.setString("SCORE: " + std::to_string(score));
		PositionTopLeftBelowClock(score_text);
	}

	void Resize(const sf::Vector2u& new_size) {
		unsigned int char_size = static_cast<unsigned int>(new_size.y * 0.045f);
		score_text.setCharacterSize(char_size);

		PositionTopLeftBelowClock(score_text);
	}
}; 
ScoreDisplay ScoreDisplay_OBJ;