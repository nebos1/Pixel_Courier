#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>

#include "Npc-s_spawn.h"
#include "Timer.h"
#include "Clock.h"


class PackageCollectSystem {
public:
    void Update(
        float delta_time,
        const sf::FloatRect& courier_box,
        NpcSpawnSystem& npc_system,
        bool& package_collected
    ) {
        if (package_collected) {
            // already carrying a package
            ResetHold();
            return;
        }

        NpcSpawnSystem::NpcSlot* slots = npc_system.GetSlots();
        int slotCount = npc_system.GetSlotCount();

        const auto now = std::chrono::steady_clock::now();

        // If courier is inside any npc zone, we hold on that npc only
        int hit_slot = -1;
        for (int i = 0; i < slotCount; ++i) {
            if (!slots[i].active) continue;

            const sf::FloatRect zone = slots[i].interaction_zone.getGlobalBounds();
            if (zone.intersects(courier_box)) {
                hit_slot = i;
                break;
            }
        }

        if (hit_slot == -1) {
            ResetHold();
            return;
        }

        // started holding on a different npc -> reset
        if (!holding || current_slot != hit_slot) {
            holding = true;
            current_slot = hit_slot;
            hold_start = now;
            return;
        }

        // still holding on same npc
        if (now - hold_start >= Timers_OBJ.npc_pickup_hold_time) {
            // pickup complete
            package_collected = true;

            // bonus time
            ClockDisplay_OBJ.AddTime(Timers_OBJ.taken_package);

            // despawn npc
            slots[current_slot].active = false;

            ResetHold();
        }
    }

private:
    bool holding = false;
    int current_slot = -1;
    std::chrono::steady_clock::time_point hold_start{};

private:
    void ResetHold() {
        holding = false;
        current_slot = -1;
    }
};