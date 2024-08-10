//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include "raylib.h"
#include <string>

namespace Inversion::AssetManager {
// ----------------------------------------------------------------------------------------------------
// Load all textures into memory.
void load_textures();

// ----------------------------------------------------------------------------------------------------
// Retrieve texture based on unique identifier.
Texture2D get_texture(std::string texture_name);

// ----------------------------------------------------------------------------------------------------
// Unload textures.
void unload_textures();

// ----------------------------------------------------------------------------------------------------
// Load custom fonts.
void load_fonts();

// ----------------------------------------------------------------------------------------------------
// Get a custom font based on unique identifier.
Font get_font(std::string font_name);

// ----------------------------------------------------------------------------------------------------
// Unload the font.
void unload_fonts();

// ----------------------------------------------------------------------------------------------------
// Load sounds and music into RAM.
void load_sounds();

// ----------------------------------------------------------------------------------------------------
// Get sound based on unique identifier.
Sound get_sound(std::string sound_name);

// ----------------------------------------------------------------------------------------------------
// Unload all sounds.
void unload_sounds();

// ----------------------------------------------------------------------------------------------------
// Retrieve music by unique identifier.
Music get_music(std::string music_name);

// ----------------------------------------------------------------------------------------------------
// Unload music.
void unload_music();
} // namespace Inversion::AssetManager
