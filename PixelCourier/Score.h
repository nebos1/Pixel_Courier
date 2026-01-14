// header for counting the score through gameplay

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class ScoreDisplay : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text text;

    int score = 0;

    // top right positioning 
    void PositionTopRight(const sf::Vector2u& window_size)
    {
        sf::FloatRect b = text.getLocalBounds();
        // 16px padding
        float x = static_cast<float>(window_size.x) - (b.width + 16.f);
        float y = 16.f;
        text.setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(text, states);
    }

public:
    ScoreDisplay() {
        if (!font.loadFromFile("fonts/DynaPuff-Bold.ttf")) {
            std::cerr << "Failed to load font";
        }

        text.setFont(font);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);
        text.setString("Score: 0");
        text.setPosition(16.f, 16.f);
    }

    void Resize(const sf::Vector2u& window_size) {
        PositionTopRight(window_size);
    }

    void SetScore(int new_score, const sf::Vector2u& window_size) {
        score = new_score;
        text.setString("Score: " + std::to_string(score));
        PositionTopRight(window_size);
    }

    void Add(int delta, const sf::Vector2u& window_size) {
        score += delta;
        text.setString("Score: " + std::to_string(score));
        PositionTopRight(window_size);
    }

    int GetScore() const {
        return score;
    }
};

ScoreDisplay ScoreDisplay_OBJ;
