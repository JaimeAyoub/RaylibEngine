#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <raylib.h>
#include <iostream>
#include "Log.h"
class ResourceManager
{
public:
	static ResourceManager& instance() {
		static ResourceManager instance;
		return instance;
	}


	std::shared_ptr<Texture2D> getTexture(const std::string& file) {
		std::string fullPath = texturePath + file;

		auto it = textures.find(fullPath);
		if (it != textures.end()) return it->second;

		if (!FileExists(fullPath.c_str())) {
			Log::print("Texture file not found: " + fullPath);
			return nullptr;
		}
		auto texture = std::make_shared<Texture2D>(LoadTexture(fullPath.c_str()));
		Log::print(fullPath);
		textures[fullPath] = texture;
		return texture;
	}

	std::shared_ptr<Music> getMusic(const std::string& file) {
		std::string fullPath = musicPath + file;

		auto it = musics.find(fullPath);
		if (it != musics.end()) return it->second;

		if (!FileExists(fullPath.c_str())) {
			Log::print("Music file not founded: " + fullPath);
			return nullptr;
		}

		auto music = std::make_shared<Music>(LoadMusicStream(fullPath.c_str()));
		musics[fullPath] = music;
		return music;
	}

	std::shared_ptr<Sound> getSound(const std::string& file) {
		std::string fullPath = soundPath + file;
		auto it = sounds.find(fullPath);
		if (it != sounds.end()) return it->second;

		if (!FileExists(fullPath.c_str())) {
			Log::print("Sound file not founded: " + fullPath);
			return nullptr;
		}
		auto sound = std::make_shared<Sound>(LoadSound(fullPath.c_str()));
		sounds[fullPath] = sound;
		return sound;
	}

	std::shared_ptr<Font> getFont(const std::string& file) {
		std::string fullPath = fontPath + file;
		auto it = fonts.find(fullPath);
		if (it != fonts.end()) return it->second;

		if (!FileExists(fullPath.c_str()))
		{
			Log::print("Font file not founded: " + fullPath);
			return nullptr;
		}
		auto font = std::make_shared<Font>(LoadFontEx(fullPath.c_str(), 32, 0, 250));
		fonts[fullPath] = font;
		return font;
	}

private:

	ResourceManager() = default;
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	std::string texturePath = "assets/textures/";
	std::string musicPath = "assets/music/";
	std::string soundPath = "assets/sounds/";
	std::string fontPath = "assets/fonts/";

	std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;
	std::unordered_map<std::string, std::shared_ptr<Music>> musics;
	std::unordered_map<std::string, std::shared_ptr<Sound>> sounds;
	std::unordered_map<std::string, std::shared_ptr<Font>> fonts;


};

