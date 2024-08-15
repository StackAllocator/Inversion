//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include <cassert>
#include <string>
#include <unordered_map>

#include "raylib.h"

#include "./asset_manager.h"

namespace Inversion::AssetManager {

// ----------------------------------------------------------------------------------------------------
// Static variables definition (internal linkage)
// ----------------------------------------------------------------------------------------------------
// Store textures/fonts/sound for the game.
static std::unordered_map<std::string, Texture2D> textures;
static std::unordered_map<std::string, Font> fonts;
static std::unordered_map<std::string, Sound> sounds;
static std::unordered_map<std::string, Music> music;
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
void load_textures() {

  auto load_texture = [=](std::string base_path,
                          std::string file) -> Texture2D {
    Texture2D texture = LoadTexture((base_path + file).c_str());
    // Assertion checks if texture has been loaded correctly.
    assert(texture.id != 0);
    return texture;
  };

  std::string sprite_path = "./Assets/Sprites/";
  std::string emoji_path =
      "./Assets/Sprites/free-emojis-pixelart/emojis-x2-64x64/";

  textures["happy"] = load_texture(emoji_path, "E17.png");
  textures["sad"] = load_texture(emoji_path, "E5.png");
  textures["fear"] = load_texture(emoji_path, "E4.png");
  textures["vomit"] = load_texture(emoji_path, "E37.png");
  textures["exhausted"] = load_texture(emoji_path, "E13.png");

  textures["armor"] = load_texture(sprite_path, "Armorstand.png");
  textures["flag"] = load_texture(sprite_path, "flag.png");

  textures["tileset"] = LoadTexture("./Assets/Sprites/Tiles-and-Enemies.png");

  textures["firework_1"] = LoadTexture("./Assets/Sprites/yellow/1.png");
  textures["firework_2"] = LoadTexture("./Assets/Sprites/yellow/2.png");
  textures["firework_3"] = LoadTexture("./Assets/Sprites/yellow/3.png");
  textures["firework_4"] = LoadTexture("./Assets/Sprites/yellow/4.png");
  textures["firework_5"] = LoadTexture("./Assets/Sprites/yellow/5.png");
  textures["firework_6"] = LoadTexture("./Assets/Sprites/yellow/6.png");
  textures["firework_7"] = LoadTexture("./Assets/Sprites/yellow/7.png");
}
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------
Texture2D get_texture(std::string texture_name) {
  return textures.at(texture_name.c_str());
}

// ----------------------------------------------------------------------------------------------------
void unload_textures() {
  for (auto &texture : textures) {
    UnloadTexture(texture.second);
  }
  textures.clear();
}

// ----------------------------------------------------------------------------------------------------
void load_fonts() {
  fonts["menu"] = LoadFont("./Assets/Fonts/jupiter_crash.png");
  fonts["level"] = LoadFont("./Assets/Fonts/Ticketing.ttf");
  fonts["dejavu"] = LoadFont("./Assets/Fonts/dejavu.png");
}

// ----------------------------------------------------------------------------------------------------
Font get_font(std::string font_name) { return fonts[font_name.c_str()]; }

// ----------------------------------------------------------------------------------------------------
void unload_fonts() {
  for (auto &font : fonts) {
    UnloadFont(font.second);
  }
  fonts.clear();
}

// ----------------------------------------------------------------------------------------------------
void load_sounds() {
  sounds["jump"] = LoadSound("./Assets/Sound/jump_07.wav");
  sounds["flip"] = LoadSound("./Assets/Sound/switch1.wav");
  sounds["win"] = LoadSound("./Assets/Sound/win_sound.wav");

  music["main"] = LoadMusicStream("./Assets/Music/music.ogg");
}

// ----------------------------------------------------------------------------------------------------
Sound get_sound(std::string sound_name) { return sounds[sound_name.c_str()]; }

// ----------------------------------------------------------------------------------------------------
void unload_sounds() {
  for (auto &sound : sounds) {
    UnloadSound(sound.second);
  }
  sounds.clear();
}

// ----------------------------------------------------------------------------------------------------
Music get_music(std::string music_name) { return music.at(music_name.c_str()); }

// ----------------------------------------------------------------------------------------------------
void unload_music() {
  for (auto &my_music : music) {
    UnloadMusicStream(my_music.second); // Unload music stream buffers from RAM.
  }
  music.clear();
}
} // namespace Inversion::AssetManager
