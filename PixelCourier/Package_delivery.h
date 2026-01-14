#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>

#include "Sprites_load.h"
#include "Timer.h"
#include "Clock.h"
#include "Score.h"


class PackageDeliverySystem {
public:
    PackageDeliverySystem() {
        SetupDropZone(drop_zone);
    }

    void Update(
        float delta_time,
        const sf::FloatRect& courier_box,
        const Sprites& sprites,
        bool& package_collected,
        int& score
    ) {
        UpdateDropZonePosition(sprites);

        if (!package_collected) {
            ResetHold();
            return;
        }

        const auto now = std::chrono::steady_clock::now();
        const sf::FloatRect zone = drop_zone.getGlobalBounds();

        if (!zone.intersects(courier_box)) {
            ResetHold();
            return;
        }

        if (!holding) {
            holding = true;
            hold_start = now;
            return;
        }

        if (now - hold_start >= Timers_OBJ.courier_drop_hold_time) {
            // delivered
            package_collected = false;

            // bonus time
            ClockDisplay_OBJ.AddTime(Timers_OBJ.package_delivered);

            // score
            score += 1;
            const sf::Vector2u window_size(1280, 720);
            sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Game");

            ScoreDisplay_OBJ.SetScore(score, window_size);

            ResetHold();
        }
    }

    // draw courier_house drop zone
    void DrawDebugZone(sf::RenderTarget& target) const {
        target.draw(drop_zone);
    }

private:
    // delivery zone around courier_house
    sf::RectangleShape drop_zone;

    bool holding = false;
    std::chrono::steady_clock::time_point hold_start{};

private:
    static void SetupDropZone(sf::RectangleShape& zone) {
        zone.setSize(sf::Vector2f(100.f, 100.f));
        zone.setOrigin(zone.getSize().x / 2.f, zone.getSize().y / 2.f);

        // TEST ONLY
       // zone.setFillColor(sf::Color(200, 160, 0, 80));
       // zone.setOutlineThickness(2.f);
       // zone.setOutlineColor(sf::Color(200, 160, 0, 220));
    }

    void UpdateDropZonePosition(const Sprites& sprites) {
        if (!sprites.courier_house.empty()) {
            // center zone on courier_house sprite position
            drop_zone.setPosition(sprites.courier_house[0].getPosition() + sf::Vector2f(50.0f, 50.0f));
        }
    }

    void ResetHold() {
        holding = false;
    }
};
