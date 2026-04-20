// header for package collect logic

#pragma once 

#include <SFML/Graphics.hpp> 

#include <chrono> 

#include "NpcsSpawn.h"
#include "Timer.h" 
#include "Clock.h" 


class PackageCollectSystem {
private:
	bool inside_npc_hitbox = false; // checks if courier inside npc pickup zone
	std::chrono::steady_clock::time_point in_zone_on_npc_for_package_collect;
	int current_npc_index = -1; // in which npc hitbox courier is 

public:
	void Update(float delta_time, const sf::FloatRect& courier_box, NpcSpawnSystem& npc_system, bool& package_collected, bool& play_collect_sound) {
		if (package_collected == true) {
			inside_npc_hitbox = false;
			current_npc_index = -1;
			return;
		}
		play_collect_sound = false;

		NpcSpawnSystem::NpcSlot* slots = npc_system.GetSlots();

		int slot_count = npc_system.GetSlotCount();
		const auto now = std::chrono::steady_clock::now();

		int npc_index = -1; // checks if courier leaves the zone before timer runs out 

		// if there are any active npc-s 
		for (int i = 0; i < slot_count; ++i) {
			if (!slots[i].active) continue; // if no active slots -> skip immediately 

			// if courier inside the npc interaction zone 
			if (slots[i].interaction_zone.getGlobalBounds().intersects(courier_box)) {
				npc_index = i; if (inside_npc_hitbox == false || current_npc_index != i) {
					in_zone_on_npc_for_package_collect = now;
					inside_npc_hitbox = true;
					current_npc_index = i;
					return;
				}
				break;
			}
		}

		// if not in npc zone for package collect -> reset timer 
		if (npc_index == -1) {
			inside_npc_hitbox = false;
			current_npc_index = -1;
			return;
		}

		// if courier inside the npc slot and for >= 2sec 
		if (inside_npc_hitbox == true && current_npc_index != -1) {
			if (now - in_zone_on_npc_for_package_collect >= Timers_OBJ.npc_pickup_hold_time) {
				// pickup complete 
				package_collected = true;
				play_collect_sound = true;
				// bonus time 
				ClockDisplay_OBJ.AddTime(Timers_OBJ.taken_package);
				// despawn npc 
				slots[current_npc_index].active = false;
				// reset on success 
				inside_npc_hitbox = false;
				current_npc_index = -1;
			}
		}
	}
};