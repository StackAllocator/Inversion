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
#include <map>
#include <string>
#include <unordered_set>
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

  bool flag_flipped;
  Rectangle flag_coords;
};

class LevelManager {
public:
  LevelManager();
  ~LevelManager();

  void load_and_extract(int level_id, const std::string &path);
  void draw_level();

  void set_texture();
  void set_level(int level_id);

  TileMapping current_level;
  std::map<int, TileMapping> levels;
  int m_Id;

private:
  Texture2D tileset;
};
} // namespace Inversion
