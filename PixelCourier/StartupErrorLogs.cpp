// main file for error log collection of all types of error eventually occurred during the startup of the program
// 2 types of errors -> critical and warnings
// fatal -> failed to load: textures, sprites, positions, hitboxes
// warnings -> failed to load: any audio file, icons

#include "StartupErrorLogs.h"


std::vector<std::string> fatal_errors;
std::vector<std::string> warning_errors;

bool StartupFatalErrorLogs::CollectFatalStartupErrorLogs() {

		// check for correct texture loading
		try {
			bool loaded_all_textures = textures.LoadAllTextures();
			if (!loaded_all_textures) {
				fatal_errors.push_back("Failed to load all textures!");
			}
		}
		catch (const std::exception& e) {
			fatal_errors.push_back(std::string("Critical system error while loading textures: ") + e.what());
		}

		// check for correct sprite loading
		try {
			sprites.CreateAllSprites(textures);
		}
		catch (const std::exception& e) {
			fatal_errors.push_back(std::string("Critical system error while loading sprites: ") + e.what());
		}

		// check for correct position loading
		try {
			bool loaded_positions = position_management.PosInit(sprites, textures);
			if (!loaded_positions) {
				fatal_errors.push_back("Failed to load positions config file!");
			}
		}
		catch (const std::exception& e) {
			fatal_errors.push_back(std::string("Critical system error while loading positions: ") + e.what());
		}

		// check for correct hitbox loading
		try {
			bool loaded_hitboxes = collision.AddHitBox(sprites);
			if (!loaded_hitboxes) {
				fatal_errors.push_back("Failed to load hitbox config file!");
			}
		}
		catch (const std::exception& e) {
			fatal_errors.push_back(std::string("Critical system error while loading hitboxes: ") + e.what());
		}

		// check for vehicle paths loading
		try {
			bool loaded_vehicle_paths = movement.PosInit(sprites, textures);
			if (!loaded_vehicle_paths) {
				fatal_errors.push_back("Failed to load vehicle paths config file!");
			}
		}
		catch (const std::exception& e) {
			fatal_errors.push_back(std::string("Critical system error while loading vehicle paths: ") + e.what());
		}

		// checked if > 0 in main function and if so, display all errors in a message box and exit the program, otherwise continue program
		return fatal_errors.size();
}
StartupFatalErrorLogs StartupFatalErrorLogsOBJ;

bool StartupWarningErrorLogs::CollectWarningStartupErrorLogs() {
		// check for correct icon loading
		sf::Image icon;
		try {
			bool loaded_icon = icon.loadFromFile("assets/icon/icon.png");
			if (!loaded_icon) {
				warning_errors.push_back("Failed to load icon image!");
			}
		}
		catch (const std::exception& e) {
			warning_errors.push_back(std::string("Critical system error while loading icon image: ") + e.what());
		}

		// check for correct music file loading
		sf::Music music_buffer_game_loop;
		try {
			bool loaded_game_loop_music = music_buffer_game_loop.openFromFile("sounds/game_loop.ogg");
			if (!loaded_game_loop_music) {
				warning_errors.push_back("Failed to load game loop music!");
			}
		}
		catch (const std::exception& e) {
			warning_errors.push_back(std::string("Critical system error while loading music files: ") + e.what());
		}

		// CHECK EVERY SOUND FILE LOADING
		sf::SoundBuffer sound_buffer_game_over;
		sf::SoundBuffer sound_buffer_package_collected;
		sf::SoundBuffer sound_buffer_package_delivered;

		// check for correct game over sound loading
		try {
			bool loaded_game_over_sound = sound_buffer_game_over.loadFromFile("sounds/game_over.wav");
			if (!loaded_game_over_sound) {
				warning_errors.push_back("Failed to load game over sound!");
			}
		}
		catch (const std::exception& e) {
			warning_errors.push_back(std::string("Critical system error while loading sound files: ") + e.what());
		}

		// check for correct package collected sound loading
		try {
			bool loaded_package_collected_sound = sound_buffer_package_collected.loadFromFile("sounds/package_collected.wav");
			if (!loaded_package_collected_sound) {
				warning_errors.push_back("Failed to load package collected sound!");
			}
		}
		catch (const std::exception& e) {
			warning_errors.push_back(std::string("Critical system error while loading sound files: ") + e.what());
		}

		// check for correct package delivered sound loading
		try {
			bool loaded_package_delivered_sound = sound_buffer_package_delivered.loadFromFile("sounds/package_delivered.wav");
			if (!loaded_package_delivered_sound) {
				warning_errors.push_back("Failed to load package delivered sound!");
			}
		}
		catch (const std::exception& e) {
			warning_errors.push_back(std::string("Critical system error while loading sound files: ") + e.what());
		}

		// checked if > 0 in main function and if so, display all errors in a message box, but continue the program
		return warning_errors.size();
}
StartupWarningErrorLogs StartupWarningErrorLogsOBJ;