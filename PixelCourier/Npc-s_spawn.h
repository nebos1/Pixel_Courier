// header for npc-s spawn logic
#pragma once

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <cstdlib> 
#include <ctime>    

#include "Textures_load.h"
#include "Sprites_load.h"
#include "Timer.h"
#include "Clock.h"


class NpcSpawnSystem : public sf::Drawable {
public:
    struct NpcSlot {
        bool active;
        sf::Sprite sprite;

        // interaction zone 
        sf::RectangleShape interaction_zone;

        // timers
        sf::Clock life_clock; // lifetime since spawn
        sf::Clock idle_clock; // idle animation swap timer

        // idle animation
        bool idle_frame;

        // which npc (1,2,3,4)
        int variant;

        NpcSlot() : active(false), idle_frame(false), variant(1) {}
    };
private:
    NpcSlot slots[3];
    sf::Clock spawn_clock;
    bool first_update;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (int i = 0; i < 3; ++i) {
            if (!slots[i].active) continue; // no active slots
            target.draw(slots[i].sprite, states); // else draw npc
        }
    }

    int FindFreeSlot() const {
        for (int i = 0; i < 3; ++i) {
            if (!slots[i].active) return i;
        }
        return -1;
    }

    // near building spawn position
    static void SetupInteractionZone(sf::RectangleShape& zone) {
        zone.setSize(sf::Vector2f(40.f, 40.f));
        zone.setOrigin(zone.getSize().x / 2.f, zone.getSize().y / 2.f);
    }

    static void AddPositions(std::vector<sf::Vector2f>& target_position, const std::vector<sf::Sprite>& source_sprites) {
        for (std::size_t i = 0; i < source_sprites.size(); ++i) {
            target_position.push_back(source_sprites[i].getPosition());
        }
    }

    std::vector<sf::Vector2f> GetBuildingPositions(const Sprites& sprites) const {
        std::vector<sf::Vector2f> all_building_positions;
        all_building_positions.reserve(128);

        AddPositions(all_building_positions, sprites.house_1);
        AddPositions(all_building_positions, sprites.block_1);
        AddPositions(all_building_positions, sprites.church_1);

        return all_building_positions;
    }

    void TrySpawn(const Sprites& sprites, Textures& textures) {
        int free_slot = FindFreeSlot();
        if (free_slot == -1) return;

        SpawnNpcInSlot(free_slot, sprites, textures);
    }

    void SpawnNpcInSlot(int idx, const Sprites& sprites, Textures& textures) {
        std::vector<sf::Vector2f> buildings = GetBuildingPositions(sprites);
        if (buildings.empty()) return;

        // pick random building 
        int pick = static_cast<int>(std::rand() % buildings.size());
        sf::Vector2f building_pos = buildings[pick];

        // offset so npc is next to it
        sf::Vector2f spawn_pos(building_pos.x - 10.0f, building_pos.y + 40.0f);

        // random npc variant (1..4)
        int variant = 1 + (std::rand() % 4);

        // setup sprite
        slots[idx].variant = variant;
        slots[idx].idle_frame = false;
        slots[idx].sprite.setTexture(GetNpcTexture(textures, variant, false));
        slots[idx].sprite.setPosition(spawn_pos);

        // setup interaction zone
        SetupInteractionZone(slots[idx].interaction_zone);
        slots[idx].interaction_zone.setPosition(slots[idx].sprite.getPosition() + sf::Vector2f(10.0f, 10.0f));

        // activate + restart timers
        slots[idx].active = true;
        slots[idx].life_clock.restart();
        slots[idx].idle_clock.restart();
    }

    static const sf::Texture& GetNpcTexture(Textures& textures, int variant, bool idle_frame) {
        switch (variant) {
        case 1: return idle_frame ? textures.person_1_m2 : textures.person_1_m1;
        case 2: return idle_frame ? textures.person_2_m2 : textures.person_2_m1;
        case 3: return idle_frame ? textures.person_3_m2 : textures.person_3_m1;
        case 4: return idle_frame ? textures.person_4_m2 : textures.person_4_m1;
        default: return idle_frame ? textures.person_1_m2 : textures.person_1_m1;
        }
    }

public:
    NpcSpawnSystem() : first_update(true) {}

    // update spawns/animates/expires npc-s
    void Update(float delta_time, const Sprites& sprites, Textures& textures) {

        // spawn at most 1 npc each interval
        if (first_update == true) {
            TrySpawn(sprites, textures);
            spawn_clock.restart();
            first_update = false;
        }
        else {
            const float spawn_interval_sec = static_cast<float>(Timers_OBJ.npc_spawn_interval.count());
            if (spawn_clock.getElapsedTime().asSeconds() >= spawn_interval_sec) {
                TrySpawn(sprites, textures);
                spawn_clock.restart();
            }
        }

        // update active npc-s
        for (int i = 0; i < 3; ++i) {
            if (!slots[i].active) continue;


            // idle animation swap
            const int idle_ms = static_cast<int>(Timers_OBJ.npc_idle_anim_interval.count());
            if (slots[i].idle_clock.getElapsedTime().asMilliseconds() >= idle_ms) {
                slots[i].idle_frame = !slots[i].idle_frame;
                slots[i].sprite.setTexture(GetNpcTexture(textures, slots[i].variant, slots[i].idle_frame));
                slots[i].idle_clock.restart();
            }

            const float life_sec = static_cast<float>(Timers_OBJ.npc_lifetime.count());
            if (slots[i].life_clock.getElapsedTime().asSeconds() >= life_sec) {
                slots[i].active = false;

                // penalty: -20 sec if npc despawns without taken package
                ClockDisplay_OBJ.SubstractTime(Timers_OBJ.penalty_untaken_package);
            }
        }
    }

    NpcSlot* GetSlots() { 
        return slots; 
    }
    const NpcSlot* GetSlots() const { 
        return slots; 
    }
    int GetSlotCount() const { 
        return 3; 
    }

    void DrawDebugZones(sf::RenderTarget& target) const {
        for (int i = 0; i < 3; ++i) {
            if (!slots[i].active) continue;
            target.draw(slots[i].interaction_zone);
        }
    }
};