//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include <gtest/gtest.h>

#include "./../menu.h"
#include "./mock_level.h"
#include "./mock_player.h"
#include "./mock_main_menu.h"

namespace Inversion {

enum class MockGameState { TITLE, MENU, LEVEL_SELECTION, GAME };

class MockGame {
  // Define the three major game states.
  // ----------------------------------------------------------------------------------------------------
public:
  MockGame();
  ~MockGame();

  // Use this public variable to simulate an ESC-key press by raylib.
  bool ESCAPE_PRESSED = false;
  bool ANY_KEY_PRESSED = false;

  // ----------------------------------------------------------------------------------------------------
  void update_game();

private:
  FRIEND_TEST(gameTest, MockGame);

  MockGameState m_GameState;
  MockLevelManager m_Level;
  MockPlayer m_player;
  MockMainMenu m_MockMainMenu;
};
} // namespace Inversion
