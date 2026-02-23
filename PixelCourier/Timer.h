// header with different timers depending on the events happening 

#pragma once

#include <chrono>



struct Timers {

	// GAME TIMER (GLOBAL COUNTDOWN)
	const std::chrono::seconds timer_duration{ 300 }; // 300 seconds timer (5 min)

	// PACKAGE EVENTS
	const std::chrono::seconds taken_package{ 10 };             // +10 sec when package is taken 
	const std::chrono::seconds package_delivered{ 30 };         // +30 sec when delivered 
	const std::chrono::seconds penalty_untaken_package{ 20 };   // -20 sec if npc expires
	const std::chrono::seconds penalty_undelivered_package{ 20 }; // -20 sec if fail 

	// NPC SPAWN + LIFETIME 
	const std::chrono::seconds npc_spawn_interval{ 3 }; // spawn npc every 3 seconds
	const std::chrono::seconds npc_lifetime{ 30 };      // npc despawns after 30 sec

	// INTERACTIONS 
	const std::chrono::seconds npc_pickup_hold_time{ 2 };      // hold 2 sec in npc zone to collect
	const std::chrono::seconds courier_drop_hold_time{ 2 };    // hold 2 sec in courier_house zone to deliver

	// NPC IDLE ANIMATION
	const std::chrono::milliseconds npc_idle_anim_interval{ 500 }; // 0.5 sec texture swap

};

static Timers Timers_OBJ;


