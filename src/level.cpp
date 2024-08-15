//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

// STL
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"
#include "raylib.h"

#include "./asset_manager.h"
#include "./level.h"

using json = nlohmann::json;

namespace Inversion {

LevelManager::LevelManager() {
  // Load and extract all levels.
  for (int i = 0; i < 16; ++i) {
    load_and_extract(i,
                     "./Assets/JSON/level_" + std::to_string(i + 1) + ".tmj");
  }
  // Set the current level to the first level.
  m_Id = 0;
  current_level = levels.at(m_Id);
}

LevelManager::~LevelManager() {}

void LevelManager::set_texture() {
  this->tileset = Inversion::AssetManager::get_texture("tileset");
}

void LevelManager::load_and_extract(int level_id, const std::string &path) {
  std::ifstream file(path);
  assert(file.is_open());

  json level_data = json::parse(file);

  TileMapping level;

  // Extract tile info from JSON
  int tile_width = level_data["tilewidth"];
  int tile_height = level_data["tileheight"];

  // TileMap and screen have a 1:4 ratio.
  float screen_tile_width = 4 * tile_width;
  float screen_tile_height = 4 * tile_height;

  int tileset_width =
      static_cast<int>(level_data["tilesets"][0]["imagewidth"]) / tile_width;

  int width = static_cast<int>(level_data["layers"][0]["width"]);
  int height = static_cast<int>(level_data["layers"][0]["height"]);

  for (auto row = 0; row < height; ++row) {
    for (auto col = 0; col < width; ++col) {

      int index = row * width + col;

      // Retrieve the global tile id from the JSON file.
      unsigned gid = level_data["layers"][0]["data"][index];

      // Extract the global ID and adjust for Tiled's 1-based indexing.
      unsigned i = (gid & 0x0fffffff) - 1;

      // Compute (x, y) position in world space.
      float x = (i % tileset_width) * tile_width;
      float y = (i / tileset_width) * tile_height;

      // Compute the destination rectangle coordinates.
      float dest_x = col * screen_tile_width;
      float dest_y = row * screen_tile_height;

      float curr_tile_width = tile_width;
      float curr_tile_height = tile_height;

      // Determine how the tile is flipped by extracting bits.
      bool flipped_horizontally = gid & 0x80000000;
      bool flipped_vertically = gid & 0x40000000;
      bool flipped_diagonally = gid & 0x20000000;

      if (flipped_horizontally)
        curr_tile_width *= -1;
      if (flipped_vertically)
        curr_tile_height *= -1;

      float rotation = 0.f;

      if (flipped_diagonally) {
        rotation = 90.f;
        curr_tile_width *= -1;
        dest_x += screen_tile_width;
      }

      // Compute the cooordinates for the source rectangle.
      level.rects.push_back(
          {dest_x, dest_y, screen_tile_width, screen_tile_height});
      level.coords.push_back({x, y});
      level.width.push_back(curr_tile_width);
      level.height.push_back(curr_tile_height);
      level.rotation.push_back(rotation);

      if (flipped_diagonally) {
        dest_x -= screen_tile_width;
      }

      /*
       * TODO:
       * Instead of checking individual tiles that are hard-coded,
       * I should use an object-layer for collisions and check against that.
       * I also shouldn't store collision rects in a vector but rather
       * compute the player collisions based on the position at runtime.
       */
      if (i == 15 || i == 41 || i == 55 || i == 66 || i == 68 || i == 132 ||
          i == 131 || i == 148 || i == 146 || i == 144 || i == 159 ||
          i == 257 || i == 84 || i == 70 || i == 283 || i == 133 || i == 417 ||
          i == 418 || i == 392 || i == 391 || i == 247 || i == 274 ||
          i == 223) {
        level.collision_rects.push_back(
            {dest_x, dest_y, screen_tile_width, screen_tile_height});
      }
    }
  }

  // Always set the flag to the same coords.
  level.flag_coords = {1780, 380};
  level.flag_flipped = false;

  // Assign the level-map a key-value pair [level_id -> level].
  levels[level_id] = level;
}

void LevelManager::set_level(int level_id) {
  m_Id = level_id;
  current_level = levels.at(m_Id);
}

// Draw the current level.
void LevelManager::draw_level() {

  for (size_t i = 0; i < current_level.coords.size(); ++i) {
    DrawTexturePro(tileset,
                   {current_level.coords[i].x, current_level.coords[i].y,
                    current_level.width[i], current_level.height[i]},
                   {current_level.rects[i].x, current_level.rects[i].y,
                    current_level.rects[i].width,
                    current_level.rects[i].height},
                   {0, 0}, current_level.rotation[i], WHITE);
  }

  DrawTexturePro(
      Inversion::AssetManager::get_texture("flag"), {0, 0, 16, 16},
      {current_level.flag_coords.x, current_level.flag_coords.y, 64, 64},
      {0, 0}, 0, WHITE);
}
} // namespace Inversion
