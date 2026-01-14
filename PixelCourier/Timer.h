// different timers depending on the events happening 

#pragma once

#include <chrono>

struct Timers {
	const std::chrono::seconds timer_duration{ 300 }; // 300 seconds timer (5 min) // used for game start
	const std::chrono::steady_clock::time_point start_countdown{ std::chrono::steady_clock::now() }; // countdown;
	std::chrono::duration<double> time_left { timer_duration - (std::chrono::steady_clock::now() - start_countdown) }; // get elapsed time
	const std::chrono::seconds taken_package{ 10 }; // 10 sec added time for taken package
	const std::chrono::seconds package_delivered{ 30 }; // 20 sec added time for package delivered
	const std::chrono::seconds penalty_untaken_package{ 20 }; // 15 sec penalty for untaken package
	const std::chrono::seconds penalty_undelivered_package{ 20 }; // 20 sec penalty for undelivered package
};
Timers Timers_OBJ;