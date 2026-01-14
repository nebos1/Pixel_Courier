// header for random spawning npc-s near buildings and collecting packages around the map

#pragma once

#include <SFML/System.hpp>

#include "Timer.h"
#include "Sprites_load.h"

#include <random>
#include <vector>
#include <algorithm>


enum BuildingType {
	house,
	block
};

struct BuildingRef {
	BuildingType bt;
	const sf::Sprite* s; // pointing exactly to the house/block
};

std::vector<BuildingRef> CollectAllBuildings(const Sprites& s) {
	// collecting all the buildings for npc-s spawn
	std::vector<BuildingRef> collection;
	collection.reserve(s.house_1.size() + s.block_1.size() /* add the rest when u make em */);

	for (const auto& var : s.house_1) collection.push_back({ BuildingType::house, &var });
	for (const auto& var : s.block_1) collection.push_back({ BuildingType::block, &var });
	// add the others after u make em
	//
	//
	//

	return collection;
}

// 
//




bool package_delivered = false;
bool package_taken = false;
