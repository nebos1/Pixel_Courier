// header for error log collection of all types of error eventually occurred during the startup of the program
// 2 types of errors -> critical and warnings
// fatal -> failed to load: textures, sprites, positions, hitboxes
// warnings -> failed to load: any audio file, icons

#pragma once

#include <vector>
#include <string>
#include <exception>

#include "TexturesLoad.h"
#include "SpritesLoad.h"
#include "PositionManagement.h"
#include "Collision.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


extern std::vector<std::string> fatal_errors;
extern std::vector<std::string> warning_errors;

// class for collecting and managing all critical errors that occur during the startup of the program
class StartupFatalErrorLogs {

	Textures textures;
	Sprites sprites;
	PositionManagement position_management;
	Collision collision;
	Movement movement;
	sf::Font font;

public:
	bool CollectFatalStartupErrorLogs();
};
extern StartupFatalErrorLogs StartupFatalErrorLogsOBJ;

// class for collecting and managing all warning errors that occur during the startup of the program
class StartupWarningErrorLogs {

public:
	bool CollectWarningStartupErrorLogs();
};
extern StartupWarningErrorLogs StartupWarningErrorLogsOBJ;
