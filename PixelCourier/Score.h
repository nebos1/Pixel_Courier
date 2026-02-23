// header for counting the score through gameplay

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

class ScoreDisplay : public sf::Drawable {
private:
    sf::Font font;
    sf::Text text;

    int score = 0;

    // top right positioning 
    void PositionTopRight(sf::Text& text, sf::RenderWindow& window) {
        sf::Vector2u size = window.getSize();
        sf::FloatRect bounds = text.getLocalBounds();

        float padding_right = 15.f;
        float padding_top = 10.f;

        text.setOrigin(bounds.left + bounds.width, bounds.top);
        text.setPosition((float)size.x - padding_right, padding_top);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(text, states);
    }

public:
    ScoreDisplay() {
        font.loadFromFile("fonts/DynaPuff-Bold.ttf");
        text.setFont(font);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);
        text.setString("Score: 0");
    }

    void Resize(sf::RenderWindow& window) {
        sf::Vector2u size = window.getSize();
        unsigned int char_size = std::max<unsigned>(12u, (unsigned int)(size.y * 0.045f));
        text.setCharacterSize(char_size);
        PositionTopRight(text, window);
    }

    void SetScore(int new_score, sf::RenderWindow& window) {
        score = new_score;
        text.setString("Score: " + std::to_string(score));
        PositionTopRight(text, window);
    }

    void Add(int delta, sf::RenderWindow& window) {
        score += delta;
        text.setString("Score: " + std::to_string(score));
        PositionTopRight(text, window);
    }

    int GetScore() {
        return score;
    }
};

ScoreDisplay ScoreDisplay_OBJ;
