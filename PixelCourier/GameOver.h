// header for Game Over screen UI

#pragma once
#include <SFML/Graphics.hpp>

#include "Collision.h"

#include <algorithm>

class GameOver : public sf::Drawable{
private:
	sf::Font font;
	sf::Text game_over_text;
	sf::Text hint;
	sf::Text score_text;

	// for game over title and hint
	static void CenterText(sf::Text& text, float x, float y) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
		text.setPosition(x, y);
	}

	// for score
	static void TopRight(sf::Text& text, const sf::Vector2u& size, float padding) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width, bounds.top);
		text.setPosition(static_cast<float>(size.x) - padding, padding);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(game_over_text, states);
		target.draw(hint, states);
		target.draw(score_text, states);
	}

public:
	GameOver() {
		font.loadFromFile("fonts/DynaPuff-Bold.ttf");


		game_over_text.setFont(font);
		game_over_text.setFillColor(sf::Color::White);
		game_over_text.setStyle(sf::Text::Bold);
		game_over_text.setString("Game Over!");
		
		hint.setFont(font);
		hint.setFillColor(sf::Color::White);
		hint.setString("Press Enter to exit");

		score_text.setFont(font);
		score_text.setFillColor(sf::Color::White);
		score_text.setString("Score: 0") ;

	}

	void setScore(int score) {
		score_text.setString("Score: " + std::to_string(score));
	}

	// dependable variable for setting positions + all texts size based on window size
	void relayout(const sf::Vector2u& size ) {

		// calculate the sizes of each text based on window size
		const unsigned int title_size = std::max<unsigned>(5, static_cast<unsigned int>(size.y * 0.15)); // 15% of the size
		const unsigned int hint_size = std::max<unsigned>(2, static_cast<unsigned int>(size.y * 0.03)); // 3% of the size
		const unsigned int score_size = std::max<unsigned>(1, static_cast<unsigned int>(size.y * 0.06)); // 6% of the size

		// set sizes
		game_over_text.setCharacterSize(title_size);
		hint.setCharacterSize(hint_size);
		score_text.setCharacterSize(score_size);
	}

	void UpdatePositions(const sf::Vector2u& size) {
		CenterText(game_over_text, size.x * 0.5f, size.y * 0.4f);
		CenterText(hint, size.x * 0.5f, size.y * 0.7f);
		TopRight(score_text, size, std::max(50.f, size.y * 0.05f)); // 5% padding
	}
};
GameOver UI_GameOver_OBJ;

