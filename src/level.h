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
#include <vector>

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// Handle the level core functionality like drawing and initialization.

struct TileMapping {
  std::vector<Rectangle> rects;
  std::vector<Rectangle> collision_rects;
  std::vector<Vector2> coords;
  std::vector<float> rotation;
  std::vector<float> width;
  std::vector<float> height;
  std::vector<int> gids;
};

struct Level {
  Level();
  // Store texture as member so it doesn't get reloaded more than once.
  void set_texture();
  Level(Level &other) = default;
  Level &operator=(Level &other) = default;
  ~Level() = default;
  // Draw the current level with parsed JSON data.
  void draw_level();

  // Set the level id to 1 initially to start with the first level.
  int m_Id = 1;

  // Definitions of the levels.
  TileMapping level_1;
  TileMapping level_2;

  // Store the tileset and extract source rects based on ids.
  Texture2D tileset;
};
} // namespace Inversion
