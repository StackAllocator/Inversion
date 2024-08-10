//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include "./level.h"
#include "./main_menu.h"
#include "./player.h"

#include "raylib.h"
#include "gtest/gtest.h"

namespace Inversion {

// Define the three major game states.
enum class GameState { TITLE, MENU, LEVEL_SELECTION, GAME };

// ----------------------------------------------------------------------------------------------------
// Class that handles the execution of the game. Title/Menu/Game
class Game {
public:
  Game();
  // ----------------------------------------------------------------------------------------------------
  // Initialize the game.
  void init_game();
  // ----------------------------------------------------------------------------------------------------
  // Run the game.
  void update_game();

  // Draw the main game loop.
  void draw_game();

  // Used to signal when the application should terminate and clean itself up.
  bool m_Quit = false;

private:
  // Define a game-state variable with initial value TITLE.
  GameState m_GameState = GameState::TITLE;

  // Store the music for the game and set desired properties.
  Music m_Music;

  // Create instances of the classes to merge game logic together.
  MainMenu main_menu;
  LevelSelection level_selection;
  LevelManager m_Level;
  Player m_Player;
};
} // namespace Inversion
