// header for clock time visualization

#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>

#include "Timer.h"

class ClockDisplay : public sf::Drawable {
private:
	sf::Font font;
	sf::Text clock_text;

	std::chrono::steady_clock::time_point start_time;
	std::chrono::seconds base_duration; // starting time
	std::chrono::seconds time_adjustments; // time difference (+/-)
	bool started = false; // countdown

	void PositionTopLeft(sf::Text& text, float padding_x, float padding_y) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left, bounds.top);
		text.setPosition(padding_x, padding_y);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(clock_text, states);
	}

public:
	ClockDisplay() : start_time(std::chrono::steady_clock::now()), base_duration(300), time_adjustments(0), started(false) {
		font.loadFromFile("fonts/DynaPuff-Bold.ttf");
		clock_text.setFont(font);
		clock_text.setFillColor(sf::Color::White);
		clock_text.setCharacterSize(32);
		clock_text.setString("TIME: 0");
		PositionTopLeft(clock_text, 20.f, 15.f);
	}

	void StartCountdown() {
		start_time = std::chrono::steady_clock::now();
		base_duration = Timers_OBJ.timer_duration; // take the current default from Timer.h
		time_adjustments = std::chrono::seconds(0);
		started = true;
		UpdateText();
	}

	void UpdateText() {
		int seconds_left = GetSecondsLeft();
		clock_text.setString("TIME: " + std::to_string(seconds_left)); // string change time
		PositionTopLeft(clock_text, clock_text.getPosition().x, clock_text.getPosition().y); // position set no change
	}

	void AddTime(const std::chrono::seconds& seconds) {
		time_adjustments += seconds;
		UpdateText();
	}

	void SubstractTime(const std::chrono::seconds& seconds) {
		time_adjustments -= seconds;
		UpdateText();
	}

	int GetSecondsLeft() const {
		if (!started) {
			return static_cast<int>(base_duration.count());
		}
		const auto now = std::chrono::steady_clock::now();
		const auto elapsed = now - start_time;
		auto remaining = (base_duration + time_adjustments) - std::chrono::duration_cast<std::chrono::seconds>(elapsed);

		if (remaining.count() < 0) {
			return 0;
		}
		else {
			return static_cast<int>(remaining.count());
		}
	}

	bool TimesUp() const {
		return GetSecondsLeft() <= 0;
	}

	// if window manually resized
	void Resize(const sf::Vector2u& size) {
		unsigned int char_size = std::max<unsigned>(12, static_cast<unsigned int>(size.y * 0.045f));
		clock_text.setCharacterSize(char_size);

		PositionTopLeft(clock_text, std::max(12.f, size.x * 0.015f), std::max(10.f, size.y * 0.015f));
	}

	// getting clock pos (used in Score.h)
	sf::FloatRect GetClockPosition() const {
		return clock_text.getGlobalBounds();
	}
};
ClockDisplay ClockDisplay_OBJ;