// header for package delivery logic

#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>

#include "Sprites_load.h"
#include "Timer.h"
#include "Clock.h"
#include "Score.h"


class PackageDeliverySystem {
private:
    // delivery zone around courier_house
    sf::RectangleShape drop_zone;
    bool inside_drop_zone = false;
    std::chrono::steady_clock::time_point in_zone_to_deliver_package; // for package drop 

    void PositionDropZone(const Sprites& sprites) {
        if (sprites.courier_house.empty()) return;

        const sf::Sprite& courier_house = sprites.courier_house[0];
        const sf::FloatRect bounds_courier_house = courier_house.getGlobalBounds();

        const float scale_zone = 1.0f; // scale the zone depending on how big courier_house bounds are

        sf::Vector2f size(bounds_courier_house.width * scale_zone, bounds_courier_house.height * scale_zone); // the size
        drop_zone.setSize(size);
        drop_zone.setOrigin(size.x, size.y);
        
        // centre the zone
        drop_zone.setPosition(bounds_courier_house.left + bounds_courier_house.width, bounds_courier_house.top + bounds_courier_house.height);
    }

public:
    PackageDeliverySystem() {}

    void Update(float delta_time, const sf::FloatRect& courier_box, const Sprites& sprites, bool& package_collected, bool& package_delivered, int& score) {
        PositionDropZone(sprites);
        package_delivered = false;
        // if not carrying a package and trying to deliver (empty thing) or at all not carrying a package => no holding
        if (!package_collected) {
            inside_drop_zone = false;
            return;
        }

        const auto now = std::chrono::steady_clock::now();
        const sf::FloatRect zone = drop_zone.getGlobalBounds();

        // if in the zone holding a package and inside drop_zone
        if (zone.intersects(courier_box)) {
            // check if courier inside zone and start countdown
            if (inside_drop_zone == false) {
                inside_drop_zone = true;
                in_zone_to_deliver_package = now;
                return;
            }
            // check the countdown if 2 sec passed 
            if (now - in_zone_to_deliver_package >= Timers_OBJ.courier_drop_hold_time) {
                // delivered
                package_collected = false;
                package_delivered = true;

                // bonus time 
                ClockDisplay_OBJ.AddTime(Timers_OBJ.package_delivered);

                // score
                score += 1;
            }
        }
        else {
            // outside zone -> reset holding state
            inside_drop_zone = false;
        }
    }

    // draw courier_house drop zone
    void DrawDebugZone(sf::RenderTarget& target) const {
        target.draw(drop_zone);
    }

};
