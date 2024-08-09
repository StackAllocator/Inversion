//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

// STL
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

#include "json.hpp"
#include "raylib.h"

#include "./asset_manager.h"
#include "./level.h"

using json = nlohmann::json;

static std::map<int, json> levels;

// ----------------------------------------------------------------------------------------------------
// Parses the JSON files based on the given path.
json load_map(std::string path) {
  std::ifstream file(path.c_str());
  assert(file.is_open());

  json data = json::parse(file);
  return data;
}

// Function loads and extracts JSON data
// and stores the level as a vector of rectangles.
void load_and_extract(const std::string &path, Inversion::TileMapping &level) {
  json level_data = load_map(path);

  // Extract tile info from provided level data.
  float tile_width = static_cast<float>(level_data["tilewidth"]);
  float tile_height = static_cast<float>(level_data["tileheight"]);

  // Tilemap and actual screen dimensions differ by a factor of 4.
  float screen_tile_width = 4 * tile_width;
  float screen_tile_height = 4 * tile_height;

  // Set bit flags to retrieve flip data in encoded number.
  const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
  const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
  const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

  // Compute the width of the tileset.
  int tilesetwidth =
      static_cast<int>(level_data["tilesets"][0]["imagewidth"]) / tile_width;

  int width = level_data["layers"][0]["width"];
  int height = level_data["layers"][0]["height"];

  // Ensure level.coords and level.rects are cleared before populating.
  level.coords.clear();
  level.rects.clear();

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      int index = row * width + col;
      unsigned gid = level_data["layers"][0]["data"][index];

      // Extract the global ID and adjust for Tiled's 1-based indexing
      unsigned i = (gid & 0x0fffffff) - 1;

      // Compute (x, y) position.
      float x = static_cast<float>(i % tilesetwidth) * tile_width;
      float y = static_cast<int>(i / tilesetwidth) * tile_height;

      // Determine how the file is flipped by extracting bits.
      bool flipped_horizontally = gid & FLIPPED_HORIZONTALLY_FLAG;
      bool flipped_vertically = gid & FLIPPED_VERTICALLY_FLAG;
      bool flipped_diagonally = gid & FLIPPED_DIAGONALLY_FLAG;

      float curr_tile_width = tile_width;
      float curr_tile_height = tile_height;

      if (flipped_horizontally)
        curr_tile_width *= -1;

      if (flipped_vertically)
        curr_tile_height *= -1;

      float rotation = 0.f;

      // Compute the destination rectangle coordinates
      float dest_x = static_cast<float>(col * screen_tile_width);
      float dest_y = static_cast<float>(row * screen_tile_height);

      if (flipped_diagonally) {
        // Translate tiles to according to a diagonal flip.
        rotation = 90.f;
        curr_tile_width *= -1;
        dest_x += screen_tile_width;
      }

      level.rects.push_back(
          {dest_x, dest_y, screen_tile_width, screen_tile_height});

      // Compute the coordinates for the source rectangle
      level.coords.push_back({x, y});
      level.width.push_back(curr_tile_width);
      level.height.push_back(curr_tile_height);
      level.rotation.push_back(rotation);

      if (i == 146 || i == 1610613175 || i == 2684354706 || i == 133 || i == 490) {

	if (flipped_diagonally) {
	  dest_y -= screen_tile_height;
	}
	if (flipped_horizontally) {
	  dest_x -= screen_tile_width;
	}
	else if (flipped_vertically) {
	  dest_x -= screen_tile_height;
	}
	level.collision_rects.push_back({dest_x, dest_y, screen_tile_width, screen_tile_height});
      }
    }
  }
}

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
Level::Level() {
  load_and_extract("./Assets/JSON/level_1.tmj", level_1);
  load_and_extract("./Assets/JSON/level_2.tmj", level_2);
  load_and_extract("./Assets/JSON/level_3.tmj", level_3);
  load_and_extract("./Assets/JSON/level_4.tmj", level_4);
}

// ----------------------------------------------------------------------------------------------------
void Level::set_texture() {
  this->tileset = Inversion::AssetManager::get_texture("tileset");
}

void draw(TileMapping level, Texture2D tileset, Rectangle flag_pos,
          bool flipped) {
  for (size_t i = 0; i < level.coords.size(); ++i) {
    DrawTexturePro(
        tileset,
        {level.coords[i].x, level.coords[i].y, level.width[i], level.height[i]},
        {level.rects[i].x, level.rects[i].y, level.rects[i].width,
         level.rects[i].height},
        {0, 0}, level.rotation[i], WHITE);
  }
  for (auto &rect : level.collision_rects) {
    DrawRectangleRec(rect, RED);
  }

  int rotation = 0;
  if (flipped) {
    rotation += 180;
  }
  DrawTexturePro(Inversion::AssetManager::get_texture("flag"), {0, 0, 16, 16},
                 flag_pos, {0, 0}, rotation, WHITE);
}

// ----------------------------------------------------------------------------------------------------
void Level::draw_level() {
  if (m_Id == 1) {
    draw(level_1, tileset, {1800, 380, 64, 64}, false);
  } else if (m_Id == 2) {
    draw(level_2, tileset, {1740, 320, 64, 64}, true);
  } else if (m_Id == 3) {
    draw(level_3, tileset, {1740, 320, 64, 64}, true);
  } else if (m_Id == 4) {
    draw(level_4, tileset, {1800, 380, 64, 64}, false);
  }
  else if (m_Id == 5) {
    draw(level_5, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 6) {
    draw(level_6, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 7) {
    draw(level_7, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 8) {
    draw(level_8, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 9) {
    draw(level_9, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 10) {
    draw(level_10, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 11) {
    draw(level_11, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 12) {
    draw(level_12, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 13) {
    draw(level_13, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 14) {
    draw(level_14, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 15) {
    draw(level_15, tileset, {1740, 320, 64, 64}, true);
  }
  else if (m_Id == 16) {
    draw(level_16, tileset, {1740, 320, 64, 64}, true);
  }
}
} // namespace Inversion
